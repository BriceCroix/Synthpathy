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

#ifndef SYNTHPATHY_WAVEFORMS_H_
#define SYNTHPATHY_WAVEFORMS_H_

#include "global.h"

enum TypeWaveform
{
    square = 0,
    saw
};

/**
 * @brief Value of a square wave of given parameters.
 * 
 * @param time The time in seconds.
 * @param frequency The frequency in Hz.
 * @param duty_cycle The duty cycle between 0 and 1.
 * @return float 
 */
float square_wave(float time, float frequency, float duty_cycle=0.5f);

/**
 * @brief Value of a rising wave of given parameters.
 * 
 * @param time The time in seconds.
 * @param frequency The frequency in Hz.
 * @return float 
 */
float saw_wave(float time, float frequency);

#endif //SYNTHPATHY_WAVEFORMS_H_