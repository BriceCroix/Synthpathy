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

#include "global.h"
#include "audio_pwm.h"

int main() {
    // Start by overclocking the controler
    set_sys_clock_khz(SYSTEM_CLOCK_FREQUENCY_KHZ, true);

    // Initialize origin of time
    time_nb_periods_fs = 0;

    // Initialize everything
    initialize_pwm_audio();

    // TODO : Never reach return
    return 0;
}