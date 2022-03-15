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
 * @brief The periods of all notes that can be played through midi.
 * At index 0 is the period of C-1, at index 14 the is the period of D0, etc.
 */
constexpr float MIDI_PERIODS_S[128] = 
{
    // C-1 to B-1
    0.12231220585508576, 0.11544734923405088, 0.10896778740921317, 0.102851895445316, 0.09707926212145707, 0.09163062181053622, 
    0.08648779018201608, 0.08163360351340897, 0.07705186140794874, 0.07272727272727272, 0.06864540455866863, 0.06479263404657011, 
    // C0 to B0
    0.06115610292754288, 0.05772367461702544, 0.05448389370460659, 0.051425947722658, 0.04853963106072853, 0.04581531090526811, 
    0.04324389509100804, 0.040816801756704484, 0.03852593070397437, 0.03636363636363636, 0.03432270227933431, 0.03239631702328507, 
    // C1 to B1
    0.03057805146377144, 0.02886183730851272, 0.027241946852303304, 0.025712973861329, 0.024269815530364256, 0.022907655452634058, 
    0.02162194754550402, 0.020408400878352235, 0.019262965351987186, 0.01818181818181818, 0.017161351139667155, 0.016198158511642535, 
    // C2 to B2
    0.01528902573188572, 0.01443091865425636, 0.013620973426151652, 0.0128564869306645, 0.012134907765182128, 0.011453827726317029, 
    0.01081097377275201, 0.010204200439176117, 0.009631482675993593, 0.00909090909090909, 0.008580675569833577, 0.008099079255821266, 
    // C3 to B3
    0.00764451286594286, 0.00721545932712818, 0.006810486713075825, 0.00642824346533225, 0.006067453882591066, 0.005726913863158514, 
    0.005405486886376005, 0.00510210021958806, 0.0048157413379967965, 0.004545454545454545, 0.004290337784916789, 0.004049539627910633, 
    // C4 to B4
    0.00382225643297143, 0.00360772966356409, 0.0034052433565379125, 0.003214121732666125, 0.003033726941295533, 0.002863456931579257, 
    0.0027027434431880024, 0.00255105010979403, 0.0024078706689983982, 0.0022727272727272726, 0.0021451688924583943, 0.0020247698139553164, 
    // C5 to B5
    0.001911128216485715, 0.001803864831782045, 0.0017026216782689563, 0.0016070608663330626, 0.0015168634706477664, 0.0014317284657896286, 
    0.0013513717215940012, 0.001275525054897015, 0.0012039353344991991, 0.0011363636363636363, 0.0010725844462291972, 0.0010123849069776582, 
    // C6 to B6
    0.0009555641082428575, 0.0009019324158910225, 0.0008513108391344781, 0.0008035304331665313, 0.0007584317353238832, 0.0007158642328948143, 
    0.0006756858607970006, 0.0006377625274485074, 0.0006019676672495996, 0.0005681818181818182, 0.0005362922231145986, 0.0005061924534888292, 
    // C7 to B7
    0.00047778205412142875, 0.00045096620794551125, 0.0004256554195672391, 0.00040176521658326564, 0.0003792158676619415, 0.00035793211644740715, 
    0.0003378429303985003, 0.00031888126372425367, 0.0003009838336247998, 0.0002840909090909091, 0.0002681461115572993, 0.0002530962267444146, 
    // C8 to B8
    0.00023889102706071437, 0.00022548310397275563, 0.00021282770978361956, 0.00020088260829163282, 0.00018960793383097075, 0.00017896605822370358, 
    0.00016892146519925015, 0.00015944063186212683, 0.0001504919168123999, 0.00014204545454545454, 0.00013407305577864967, 0.00012654811337220725, 
    // C9 to G9
    0.00011944551353035719, 0.00011274155198637781, 0.00010641385489180974, 0.00010044130414581641, 9.480396691548542e-05, 8.948302911185177e-05, 
    8.446073259962508e-05, 7.972031593106344e-05, 
};


// Methods -----------------------------------------------------------------------------------------

/**
 * @brief Returns the number corresponding to a specific note in midi standard.
 * The midi standard describes notes from C-1 (~8 Hz) to G9 (~12544 Hz)
 * @param octave The octave between -1 and 9. 
 * @param note The desired note with 0 for C, 1 for C#, 4 for D, ... , 11 for B.
 * @return MidiByte 
 */
inline MidiByte midi_get_note(int octave, unsigned int note)
{
    return ((12 * (octave+1)) + note);
}

/**
 * @brief Creates a Note On/Off Midi Event with the specified parameters.
 * 
 * @param event_type The type of midi event : Note On, Note Off.
 * @param channel The channel on which to send the event between 0 and 15.
 * @param note The note value between 0 and 127.
 * @param velocity The velocity of the note between 0 and 127.
 * @return MidiEvent
 */
inline MidiEvent midi_event_note_onoff(MidiByte event_type, unsigned int channel, MidiByte note, MidiByte velocity)
{
    return (event_type | channel) | (note << 8) | (velocity << 16);
}

#endif //SYNTHPATHY_MIDI_H_