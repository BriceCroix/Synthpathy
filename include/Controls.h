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
 * This class uses the global midi buffer to push new events.
 */
struct Controls
{
protected:

    Controls(); // Prevent construction
    Controls(const Controls&) = delete; // Prevent construction by copying
    Controls& operator=(const Controls&) = delete; // Prevent assignment


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
    /**@}*/

    /**
     * @brief The number of times a button must be seen with the same value to be considered stable.
     * 
     */
    static constexpr unsigned int NB_STABLE_BUTTON_STATES = 3;

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
    static constexpr MidiByte MIDI_DEFAULT_VELOCITY = 0x7F;


    // Private members ---------------------------------------------------------

    /**
     * @brief The status of each button, with one bit per button.
     * 0 being not pressed and 1 being pressed.
     * Example : bool is_button_5_pressed = (buttons & (1<<5))
     * These buttons states are verified and stable, not bouncing.
     */
    uint32_t m_buttons = 0;

    /**
     * @brief The previous value of m_buttons.
     * 
     */
    uint32_t m_buttons_old = 0;

    /**
     * @brief The past status of the button matrix, per row.
     * Example : m_buttons_row_evolution[1][3] is the status of
     * buttons NB_PIN_BUTTON_MATRIX_IN to 2*NB_PIN_BUTTON_MATRIX_IN-1,
     * as they were 3 read operations in the past.
     */
    uint8_t m_buttons_row_past[NB_PIN_BUTTON_MATRIX_OUT][NB_STABLE_BUTTON_STATES+1];

    /**
     * @brief The index of the output pin that is currently high for the button matrix.
     * 
     */
    unsigned int m_button_matrix_out_idx = 0;

    /**
     * @brief The status of each LED, with one bit per LED.
     * 0 being LED turned off, 1 being LED turned on.
     */
    uint32_t m_leds = 0;

    /**
     * @brief The currently selected type of waveform.
     * 
     */
    TypeWaveform m_selected_waveform = TypeWaveform::square;

    /**
     * @brief The currently selected octave.
     * 
     */
    int m_selected_octave = 3;

    /**
     * @brief The attack value of the ADSR envelope, in number of periods of the audio sampling frequency.
     * 
     */
    unsigned int m_attack_fs;

    /**
     * @brief The decay value of the ADSR envelope, in number of periods of the audio sampling frequency.
     * 
     */
    unsigned int m_decay_fs;

    /**
     * @brief The sustain value between 0 and 1.
     * 
     */
    float m_sustain;

    /**
     * @brief The release value of the ADSR envelope, in number of periods of the audio sampling frequency.
     * 
     */
    unsigned int m_release_fs;


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
     * @brief The attack value of the ADSR envelope, in number of periods of the audio sampling frequency.
     * 
     */
    inline unsigned int get_attack_fs() const { return m_attack_fs; }
    
    /**
     * @brief The decay value of the ADSR envelope, in number of periods of the audio sampling frequency.
     * 
     */
    inline unsigned int get_decay_fs() const { return m_decay_fs; }

    /**
     * @brief The sustain value between 0 and 1.
     * 
     */
    inline float get_sustain() const { return m_sustain; }

    /**
     * @brief The release value of the ADSR envelope, in number of periods of the audio sampling frequency.
     * 
     */
    inline unsigned int get_release_fs() const { return m_release_fs; }


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

/**
 * @brief Puts a gpio output to high impedance.
 * This is simply an alias to configure the gpio as input.
 * Indeed the gpio MUST NOT be pulled up or down for it to be in high impedance.
 * @param gpio gpio number.
 */
inline void gpio_put_high_z(unsigned int gpio)
{
    //gpio_put(gpio, false);
    gpio_set_dir(gpio, GPIO_IN);
}

/**
 * @brief Remove high impedance state from gpio output and put it high.
 * This reconfigures the gpio as output then puts it high.
 * @param gpio gpio number.
 */
inline void gpio_put_1_from_high_z(unsigned int gpio)
{
    gpio_set_dir(gpio, GPIO_OUT);
    gpio_put(gpio, true);
}

#endif //SYNTHPATHY_CONTROLS_H_