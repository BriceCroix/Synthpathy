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

#include "pico/float.h"


/**
 * @brief Value of a square wave of given parameters.
 * 
 * @param time The time in number of samples.
 * @param period The period in number of samples.
 * @param duty_cycle The duty cycle between 0 and 1.
 * @return float 
 */
inline float square_wave(unsigned int time, unsigned int period, float duty_cycle = 0.5f)
{
    return ((time % period) < (period * duty_cycle)) ? 1.0f : -1.0f;
}

/**
 * @brief Value of a rising wave of given parameters.
 * 
 * @param time The time in number of samples.
 * @param period The period in number of samples.
 * @param reserved Unused parameter.
 * @return float 
 */
inline float saw_wave(unsigned int time, unsigned int period, float reserved = 0.f)
{
    return (2 * (time % period) / period) - 1.f;
}


#endif //SYNTHPATHY_WAVEFORMS_H_