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

#ifndef SYNTHPATHY_GLOBAL_H_
#define SYNTHPATHY_GLOBAL_H_

#include "pico/stdlib.h"
#include "hardware/pwm.h"

#include "CircularBuffer.hpp"
#include "midi.h"
#include "fxpt.h"

// Global constants ------------------------------------------------------------

/**
 * @brief The System clock frequency in kHz, required for overclocking.
 * 
 */
constexpr unsigned int SYSTEM_CLOCK_FREQUENCY_KHZ = 192000U;

/**
 * @brief The number of midi events that can be stored in the midi buffer.
 * 
 */
constexpr unsigned int SIZE_MIDI_BUFFER = 4;

/**
 * @brief The number of bits used by one channel the pwm audio output slice.
 * 
 */
constexpr unsigned int PWM_AUDIO_BIT_DEPTH_PER_CHANNEL = 8;

/**
 * @brief The clock divider used by the pwm audio output.
 * NB : 192MHz / (16*256) = 46875 Hz of sampling frequency. 
 */
constexpr unsigned int PWM_AUDIO_CLK_DIVIDER = 16;

/**
 * @brief The actual sampling frequency used for sample-based computation.
 * Variables given in sampling ticks refer to a number of periods of this frequency.
 */
constexpr unsigned int AUDIO_SAMPLING_FREQUENCY = (SYSTEM_CLOCK_FREQUENCY_KHZ*1000)
    / (PWM_AUDIO_CLK_DIVIDER * (1<<PWM_AUDIO_BIT_DEPTH_PER_CHANNEL));

/**
 * @brief The size of the audio buffer in milliseconds.
 * 10 ms is the just noticeable delay for most humans.
 */
constexpr unsigned int SIZE_AUDIO_BUFFER_MS = 8;

/**
 * @brief The size of the audio buffer in number of samples.
 * 10 ms is the just noticeable delay for most humans.
 */
constexpr unsigned int SIZE_AUDIO_BUFFER = AUDIO_SAMPLING_FREQUENCY * SIZE_AUDIO_BUFFER_MS / 1000;

/**
 * @brief The ADC base clock in Hertz according to pico documentation.
 * A complete conversion takes 96 cycles, so at maximum speed,
 * sampling rate is 48MHz / 96 = 500kHz.
 */
constexpr unsigned int ADC_BASE_CLOCK_HZ = 48e6;

/**
 * @brief The refresh rate of the Controls potentiometers in Hertz.
 * Note that each potentiometer is refreshed at a time, and refresh rate for
 * each potentiometer is then POTENTIOMETERS_REFRESH_RATE_HZ / NB_PIN_POTENTIOMETERS.
 */
constexpr unsigned int POTENTIOMETERS_REFRESH_RATE_HZ =
#if (DEBUG == 3)
    1;
#else
    5000;
#endif

/**
 * @brief The transition duration used by the dynamic filter, in number of samples.
 * The longer the smoother.
 */
constexpr unsigned int DYNAMIC_FILTER_TRANSITION_FS = AUDIO_SAMPLING_FREQUENCY * 0.01;


// Global variables ------------------------------------------------------------

/**
 * @brief The time in number of periods of the audio sampling frequency.
 * 
 */
extern volatile unsigned int g_time_fs;

/**
 * @brief The internal buffer used by Synthpathy to know what note to play and when.
 * 
 */
extern CircularBuffer<MidiEvent, SIZE_MIDI_BUFFER> g_midi_internal_buffer;

/**
 * @brief The analog value of the audio output.
 * 
 */
extern CircularBuffer<fxpt_Q0_31, SIZE_AUDIO_BUFFER> g_output_audio_buffer;


// GPIO pins assignation -------------------------------------------------------

/**
 * @brief The GPIO pins used for the audio PWM output.
 * These pins are connected to PWM Channel 1 (slice 1, channel 0 and 1).
 * PIN_PWM_AUDIO_OUTPUT_L takes bits 0 to 7 of the audio value (Low byte).
 * PIN_PWM_AUDIO_OUTPUT_H takes bits 8 to 15 of the audio value (High byte).
 * @{
 */
constexpr unsigned int PIN_PWM_AUDIO_OUTPUT_L = 2;
constexpr unsigned int PIN_PWM_AUDIO_OUTPUT_H = 3;
/**@}*/

/**
 * @brief The slice associated with the audio PWM pins.
 * NB : equivalent to pwm_gpio_to_slice_num(PIN_PWM_AUDIO_OUTPUT_L).
 */
constexpr unsigned int SLICE_PWM_AUDIO_OUTPUT = 1;

/**
 * @brief The GPIO pin associated with the midi output.
 * This pin is connected to UART1_TX.
 */
constexpr unsigned int PIN_MIDI_OUT = 4;

/**
 * @brief The GPIO pin associated with the midi input.
 * This pin is connected to UART1_RX.
 */
constexpr unsigned int PIN_MIDI_IN = 5;

/**
 * @brief The number of output pins for the button matrix.
 * 
 */
constexpr unsigned int NB_PIN_BUTTON_MATRIX_OUT = 5;

/**
 * @brief The microcontroler output array for the button matrix.
 * NB : 5 outputs and 5 inputs makes for 25 buttons.
 */
constexpr unsigned int PIN_BUTTON_MATRIX_OUT[NB_PIN_BUTTON_MATRIX_OUT] = {6,7,8,9,10};

/**
 * @brief The number of input pins for the button matrix.
 * 
 */
constexpr unsigned int NB_PIN_BUTTON_MATRIX_IN = 5;

/**
 * @brief The microcontroler input array for the button matrix.
 * NB : 5 outputs and 5 inputs makes for 25 buttons.
 */
constexpr unsigned int PIN_BUTTON_MATRIX_IN[NB_PIN_BUTTON_MATRIX_IN] = {11,12,13,14,15};

/**
 * @brief The number of GPIO pins used for the led indications.
 * 
 */
constexpr unsigned int NB_PIN_LEDS = 3;

/**
 * @brief The GPIO pins used for the led indications.
 * 
 */
constexpr unsigned int PIN_LEDS[NB_PIN_LEDS] = {20,21,22};

/**
 * @brief The GPIO pin used by the on-board LED.
 * 
 */
constexpr unsigned int PIN_LED_ONBOARD = 25;

/**
 * @brief The number of GPIO pins used for the potentiometers.
 * 
 */
constexpr unsigned int NB_PIN_POTENTIOMETERS = 3;

/**
 * @brief The GPIO pins used for the potentiometers.
 * These pins are connected to ADC0, ADC1 and ADC2.
 */
constexpr unsigned int PIN_POTENTIOMETERS[NB_PIN_POTENTIOMETERS] = {26,27,28};


#endif //SYNTHPATHY_GLOBAL_H_