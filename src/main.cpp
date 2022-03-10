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

#include "pico/stdlib.h"
#include "hardware/sync.h"

#if (defined(DEBUG) || defined(DEBUG_AUDIO))
#if defined(DEBUG)
#pragma message "Compiling with DEBUG enabled"
#endif
#if defined(DEBUG_AUDIO)
#pragma message "Compiling with DEBUG_AUDIO enabled"
#endif
#include <stdio.h>
#endif

#ifdef TESTS_ONLY
#pragma message "Compiling with TESTS_ONLY enabled"
#include "tests.h"
#endif

#include "global.h"
#include "audio_pwm.h"
#include "Controls.h"
#include "NoteManager.h"

int main() {
    // Start by overclocking the controler
    set_sys_clock_khz(SYSTEM_CLOCK_FREQUENCY_KHZ, true);

    #ifdef TESTS_ONLY
    perform_tests();
    #endif

    #if (defined(DEBUG) || defined(DEBUG_AUDIO))
    // Initialize standard output
    stdio_init_all();
    printf("========== Synthpathy started ==========\n");
    #endif

    // Initialize origin of time
    g_time_fs = SIZE_AUDIO_BUFFER;
    // Initialize audio level with samples ready to be popped
    g_output_audio_buffer.empty();
    g_output_audio_buffer.fill(0.f);
    // Initialize midi buffer
    g_midi_internal_buffer.empty();

    // Initialize everything
    initialize_pwm_audio();
    initialize_controls();
    //TODO : initialize_adc()
    //TODO : initialize_uart()

    #if (defined(DEBUG) || defined(DEBUG_AUDIO))
    gpio_put(PIN_LED_ONBOARD, true);
    #endif
    
    // Retrieve the controls instance
    Controls& controls = Controls::get_instance();
    // Retrieve the notes manager
    NoteManager& active_note_manager = NoteManager::get_instance();

    // A local value of time, that can be a little late on the global one
    unsigned int l_time_fs = 0;

    // Start the audio output
    start_pwm_audio();

    // Start main loop
    while(1)
    {
        // Check and process new inputs
        if(controls.read_buttons())
        {
            controls.process_buttons();
        }
        // Create, release and update notes
        active_note_manager.update_active_notes(g_time_fs);

        // Compute next samples
        while(l_time_fs != g_time_fs)
        {
            // Compute audio sample
            const float l_audio_sample = active_note_manager.get_audio(l_time_fs);

            // Effects can be added on the audio sample here

            #ifdef DEBUG_AUDIO
            printf("%f\n", l_audio_sample);
            #endif

            #if (defined(DEBUG) || defined(DEBUG_AUDIO))
            if(g_output_audio_buffer.is_empty())
            {
                printf("\n/!\\/!\\/!\\ Could not compute samples fast enough. Reset needed /!\\/!\\/!\\\n");
            }
            #endif

            // Push audio sample in buffer
            g_output_audio_buffer.push(l_audio_sample);

            // Increment time
            l_time_fs++;
        }
    }

    // Return is never reached
    return 1;
}