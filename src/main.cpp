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
#ifdef DEBUG
#include <stdio.h>
#endif

#include "global.h"
#include "audio_pwm.h"
#include "Controls.h"
#include "NoteManager.h"

int main() {
    // Start by overclocking the controler
    set_sys_clock_khz(SYSTEM_CLOCK_FREQUENCY_KHZ, true);

#ifdef DEBUG
    // Initialize standard output
    stdio_init_all();
    printf("========== Synthpathy started with DEBUG enabled ==========\n");
#endif

    // Initialize origin of time
    g_time_fs = 0;
    // Initialize audio level
    g_audio_level = 0;

    // Initialize everything
    initialize_pwm_audio();
    initialize_controls();
    //TODO : initialize_adc()
    //TODO : initialize_uart()

    // Empty midi buffer
    g_midi_internal_buffer.empty();
    
    // Retrieve the controls instance
    Controls& controls = Controls::get_instance();
    // Retrieve the notes manager
    NoteManager& active_note_manager = NoteManager::get_instance();

    unsigned int l_time_fs;

    while(1)
    {
        // Copy time locally
        l_time_fs = g_time_fs;
        // Check and process new inputs
        if(controls.read_buttons())
        {
            controls.process_buttons();
        }
        // Create, release and update notes
        active_note_manager.update_active_notes(g_time_fs);
        // Compute audio sample
        g_audio_level = active_note_manager.get_audio(g_time_fs);
        // Effects can be added on g_audio_level here

        // Wait for next sample
        do
        {
            tight_loop_contents();// __wfi(); // Wait for Interrupt
        }
        while (l_time_fs == g_time_fs);

        #ifdef DEBUG
        // Check for missed sample
        if(g_time_fs != l_time_fs+1)
        {
            printf("/!\\ MISSED SAMPLE(s) between t=%u and t=%u /!\\\n", l_time_fs, g_time_fs);
        }
        #endif
    }

    // Return is never reached
    return 1;
}