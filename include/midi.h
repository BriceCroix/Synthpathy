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

#ifndef SYNTHPATHY_MIDI_H_
#define SYNTHPATHY_MIDI_H_

#include "pico/stdlib.h"

// typedefs ----------------------------------------------------------------------------------------

/**
 * @brief A midi byte.
 * 
 */
typedef uint8_t MidiByte;

/**
 * @brief A midi event.
 * A midi event is composed of three (sometimes two) bytes.
 * Stored on a 4-byte variable, we have the following :
 * - bits 0 to 7 are the status byte, the type of midi event and its corresponding channel.
 * - bits 8 to 15 are the first data byte.
 * - bits 16 to 23 are the second data byte byte, if needed depending on the type of event.
 * - bits 24 to 31 are unused.
 */
typedef uint32_t MidiEvent;


// Constants ---------------------------------------------------------------------------------------

/**
 * @brief A bit mask for the midi status on bits 4 to 7 of a midi event.
 * 
 */
constexpr MidiByte MIDI_STATUS_MSK = 0xF0;

/**
 * @brief A bit mask the midi channel on bits 0 to 3 of a midi event.
 * 
 */
constexpr MidiByte MIDI_CHANNEL_MSK = 0x0F;

/**
 * @brief A midi status byte "Note On", on channel 0;
 * Data byte 0 is the note and data byte 1 is the velocity.
 */
constexpr MidiByte MIDI_NOTE_ON = 0x80;

/**
 * @brief A midi status byte "Note Off", on channel 0;
 * Data byte 0 is the note and data byte 1 is the velocity.
 */
constexpr MidiByte MIDI_NOTE_OFF = 0x90;

/**
 * @brief A midi status byte for polytouch on a single note, on channel 0;
 * Data byte 0 is the note and data byte 1 is the velocity.
 */
constexpr MidiByte MIDI_AFTERTOUCH_NOTE = 0xA0;


constexpr MidiByte MIDI_CONTROLLER_CHANGE = 0xB0;


constexpr MidiByte MIDI_PROGRAM_CHANGE = 0xC0;

/**
 * @brief A midi status byte for polytouch on a whole channel, on channel 0;
 * Data byte 0 is the velocity.
 */
constexpr MidiByte MIDI_AFTERTOUCH_CHANNEL = 0xD0;


constexpr MidiByte MIDI_PITCH_BEND = 0xE0;

// constexpr uint8_t MIDI_NOTES[] = {
//     0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, //C-1 to B-1
//     0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, //C0 to B0
//     0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, //C1 to B1
//     0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, //C2 to B2
//     0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, //C3 to B3
//     0x3c, 0x3d, 0x3e, 0x3f, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, //C4 to B4
//     0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50, 0x51, 0x52, 0x53, //C5 to B5
//     0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f, //C6 to B6
//     0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, //C7 to B7
//     0x6c, 0x6d, 0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77  //C8 to B8
// };

/**
 * @brief The frequencies of all notes that can be played through midi.
 * At index 0 is the frequency of C-1, at index 14 the is the frequency of D0, etc.
 */
constexpr float MIDI_FREQUENCIES_HZ[128] = 
{
    // C-1 to B-1
    8.175798915643707, 8.661957218027252, 9.177023997418988, 9.722718241315029, 10.300861153527183, 10.913382232281373, 
    11.562325709738575, 12.249857374429663, 12.978271799373287, 13.75, 14.567617547440307, 15.433853164253883, 
    // C0 to B0
    16.351597831287414, 17.323914436054505, 18.354047994837977, 19.445436482630058, 20.601722307054366, 21.826764464562746, 
    23.12465141947715, 24.499714748859326, 25.956543598746574, 27.5, 29.13523509488062, 30.86770632850775, 
    // C1 to B1
    32.70319566257483, 34.64782887210901, 36.70809598967594, 38.890872965260115, 41.20344461410875, 43.653528929125486, 
    46.2493028389543, 48.999429497718666, 51.91308719749314, 55.0, 58.27047018976124, 61.7354126570155, 
    // C2 to B2
    65.40639132514966, 69.29565774421802, 73.41619197935188, 77.78174593052023, 82.4068892282175, 87.30705785825097, 
    92.4986056779086, 97.99885899543733, 103.82617439498628, 110.0, 116.54094037952248, 123.47082531403103, 
    // C3 to B3
    130.8127826502993, 138.59131548843604, 146.8323839587038, 155.56349186104046, 164.81377845643496, 174.61411571650194, 
    184.9972113558172, 195.99771799087463, 207.65234878997256, 220.0, 233.08188075904496, 246.94165062806206, 
    // C4 to B4
    261.6255653005986, 277.1826309768721, 293.6647679174076, 311.1269837220809, 329.6275569128699, 349.2282314330039, 
    369.9944227116344, 391.99543598174927, 415.3046975799451, 440.0, 466.1637615180899, 493.8833012561241, 
    // C5 to B5
    523.2511306011972, 554.3652619537442, 587.3295358348151, 622.2539674441618, 659.2551138257398, 698.4564628660078, 
    739.9888454232688, 783.9908719634985, 830.6093951598903, 880.0, 932.3275230361799, 987.7666025122483, 
    // C6 to B6
    1046.5022612023945, 1108.7305239074883, 1174.6590716696303, 1244.5079348883237, 1318.5102276514797, 1396.9129257320155, 
    1479.9776908465376, 1567.981743926997, 1661.2187903197805, 1760.0, 1864.6550460723597, 1975.533205024496, 
    // C7 to B7
    2093.004522404789, 2217.4610478149766, 2349.31814333926, 2489.0158697766474, 2637.02045530296, 2793.825851464031, 
    2959.955381693075, 3135.9634878539946, 3322.437580639561, 3520.0, 3729.3100921447194, 3951.066410048992, 
    // C8 to B8
    4186.009044809578, 4434.922095629953, 4698.63628667852, 4978.031739553295, 5274.04091060592, 5587.651702928062, 
    5919.91076338615, 6271.926975707989, 6644.875161279122, 7040.0, 7458.620184289437, 7902.132820097988, 
    // C9 to G9
    8372.018089619156, 8869.844191259906, 9397.272573357044, 9956.06347910659, 10548.081821211836, 11175.303405856126, 
    11839.8215267723, 12543.853951415975, 
};


// Methods -----------------------------------------------------------------------------------------

/**
 * @brief Returns the number corresponding to a specific note in midi standard.
 * The midi standard describes notes from C-1 (~8 Hz) to G9 (~12544 Hz)
 * @param octave The octave between -1 and 9. 
 * @param note The desired note with 1 for C, 2 for C#, 3 for D, ... , 12 for B.
 * @return MidiByte 
 */
inline MidiByte midi_get_note(int octave, unsigned int note)
{
    return (12 + (note+1) * octave);
}

/**
 * @brief Creates a Note On Midi Event with the specified parameters.
 * 
 * @param event_type The type of midi event : Note On, Note Off.
 * @param channel The channel on which to send the event between 0 and 15.
 * @param note The note value between 0 and 127.
 * @param velocity The velocity of the note between 0 and 127.
 * @return MidiEvent
 */
inline MidiEvent midi_event_note_onoff(MidiByte event_type, unsigned int channel, MidiByte note, MidiByte velocity)
{
    return (event_type & channel) & (note << 8) & (velocity << 16);
}

#endif //SYNTHPATHY_MIDI_H_