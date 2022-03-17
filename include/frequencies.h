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

#ifndef SYNTHPATHY_FREQUENCIES_H_
#define SYNTHPATHY_FREQUENCIES_H_

#include "global.h"

/**
 * @brief The periods of all notes that can be played through midi in number of samples.
 * At index 0 is the period of C-1, at index 14 the is the period of D0, etc.
 */
constexpr unsigned int MIDI_PERIODS_FS[128] = 
{
    // C-1 to B-1
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/8.175798915643707), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/8.661957218027252), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/9.177023997418988), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/9.722718241315029), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/10.300861153527183), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/10.913382232281373), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/11.562325709738575), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/12.249857374429663), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/12.978271799373287), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/13.75), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/14.567617547440307), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/15.433853164253883), 
    // C0 to B0
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/16.351597831287414), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/17.323914436054505), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/18.354047994837977), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/19.445436482630058), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/20.601722307054366), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/21.826764464562746), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/23.12465141947715), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/24.499714748859326), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/25.956543598746574), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/27.5), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/29.13523509488062), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/30.86770632850775), 
    // C1 to B1
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/32.70319566257483), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/34.64782887210901), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/36.70809598967594), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/38.890872965260115), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/41.20344461410875), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/43.653528929125486), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/46.2493028389543), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/48.999429497718666), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/51.91308719749314), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/55.0), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/58.27047018976124), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/61.7354126570155), 
    // C2 to B2
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/65.40639132514966), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/69.29565774421802), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/73.41619197935188), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/77.78174593052023), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/82.4068892282175), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/87.30705785825097), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/92.4986056779086), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/97.99885899543733), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/103.82617439498628), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/110.0), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/116.54094037952248), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/123.47082531403103), 
    // C3 to B3
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/130.8127826502993), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/138.59131548843604), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/146.8323839587038), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/155.56349186104046), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/164.81377845643496), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/174.61411571650194), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/184.9972113558172), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/195.99771799087463), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/207.65234878997256), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/220.0), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/233.08188075904496), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/246.94165062806206), 
    // C4 to B4
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/261.6255653005986), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/277.1826309768721), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/293.6647679174076), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/311.1269837220809), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/329.6275569128699), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/349.2282314330039), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/369.9944227116344), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/391.99543598174927), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/415.3046975799451), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/440.0), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/466.1637615180899), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/493.8833012561241), 
    // C5 to B5
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/523.2511306011972), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/554.3652619537442), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/587.3295358348151), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/622.2539674441618), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/659.2551138257398), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/698.4564628660078), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/739.9888454232688), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/783.9908719634985), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/830.6093951598903), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/880.0), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/932.3275230361799), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/987.7666025122483), 
    // C6 to B6
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/1046.5022612023945), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/1108.7305239074883), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/1174.6590716696303), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/1244.5079348883237), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/1318.5102276514797), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/1396.9129257320155), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/1479.9776908465376), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/1567.981743926997), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/1661.2187903197805), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/1760.0), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/1864.6550460723597), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/1975.533205024496), 
    // C7 to B7
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/2093.004522404789), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/2217.4610478149766), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/2349.31814333926), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/2489.0158697766474), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/2637.02045530296), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/2793.825851464031), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/2959.955381693075), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/3135.9634878539946), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/3322.437580639561), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/3520.0), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/3729.3100921447194), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/3951.066410048992), 
    // C8 to B8
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/4186.009044809578), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/4434.922095629953), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/4698.63628667852), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/4978.031739553295), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/5274.04091060592), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/5587.651702928062), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/5919.91076338615), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/6271.926975707989), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/6644.875161279122), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/7040.0), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/7458.620184289437), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/7902.132820097988), 
    // C9 to G9
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/8372.018089619156), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/8869.844191259906), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/9397.272573357044), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/9956.06347910659), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/10548.081821211836), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/11175.303405856126), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/11839.8215267723), 
    static_cast<unsigned int>(AUDIO_SAMPLING_FREQUENCY*1.f/12543.853951415975), 
};

#endif //SYNTHPATHY_FREQUENCIES_H_