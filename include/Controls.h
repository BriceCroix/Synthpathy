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
     * @brief The minimum duration between two read_buttons execution in seconds.
     * 
     */
    static constexpr float BUTTONS_READ_TIME_INTERVAL_S = 0.0004;

    /**
     * @brief The minimum duration between two read_buttons execution in number of samples.
     * 
     */
    static constexpr unsigned int BUTTONS_READ_TIME_INTERVAL_FS = BUTTONS_READ_TIME_INTERVAL_S * AUDIO_SAMPLING_FREQUENCY;

    /**
     * @brief The number of times a button must be seen with the same value to be considered stable.
     * 
     */
    static constexpr unsigned int BUTTONS_STABILITY_THRESHOLD = 3;

    /**
     * @brief The indices of each LED signification.
     * These indices correspond to bits in the m_leds member.
     * @{
     */
    static constexpr unsigned int LED_WAVEFORM_SQUARE_ENABLED_IDX = 0;
    static constexpr unsigned int LED_WAVEFORM_SAW_ENABLED_IDX = 1;
    /**@}*/

    /**
     * @brief The function of each ADC channel, of each potentiometer.
     * @{
     */
    static constexpr unsigned int POTENTIOMETER_ATTACK_IDX = 0;
    static constexpr unsigned int POTENTIOMETER_SUSTAIN_IDX = 1;
    static constexpr unsigned int POTENTIOMETER_RESERVED_IDX = 2;
    static constexpr unsigned int POTENTIOMETER_TEXTURE_IDX = 0xFF;
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

    /**
     * @brief The minimum attack duration in seconds.
     * 
     */
    static constexpr float ATTACK_MIN_S = 0.f;

    /**
     * @brief The minimum attack duration in number of samples.
     * 
     */
    static constexpr unsigned ATTACK_MIN_FS = ATTACK_MIN_S * AUDIO_SAMPLING_FREQUENCY;

    /**
     * @brief The maximum attack duration in seconds.
     * 
     */
    static constexpr float ATTACK_MAX_S = 5.f;

    /**
     * @brief The maximum attack duration in number of samples.
     * 
     */
    static constexpr unsigned ATTACK_MAX_FS = ATTACK_MAX_S * AUDIO_SAMPLING_FREQUENCY;

    /**
     * @brief The minimum decay duration in seconds.
     * 
     */
    static constexpr float DECAY_MIN_S = 0.f;

    /**
     * @brief The minimum decay duration in number of samples.
     * 
     */
    static constexpr unsigned DECAY_MIN_FS = DECAY_MIN_S * AUDIO_SAMPLING_FREQUENCY;

    /**
     * @brief The maximum decay duration in seconds.
     * 
     */
    static constexpr float DECAY_MAX_S = 5.f;

    /**
     * @brief The maximum decay duration in number of samples.
     * 
     */
    static constexpr unsigned DECAY_MAX_FS = DECAY_MAX_S * AUDIO_SAMPLING_FREQUENCY;

    /**
     * @brief The minimum sustain value.
     * 
     */
    static constexpr float SUSTAIN_MIN = 0.f;

    /**
     * @brief The maximum sustain value.
     * 
     */
    static constexpr float SUSTAIN_MAX = 1.f;

    /**
     * @brief The minimum release duration in seconds.
     * 
     */
    static constexpr float RELEASE_MIN_S = 1e-3f;

    /**
     * @brief The minimum release duration in number of samples.
     * 
     */
    static constexpr unsigned RELEASE_MIN_FS = RELEASE_MIN_S * AUDIO_SAMPLING_FREQUENCY;

    /**
     * @brief The maximum release duration in seconds.
     * 
     */
    static constexpr float RELEASE_MAX_S = 5.f;

    /**
     * @brief The maximum release duration in number of samples.
     * 
     */
    static constexpr unsigned RELEASE_MAX_FS = RELEASE_MAX_S * AUDIO_SAMPLING_FREQUENCY;
    

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
     * @brief The raw status of the buttons, without debounce.
     * 
     */
    uint32_t m_buttons_raw = 0;

    /**
     * @brief An array to keep track of the stability of the buttons.
     * This counter is incremented each time a button has been seen with the
     * same value.
     */
    unsigned int m_buttons_stability_count[NB_PIN_BUTTON_MATRIX_OUT];

    /**
     * @brief The index of the output pin that is currently high for the button matrix.
     * 
     */
    unsigned int m_button_matrix_out_idx = 0;

    /**
     * @brief The last time at which the read method was called and executed.
     * 
     */
    unsigned int m_button_time_fs_last_read = 0;

    /**
     * @brief The status of each LED, with one bit per LED.
     * 0 being LED turned off, 1 being LED turned on.
     */
    uint32_t m_leds = 0;

    /**
     * @brief The currently selected type of waveform, as a pointer to the actual waveform function.
     * 
     */
    float(*m_selected_waveform)(float, float, float)  = &square_wave;

    /**
     * @brief The additionnal parameter of each waveform function.
     * 
     */
    float m_texture;

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
     * This function returned pointer has signature :
     * float waveform(float time, float frequency, float texture);
     * 
     * @return float(*)(float, float, float) 
     */
    inline float(*get_selected_waveform(void) const)(float, float, float) { return m_selected_waveform; }

    /**
     * @brief Set the currently selected type of waveform.
     * 
     */
    inline void set_selected_waveform(float (*type_waveform)(float, float, float)) { m_selected_waveform = type_waveform; }

    /**
     * @brief Get the texture parameter for the selected waveform.
     * 
     * @return float 
     */
    inline float get_texture() const { return m_texture; }

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
     * One call of this method only reads one row of the button matrix.
     * @param time_fs The time in number of periods of sampling frequency.
     * @return true if at least one button has changed its status.
     * @return false if there is no button status change.
     */
    bool read_buttons(unsigned int time_fs);

    /**
     * @brief Process the buttons status change.
     * 
     */
    void process_buttons();

    /**
     * @brief Called by the ADC after a conversion is complete.
     * Can also be used to set the potentiometers values in software.
     * @param potentiometer_idx The index of the potentiometer.
     * @param value The value of the ADC.
     */
    void set_potentiometer(unsigned int potentiometer_idx, uint8_t value);
};

/**
 * @brief Initializes the GPIO used by the Controls instance.
 * Also initializes the Analog to Digital Converter.
 */
void initialize_controls();

/**
 * @brief The handler function for the ADC end of conversion interrupt.
 * 
 */
void adc_irq_handler();

/**
 * @brief Puts a gpio output to high impedance.
 * This is simply an alias to configure the gpio as input.
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