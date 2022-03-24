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
#include <limits>

#include "fxpt.h"


/**
 * @brief Value of a square wave of given parameters.
 * 
 * @param time The time in number of samples.
 * @param period The period in number of samples.
 * @param duty_cycle The duty cycle between 0 and 1.
 * @return fxpt_Q0_31 
 */
inline fxpt_Q0_31 square_wave(unsigned int time, unsigned int period, float duty_cycle = 0.5f)
{
    return ((time % period) < (period * duty_cycle)) ? std::numeric_limits<fxpt_Q0_31>::max() : std::numeric_limits<fxpt_Q0_31>::min();
}

/**
 * @brief Value of a rising wave of given parameters.
 * 
 * @param time The time in number of samples.
 * @param period The period in number of samples.
 * @param reserved Unused parameter.
 * @return fxpt_Q0_31 
 */
inline fxpt_Q0_31 saw_wave(unsigned int time, unsigned int period, float reserved = 0.f)
{
    // return 2. * ((static_cast<float>(time % period) / period) - 0.5f);

    // longest period takes about 13 bits, it is safe to convert to UQ16.16
    return 2 * (static_cast<fxpt_Q0_31>(fxpt_convert_n(fxpt_dec_step(time % period, 16) / period, 16, 31)) - fxpt_Q0_31(1<<30));
}


#endif //SYNTHPATHY_WAVEFORMS_H_