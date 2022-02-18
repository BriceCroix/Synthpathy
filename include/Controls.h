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

#ifndef SYNTHPATHY_CONTROLS_H_
#define SYNTHPATHY_CONTROLS_H_

#include "pico/stdlib.h"

#include "CircularBuffer.hpp"
#include "midi.h"
#include "global.h"
#include "waveforms.h"

/**
 * @brief This class owns the GPIOs used by the user.
 * It is a singleton, only one instance can ever be created.
 */
struct Controls
{
protected:

    Controls(); // Prevent construction
    Controls(const Controls&) = delete; // Prevent construction by copying
    Controls& operator=(const Controls&) = delete; // Prevent assignment

    // Private members ---------------------------------------------------------

    /**
     * @brief The status of each button, with one bit per button.
     * 0 being not pressed and 1 being pressed.
     * Example : bool is_button_5_pressed = (buttons & (1<<5))
     */
    uint32_t m_buttons = 0;

    /**
     * @brief The previous value of m_buttons.
     * 
     */
    uint32_t m_buttons_old = 0;

    /**
     * @brief The status of each LED, with one bit per LED.
     * 0 being LED turned off, 1 being LED turned on.
     */
    uint32_t m_leds = 0;

    /**
     * @brief The adress of the buffer where new midi events are to be stored.
     * 
     */
    CircularBuffer<MidiEvent, SIZE_MIDI_BUFFER> *m_midi_buffer;

    /**
     * @brief The currently selected type of waveform.
     * 
     */
    TypeWaveform m_selected_waveform = TypeWaveform::square;

    /**
     * @brief Is midi-through enabled ?
     * Midi-through means that the midi input events are copied to the midi output.
     */
    bool m_midi_trough_enabled = false;

    /**
     * @brief The currently selected octave.
     * 
     */
    unsigned int m_selected_octave = 3;

    // Private constants -------------------------------------------------------

    /**
     * @brief The indices of each button functionnality.
     * These indices correspond to bits in the m_buttons members.
     * @{
     */
    static constexpr unsigned int BUTTON_KEY_C0_IDX = 0;
    static constexpr unsigned int BUTTON_KEY_CS0_IDX = 1;
    static constexpr unsigned int BUTTON_KEY_D0_IDX = 2;
    static constexpr unsigned int BUTTON_KEY_DS0_IDX = 3;
    static constexpr unsigned int BUTTON_KEY_E0_IDX = 4;
    static constexpr unsigned int BUTTON_KEY_F0_IDX = 5;
    static constexpr unsigned int BUTTON_KEY_FS0_IDX = 6;
    static constexpr unsigned int BUTTON_KEY_G0_IDX = 7;
    static constexpr unsigned int BUTTON_KEY_GS0_IDX = 8;
    static constexpr unsigned int BUTTON_KEY_A0_IDX = 9;
    static constexpr unsigned int BUTTON_KEY_AS0_IDX = 10;
    static constexpr unsigned int BUTTON_KEY_B0_IDX = 11;
    static constexpr unsigned int BUTTON_KEY_C1_IDX = 12;
    static constexpr unsigned int BUTTON_OCTAVE_DOWN_IDX = 13;
    static constexpr unsigned int BUTTON_OCTAVE_UP_IDX = 14;
    static constexpr unsigned int BUTTON_WAVEFORM_SELECT_IDX = 15;
    static constexpr unsigned int BUTTON_MIDI_THROUGH_ENABLE_IDX = 16;
    /**@}*/

    /**
     * @brief The indices of each LED signification.
     * These indices correspond to bits in the m_leds member.
     * @{
     */
    static constexpr unsigned int LED_WAVEFORM_SQUARE_ENABLED_IDX = 0;
    /**@}*/

    /**
     * @brief The default channel on which to create midi events.
     * 
     */
    static constexpr MidiByte MIDI_DEFAULT_CHANNEL = 0;

    /**
     * @brief The default velocity value for new note on/off midi events.
     * 
     */
    static constexpr MidiByte MIDI_DEFAULT_VELOCITY = 0x8F;

    // Private methods ---------------------------------------------------------

    /**
     * @brief Update the GPIOs to turn on and off relevant LEDs.
     * 
     */
    void write_leds() const;


public:

    /**
     * @brief Get the Controls instance.
     * 
     */
    inline static Controls& get_instance()
    {
        static Controls instance;
        return instance;
    }

    /**
     * @brief Get the currently selected type of waveform.
     * 
     * @return TypeWaveform 
     */
    inline TypeWaveform get_selected_waveform() const { return m_selected_waveform; }

    /**
     * @brief Reads the buttons and update its internal values accordingly.
     * 
     * @return true if at least one button has changed its status.
     * @return false if there is no button status change.
     */
    bool read_buttons();

    /**
     * @brief Process the buttons status change.
     * 
     */
    void process_buttons();
};

/**
 * @brief Initializes the GPIO used by the Controls instance.
 * 
 */
void initialize_controls();

#endif //SYNTHPATHY_CONTROLS_H_