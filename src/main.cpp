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
#include "Biquad.h"


int panic();

/**
 * @brief Main application entry point.
 * Should never return.
 * @return int 
 */
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
    g_time_fs = 0;
    // Initialize audio buffer
    g_output_audio_buffer.empty();
    // Initialize midi buffer
    g_midi_internal_buffer.empty();

    // Initialize everything
    initialize_pwm_audio();
    initialize_controls();
    //TODO : initialize_uart()

    #if (defined(DEBUG) || defined(DEBUG_AUDIO))
    gpio_set_dir(PIN_LED_ONBOARD, GPIO_OUT);
    gpio_put(PIN_LED_ONBOARD, true);
    #endif
    
    // Retrieve the controls instance
    Controls& controls = Controls::get_instance();
    // Retrieve the notes manager
    NoteManager& active_note_manager = NoteManager::get_instance();
    // Create the low-pass filter and acknowledge that controls were taken into account
    DynamicBiquad l_filter = DynamicBiquad(Biquad::get_low_pass(controls.get_filter_cutoff(), AUDIO_SAMPLING_FREQUENCY, controls.get_filter_Q()));
    controls.have_filter_params_changed();


    // A local value of time, that can be a little late on the global one
    unsigned int l_time_fs = 0;

    // Pre-compute buffer full of 0's, update time accordingly
    while(!g_output_audio_buffer.is_full())
    {
        g_output_audio_buffer.push(0.f);
        l_time_fs++;
    }
    g_time_fs = l_time_fs;

    // Start the audio output
    start_pwm_audio();

    // Start main loop
    while(1)
    {
        // Check and process new inputs
        if(controls.read_buttons(g_time_fs))
        {
            controls.process_buttons();
        }

        // Create, release and update notes
        active_note_manager.update_active_notes(l_time_fs);

        // Update low-pass filter
        if(controls.have_filter_params_changed())
        {
            l_filter.set_target(
                Biquad::get_low_pass(controls.get_filter_cutoff(), AUDIO_SAMPLING_FREQUENCY, controls.get_filter_Q()),
                DYNAMIC_FILTER_TRANSITION_FS
            );
        }

        // Compute next samples
        #ifndef DEBUG_AUDIO
        while(!g_output_audio_buffer.is_full())
        #endif
        {
            // Compute audio sample
            fxpt_Q0_31 l_audio_sample = active_note_manager.get_audio(l_time_fs);
            // Filter audio sample
            l_audio_sample = l_filter.process(l_audio_sample);

            // Effects can be added on the audio sample here

            #ifdef DEBUG_AUDIO
            printf("%d\n", l_audio_sample);
            #endif

            // Check that there are still samples ready
            if(g_output_audio_buffer.is_empty())
            {
                #ifndef DEBUG_AUDIO
                panic();
                #endif
            }

            // Push audio sample in buffer, without verification since it is not full
            // TODO : protect this push from interrupt (replace by pico/utils/queue)
            g_output_audio_buffer.push_fast(l_audio_sample);

            // Increment local time
            l_time_fs++;
        }
    }

    // Return is never reached
    return 1;
}

/**
 * @brief Synthpathy panic state.
 * 
 * @return int 
 */
int panic()
{
    // Stop audio output
    stop_pwm_audio();

    while(1)
    {
        #if defined(DEBUG)
        printf("\n/!\\/!\\/!\\ Could not compute samples fast enough. Reset needed /!\\/!\\/!\\\n");
        #endif

        // TODO : blink all leds, not only the on-board one
        gpio_put(PIN_LED_ONBOARD, true);
        sleep_ms(1000);
        gpio_put(PIN_LED_ONBOARD, false);
        sleep_ms(1000);
    }

    // Return is never reached
    return 1;
}