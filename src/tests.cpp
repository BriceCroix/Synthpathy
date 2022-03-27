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

#include "tests.h"

#include "pico/stdlib.h"
#include <stdio.h>

#include "Controls.h"
#include "audio_pwm.h"
#include "global.h"
#include "NoteManager.h"
#include "waveforms.h"
#include "Biquad.h"

void perform_tests()
{
    stdio_init_all();
    g_midi_internal_buffer.empty();

    initialize_pwm_audio();
    initialize_controls();
    
    Controls& controls = Controls::get_instance();
    NoteManager& note_manager = NoteManager::get_instance();

    unsigned int t_us;
    unsigned int duration_ns;
    
    while(1)
    {
        printf("\n\n==================== Synthpathy tests ====================\n\n");

        t_us = time_us_32();
        for(unsigned int i = 0; i < NB_TESTS; ++i)
        {
            controls.read_buttons(10*i);
        }
        t_us = time_us_32() - t_us;
        duration_ns = t_us * 1000 / NB_TESTS;
        printf("controls.read_buttons() : %u ns\n", duration_ns);

        /*----------------------------------------------------------------------------------------*/

        t_us = time_us_32();
        for(unsigned int i = 0; i < NB_TESTS; ++i)
        {
            controls.process_buttons();
        }
        t_us = time_us_32() - t_us;
        duration_ns = t_us * 1000 / NB_TESTS;
        printf("controls.process_buttons() : %u ns\n", duration_ns);

        /*----------------------------------------------------------------------------------------*/

        t_us = time_us_32();
        for(unsigned int i = 0; i < NB_TESTS; ++i)
        {
            note_manager.update_active_notes(42);
        }
        t_us = time_us_32() - t_us;
        duration_ns = t_us * 1000 / NB_TESTS;
        printf("note_manager.update_active_notes(...) [Empty midi queue] : %u ns\n", duration_ns);

        /*----------------------------------------------------------------------------------------*/

        t_us = time_us_32();
        for(unsigned int i = 0; i < NB_TESTS; ++i)
        {
            // Push an event to pop
            g_midi_internal_buffer.push(midi_event_note_onoff(
                (i%2 == 0) ? MIDI_NOTE_ON : MIDI_NOTE_OFF,
                0,
                (i/2) % 128,
                0x7F
            ));
            // Pop event
            note_manager.update_active_notes(42);
        }
        t_us = time_us_32() - t_us;
        duration_ns = t_us * 1000 / NB_TESTS;
        printf("note_manager.update_active_notes(...) [push + Not empty midi queue] : %u ns\n", duration_ns);

        /*----------------------------------------------------------------------------------------*/

        t_us = time_us_32();
        ActiveNote active_note(0, fxpt_Q0_31(1<<30), 0, 500, 500);
        for(unsigned int i = 0; i < NB_TESTS; ++i)
        {
            active_note.get_audio_value(i%1000, &square_wave, fxpt_Q0_31(1<<30), fxpt_Q0_31(1<<30));
        }
        t_us = time_us_32() - t_us;
        duration_ns = t_us * 1000 / NB_TESTS;
        printf("active_note.get_audio_value(...) [square wave, alive] : %u ns\n", duration_ns);

        /*----------------------------------------------------------------------------------------*/

        t_us = time_us_32();
        for(unsigned int i = 0; i < NB_TESTS; ++i)
        {
            active_note.get_audio_value(i%1000, &saw_wave, fxpt_Q0_31(0), fxpt_Q0_31(1<<30));
        }
        t_us = time_us_32() - t_us;
        duration_ns = t_us * 1000 / NB_TESTS;
        printf("active_note.get_audio_value(...) [saw wave, alive] : %u ns\n", duration_ns);

        /*----------------------------------------------------------------------------------------*/

        active_note.kill();
        t_us = time_us_32();
        for(unsigned int i = 0; i < NB_TESTS; ++i)
        {
            active_note.get_audio_value(i%1000, &square_wave, fxpt_Q0_31(1<<30), fxpt_Q0_31(1<<30));
        }
        t_us = time_us_32() - t_us;
        duration_ns = t_us * 1000 / NB_TESTS;
        printf("active_note.get_audio_value(...) [square wave, killed] : %u ns\n", duration_ns);

        /*----------------------------------------------------------------------------------------*/

        constexpr unsigned int NB_ACTIVE_NOTES = 4;
        // Load Notes
        for(unsigned int i = 0; i < NB_ACTIVE_NOTES; i++)
        {
            g_midi_internal_buffer.push(midi_event_note_onoff(MIDI_NOTE_ON, 0, 12*i, 0x7F));
            note_manager.update_active_notes(0);
        }
        unsigned int attack = controls.get_attack_fs();
        unsigned int decay = controls.get_attack_fs();
        unsigned int attack_decay = attack + decay;

        controls.set_selected_waveform(&square_wave);
        // Attack and decay values are not properly handled

        t_us = time_us_32();
        for(unsigned int i = 0; i < NB_TESTS; ++i)
        {
            // Trying to force attack and decay phases, decay being the most complicated one to compute
            note_manager.get_audio(i%attack_decay);
        }
        t_us = time_us_32() - t_us;
        duration_ns = t_us * 1000 / NB_TESTS;
        printf("note_manager.get_audio(...) [Full pool, square] : %u ns\n", duration_ns);

        controls.set_selected_waveform(&saw_wave);

        t_us = time_us_32();
        for(unsigned int i = 0; i < NB_TESTS; ++i)
        {
            
            note_manager.get_audio(i%attack_decay);
        }
        t_us = time_us_32() - t_us;
        duration_ns = t_us * 1000 / NB_TESTS;
        printf("note_manager.get_audio(...) [Full pool, saw] : %u ns\n", duration_ns);

        // Release notes
        for(unsigned int i = 0; i < NB_ACTIVE_NOTES; i++)
        {
            g_midi_internal_buffer.push(midi_event_note_onoff(MIDI_NOTE_OFF, 0, 12*i, 0x7F));
            note_manager.update_active_notes(0);
        }

        /*----------------------------------------------------------------------------------------*/

        Biquad l_filter;

        t_us = time_us_32();
        for(unsigned int i = 0; i < NB_TESTS; ++i)
        {
            l_filter = Biquad::get_low_pass(i, AUDIO_SAMPLING_FREQUENCY, M_SQRT1_2);;
        }
        t_us = time_us_32() - t_us;
        duration_ns = t_us * 1000 / NB_TESTS;
        printf("Biquad.get_low_pass(...) : %u ns\n", duration_ns);

        /*----------------------------------------------------------------------------------------*/

        l_filter = Biquad::get_low_pass(500., AUDIO_SAMPLING_FREQUENCY, M_SQRT1_2);

        t_us = time_us_32();
        for(unsigned int i = 0; i < NB_TESTS; ++i)
        {
            l_filter.process(i);
        }
        t_us = time_us_32() - t_us;
        duration_ns = t_us * 1000 / NB_TESTS;
        printf("Biquad.process(...) : %u ns\n", duration_ns);

        /*----------------------------------------------------------------------------------------*/

        DynamicBiquad l_dynamic_filter = DynamicBiquad(Biquad::get_low_pass(500., AUDIO_SAMPLING_FREQUENCY, M_SQRT1_2));
        l_dynamic_filter.set_target(Biquad::get_low_pass(1000., AUDIO_SAMPLING_FREQUENCY, 1.));

        t_us = time_us_32();
        for(unsigned int i = 0; i < NB_TESTS; ++i)
        {
            l_dynamic_filter.set_target(l_filter);
        }
        t_us = time_us_32() - t_us;
        duration_ns = t_us * 1000 / NB_TESTS;
        printf("DynamicBiquad.set_target(...) : %u ns\n", duration_ns);

        /*----------------------------------------------------------------------------------------*/

        l_dynamic_filter.set_target(Biquad::get_low_pass(1000., AUDIO_SAMPLING_FREQUENCY, 1.), NB_TESTS);

        t_us = time_us_32();
        for(unsigned int i = 0; i < NB_TESTS; ++i)
        {
            l_dynamic_filter.process(i);
        }
        t_us = time_us_32() - t_us;
        duration_ns = t_us * 1000 / NB_TESTS;
        printf("DynamicBiquad.process(...) [transitionning]: %u ns\n", duration_ns);

        /*----------------------------------------------------------------------------------------*/

        t_us = time_us_32();
        for(unsigned int i = 0; i < NB_TESTS; ++i)
        {
            l_dynamic_filter.process(i);
        }
        t_us = time_us_32() - t_us;
        duration_ns = t_us * 1000 / NB_TESTS;
        printf("DynamicBiquad.process(...) [not transitionning]: %u ns\n", duration_ns);

        /*----------------------------------------------------------------------------------------*/

        printf("\n====================   End of tests   ====================\n\n");
        sleep_ms(5000);
    }
}