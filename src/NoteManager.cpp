/**
 * Synthpathy is a small and versatile audio synthesizer on a microcontroler. 
 * Copyright (C) 2022  Brice Croix
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "NoteManager.h"

#include "Controls.h"

#if (defined(DEBUG) || defined(DEBUG_AUDIO))
#include <stdio.h>
#endif

NoteManager::NoteManager()
{
    for(unsigned int i = 0; i < NB_ACTIVE_NOTES; ++i)
    {
        m_active_notes_pool[i].kill();
    }
}

void NoteManager::update_active_notes(unsigned int time_fs)
{
    unsigned int i;
    const Controls& controls = Controls::get_instance();

    // The midi buffer will be empty most of the time
    while(!g_midi_internal_buffer.is_empty())
    {
        // At least one midi event must be processed
        const MidiEvent l_event = g_midi_internal_buffer.pop_fast();
        // Decode the event
        const MidiByte l_midi_type_event = l_event & MIDI_STATUS_MSK;
        const MidiByte l_midi_channel = l_event & MIDI_CHANNEL_MSK;
        const MidiByte l_midi_data1 = l_event >> 8;
        const MidiByte l_midi_data2 = l_event >> 16;

        #ifdef DEBUG
        printf("MIDI event popped : 0x%06x\n", l_event);
        #endif

        // Switch on event type
        switch(l_midi_type_event)
        {
            // A new note must be created
            case MIDI_NOTE_ON:
                // Search for an available index in the pool
                i = 0;
                do
                {
                    if(!m_active_notes_pool[i].is_alive(time_fs))
                    {
                        #ifdef DEBUG
                        printf("Found available note at index %d\n", i);
                        #endif

                        const float velocity = static_cast<float>(l_midi_data2) / 0x7F;
                        // Add the new note to the pool
                        m_active_notes_pool[i] = ActiveNote(l_midi_data1, velocity, time_fs, controls.get_attack_fs(), controls.get_decay_fs());
                        break;
                    }    
                }
                while ((++i) < NB_ACTIVE_NOTES);
                break;

            // A formerly created note must be released
            case MIDI_NOTE_OFF:
                // Search for the note to be released
                i = 0;
                do
                {
                    // Search for this midi note that is not released yet
                    if(m_active_notes_pool[i].get_midi_note() == l_midi_data1 && !m_active_notes_pool[i].is_released())
                    {
                        #ifdef DEBUG
                        printf("Found note to release at index %d\n", i);
                        #endif

                        // Release
                        m_active_notes_pool[i].release(time_fs, controls.get_sustain(), controls.get_release_fs());
                        break;
                    }
                }
                while ((++i) < NB_ACTIVE_NOTES);
                break;

            case MIDI_AFTERTOUCH_CHANNEL:
            case MIDI_AFTERTOUCH_NOTE:
                // TODO : handle these cases, and other

            default:
                // Unhandled events
                break;
        }
    }
}


float NoteManager::get_audio(unsigned int time_fs)
{
    Controls& controls = Controls::get_instance();
    float l_audio_value = 0;
    // TODO : multiprocessing
    for(unsigned int i = 0; i < NB_ACTIVE_NOTES; ++i)
    {
        const float l_audio_value_single = m_active_notes_pool[i].get_audio_value(time_fs, controls.get_selected_waveform(), controls.get_sustain());    
        l_audio_value += l_audio_value_single;
        #if (DEBUG_AUDIO == 2)
        printf("%.2f;", l_audio_value_single);
        #endif
    }

    // Prevent audio signal from exceeding amplitude 1
    l_audio_value /= NB_ACTIVE_NOTES;

    #ifdef DEBUG_AUDIO
    printf("%.3f\n", l_audio_value);
    #endif

    return l_audio_value;
}