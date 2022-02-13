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

#include "audio_pwm.h"
#include "global.h"

#include "pico/stdlib.h"
#include "hardware/irq.h"

void initialize_pwm_audio()
{
    // Initialize and link to PWM the two relevant pins
    gpio_init(PIN_PWM_AUDIO_OUTPUT_L);
    gpio_init(PIN_PWM_AUDIO_OUTPUT_H);
    gpio_set_function(PIN_PWM_AUDIO_OUTPUT_L, GPIO_FUNC_PWM);
    gpio_set_function(PIN_PWM_AUDIO_OUTPUT_H, GPIO_FUNC_PWM);
    // Set handle function
    irq_set_exclusive_handler(PWM_IRQ_WRAP, pwm_interrupt_handler); 
    irq_set_enabled(PWM_IRQ_WRAP, true);

    // Setup PWM for audio output, see global.h for explanation
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, PWM_AUDIO_CLK_DIVIDER); 
    pwm_config_set_wrap(&config, (1<<PWM_AUDIO_BIT_DEPTH_PER_CHANNEL)-1);
    pwm_init(SLICE_PWM_AUDIO_OUTPUT, &config, true);

    // TODO : use slice and channel rather than pin
    pwm_set_gpio_level(PIN_PWM_AUDIO_OUTPUT_L, 0);
    pwm_set_gpio_level(PIN_PWM_AUDIO_OUTPUT_H, 0);
}

void pwm_interrupt_handler()
{
    // Clear IRQ flag
    pwm_clear_irq(SLICE_PWM_AUDIO_OUTPUT);
    // Increment time
    time_nb_periods_fs++;

    // TODO : use slice and channel rather than pin
    pwm_set_gpio_level(PIN_PWM_AUDIO_OUTPUT_L, 0);
    pwm_set_gpio_level(PIN_PWM_AUDIO_OUTPUT_H, 0);
}