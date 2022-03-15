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

#include "ActiveNote.h"

#include <limits>

#ifdef DEBUG
#include <stdio.h>
#endif

ActiveNote::ActiveNote()
{
    m_time_stop_fs = 0; 
}

ActiveNote::ActiveNote(MidiByte _midi_note, float _velocity, unsigned int _time_start_fs, unsigned int _attack_fs, unsigned int _decay_fs) :
    m_midi_note(_midi_note),
    m_velocity(_velocity),
    m_time_start_fs(_time_start_fs),
    m_attack_fs(_attack_fs),
    m_decay_fs(_decay_fs)
{
    m_period = MIDI_PERIODS_S[_midi_note];

    m_time_released_fs = std::numeric_limits<unsigned int>::max();
    m_time_stop_fs = std::numeric_limits<unsigned int>::max();
    #ifdef DEBUG
    printf("ActiveNote(%d, %f, %d, %d, %d)\n", m_midi_note, m_velocity, m_time_start_fs, m_attack_fs, m_decay_fs);
    #endif
}


float ActiveNote::get_ADSR_envelope(unsigned int time_fs, float sustain) const
{
    // While the note has not been released the release time is infinite
    if(time_fs < m_time_released_fs)
    {
        // The time elapsed since the beginning of the note
        const unsigned int l_elapsed = time_fs - m_time_start_fs;


        // If in sustain phase
        if(l_elapsed >= (m_attack_fs + m_decay_fs))
        {
            return sustain;
        }
        else
        {
            // If in decay phase
            if(l_elapsed >= m_attack_fs)
            {
                return 1.f - ((1.f - sustain) * static_cast<float>(l_elapsed - m_attack_fs) / m_decay_fs);
            }
            // If in attack phase
            else
            {
                return static_cast<float>(l_elapsed) / m_attack_fs;
            }
        }
    }
    else
    {
        // Release phase
        return m_ADSR_at_release * (1.f - (static_cast<float>(time_fs - m_time_released_fs) / m_release_fs));
    }
}


void ActiveNote::release(unsigned int time_released_fs, float sustain, unsigned int release)
{
    m_release_fs = release;
    m_ADSR_at_release = get_ADSR_envelope(time_released_fs, sustain);
    m_time_released_fs = time_released_fs;
    m_time_stop_fs = m_time_released_fs + m_release_fs;

    #ifdef DEBUG
    printf("ActiveNote released(%d, %f, %d)\n", m_time_released_fs, sustain, m_release_fs);
    #endif
}


float ActiveNote::get_audio_value(unsigned int time_fs, float(*waveform)(float, float, float), float texture, float sustain) const
{
    if (time_fs >= m_time_stop_fs)
    {
        return 0.f;
    }

    float l_audio_value = waveform(static_cast<float>(time_fs)/AUDIO_SAMPLING_FREQUENCY, m_period, texture);

    l_audio_value *= get_ADSR_envelope(time_fs, sustain) * m_velocity;
    return l_audio_value;
}