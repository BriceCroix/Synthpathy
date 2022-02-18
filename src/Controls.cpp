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

#include "Controls.h"
#include "global.h"
#include "midi.h"

#include "pico/stdlib.h"

Controls::Controls()
{
    // Initialize all buttons as not pressed
    m_buttons = 0;
    m_buttons_old = 0;
    // Initialize all leds as turned off
    m_leds = 0;

    // New midi events are to be stored in the internal buffer
    m_midi_buffer = &g_midi_internal_buffer;

    m_selected_octave = 3;

    m_selected_waveform = TypeWaveform::square;
}

bool Controls::read_buttons()
{
    m_buttons_old = m_buttons;
    m_buttons = 0;

    for(unsigned int button_matrix_out_idx = 0; button_matrix_out_idx < NB_PIN_BUTTON_MATRIX_OUT; ++button_matrix_out_idx)
    {
        unsigned int l_gpio_status;

        // TODO : unroll this loop, maybe use gpio_get_all for more efficiency

        // Set one output to high, then read each input, so that each pair of input-output is driven by a different button
        gpio_put(PIN_BUTTON_MATRIX_OUT[button_matrix_out_idx], true);
        for(unsigned int button_matrix_in_idx = 0; button_matrix_in_idx < NB_PIN_BUTTON_MATRIX_IN; ++button_matrix_in_idx)
        {
            // The following is done because gpio_get does not ensure 1 is returned in case of high state
            l_gpio_status = gpio_get(PIN_BUTTON_MATRIX_IN[button_matrix_in_idx]) ? 1 : 0;
            // Unset relevant bit if button is pressed
            m_buttons |= (l_gpio_status << (button_matrix_out_idx * NB_PIN_BUTTON_MATRIX_OUT + button_matrix_in_idx)); 
        }
    }

    // Return true if at least one button has changed
    return m_buttons == m_buttons_old;
}

void Controls::process_buttons()
{
    //TODO : Update LED array
    bool l_leds_need_refresh = false;

    // Process the key buttons, this loop only works if the keys are next to each other in the m_buttons variables
    for(unsigned int i = BUTTON_KEY_C0_IDX; i <= BUTTON_KEY_C1_IDX; ++i)
    {
        // If button is pressed and was not pressed before
        if((m_buttons & (1<<i)) && ~(m_buttons_old & (1<<i)))
        {
            m_midi_buffer->push(midi_event_note_onoff(
                MIDI_NOTE_ON, MIDI_DEFAULT_CHANNEL, midi_get_note(m_selected_octave, i-BUTTON_KEY_C0_IDX+1), MIDI_DEFAULT_VELOCITY));
        }
        // If button was pressed before and is not pressed anymore
        else if(~(m_buttons & (1<<i)) && (m_buttons_old & (1<<i)))
        {
            m_midi_buffer->push(midi_event_note_onoff(
                MIDI_NOTE_OFF, MIDI_DEFAULT_CHANNEL, midi_get_note(m_selected_octave, i-BUTTON_KEY_C0_IDX+1), MIDI_DEFAULT_VELOCITY));
        }
    }

    // Process octave change, and assume octave up and down are not pressed at the same time
    if((m_buttons & (1<<BUTTON_OCTAVE_DOWN_IDX)) && ~(m_buttons_old & (1<<BUTTON_OCTAVE_DOWN_IDX)))
    {
        if(m_selected_octave > -1) m_selected_octave--;
    }
    else if((m_buttons & (1<<BUTTON_OCTAVE_UP_IDX)) && ~(m_buttons_old & (1<<BUTTON_OCTAVE_UP_IDX)))
    {
        if(m_selected_octave < 8) m_selected_octave++;
    }

    // Process waveform change
    if((m_buttons & (1<<BUTTON_WAVEFORM_SELECT_IDX)) && ~(m_buttons_old & (1<<BUTTON_WAVEFORM_SELECT_IDX)))
    {
        if(m_selected_waveform == TypeWaveform::square)
        {
            m_selected_waveform = TypeWaveform::saw;
            m_leds &= ~(1<<LED_WAVEFORM_SQUARE_ENABLED_IDX);
        }
        // There are only two waveforms possible
        else
        {
            m_selected_waveform = TypeWaveform::square;
            m_leds |= (1<<LED_WAVEFORM_SQUARE_ENABLED_IDX);
        }
        l_leds_need_refresh = true;
    }

    // Process midi-through enable button
    if((m_buttons & (1<<BUTTON_MIDI_THROUGH_ENABLE_IDX)) && ~(m_buttons_old & (1<<BUTTON_MIDI_THROUGH_ENABLE_IDX)))
    {
        m_midi_trough_enabled = !m_midi_trough_enabled;
    }

    // Finally update leds if necessary
    if(l_leds_need_refresh)
    {
        write_leds();
    }

}

void Controls::write_leds() const
{
    // Put each LED GPIO in its corresponding internal state
    for(unsigned int led_idx = 0; led_idx < NB_PIN_LEDS; ++led_idx)
    {
        gpio_put(PIN_LEDS[led_idx], m_leds & (1<<led_idx));
    }
}

void initialize_controls()
{
    // Setup the outputs for the button matrix
    for(unsigned int i = 0; i < NB_PIN_BUTTON_MATRIX_OUT; ++i)
    {
        gpio_init(PIN_BUTTON_MATRIX_OUT[i]);
        gpio_set_dir(PIN_BUTTON_MATRIX_OUT[i], GPIO_OUT);
        gpio_put(PIN_BUTTON_MATRIX_OUT[i], false);
    }

    // Setup the pulled-down inputs for the button matrix
    // This means that the inputs will read low by default
    for(unsigned int i = 0; i < NB_PIN_BUTTON_MATRIX_IN; ++i)
    {
        gpio_init(PIN_BUTTON_MATRIX_IN[i]);
        gpio_set_dir(PIN_BUTTON_MATRIX_IN[i], GPIO_IN);
        gpio_pull_down(PIN_BUTTON_MATRIX_IN[i]);
    }

    // Setup LEDs pins as output
    for(unsigned int i = 0; i < NB_PIN_LEDS; ++i)
    {
        gpio_init(PIN_LEDS[i]);
        gpio_set_dir(PIN_LEDS[i], GPIO_OUT);
    }

    // Setup On-board LED pin as output
    gpio_init(PIN_LED_ONBOARD);
    gpio_set_dir(PIN_LED_ONBOARD, GPIO_OUT);

    // Get the Controls instance in order to initialize it
    Controls::get_instance();
}