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

#ifndef SYNTHPATHY_AUDIO_PWM_H_
#define SYNTHPATHY_AUDIO_PWM_H_

/**
 * @brief Initialize pwm audio pin and interrupts for audio use.
 * 
 */
void initialize_pwm_audio();

/**
 * @brief PWM Interrupt Handler which outputs PWM level and keeps track of time. 
 * 
 */
void pwm_wrap_interrupt_handler();

/**
 * @brief Starts the pwm.
 * 
 */
void start_pwm_audio();

/**
 * @brief Stops the pwm.
 * 
 */
void stop_pwm_audio();



#endif //SYNTHPATHY_AUDIO_PWM_H_