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
#include "hardware/adc.h"
#include "hardware/irq.h"

#include <limits>
#include <math.h>

#ifdef DEBUG
#include <stdio.h>
#endif


Controls::Controls()
{
    // Initialize all buttons as not pressed
    m_buttons = 0;
    m_buttons_old = 0;
    // Initalize all buttons as instable
    for(unsigned int row = 0; row < NB_PIN_BUTTON_MATRIX_OUT; ++row)
    {
        m_buttons_stability_count[row] = 0;
    }
    // Initialize all leds as turned off
    m_leds = 0;
    // The first button matrix pin to be high
    m_button_matrix_out_idx = 0;

    // Default selection
    m_selected_octave = 3;
    m_selected_waveform = &square_wave;
    m_texture = fxpt_Q0_31(1<<30);
    m_leds |= (1<<LED_WAVEFORM_SQUARE_ENABLED_IDX);

    // Default ADSR
    m_attack_fs = (ATTACK_MAX_FS - ATTACK_MIN_FS) / 2;
    m_decay_fs = 0.1 * AUDIO_SAMPLING_FREQUENCY; // 0.1 second
    m_sustain = (SUSTAIN_MAX - SUSTAIN_MIN) / 2;
    m_release_fs = (RELEASE_MAX_FS - RELEASE_MIN_FS) / 2;

    // Initialize filter parameters
    m_filter_cutoff = sqrtf(FILTER_CUTOFF_MAX_HZ * FILTER_CUTOFF_MIN_HZ);
    m_filter_cutoff_old = m_filter_cutoff;
    m_filter_Q = M_SQRT1_2;
    m_filter_Q_old = m_filter_Q;

    // Get ready for first button matrix read operation
    gpio_put_1_from_high_z(PIN_BUTTON_MATRIX_OUT[m_button_matrix_out_idx]);
    // Turn on leds
    write_leds();
}


bool Controls::read_buttons(unsigned int time_fs)
{
    // This read operation could be handled by the PIO in order not to update the pin 1 time out of NB_PIN_BUTTON_MATRIX_OUT
    // Using charlieplexing could also provide a lot more buttons if needed (N^2-N instead of (N/2)^2)

    // Do not do anything if called too early. This is done because two consecutive calls can interfer.
    if(time_fs < m_button_time_fs_last_read + BUTTONS_READ_TIME_INTERVAL_FS)
    {
        return false;
    }
    // Update last time read was actually done
    m_button_time_fs_last_read = time_fs;

    // Old buttons state are now current state
    m_buttons_old = m_buttons;

    // A bit mask with NB_PIN_BUTTON_MATRIX_IN 1's.
    constexpr uint32_t l_input_mask = (1U << NB_PIN_BUTTON_MATRIX_IN) - 1;

    // Reading all buttons of this row, and put relevant bits in lsb
    // WARNING : this only works if the pins used as input are contiguous and ordered.
    const uint32_t l_buttons_inputs = (gpio_get_all() >> PIN_BUTTON_MATRIX_IN[0]) & l_input_mask;
    // Retrieve last status of these buttons
    const uint32_t l_buttons_inputs_prev = (m_buttons_raw >> (m_button_matrix_out_idx * NB_PIN_BUTTON_MATRIX_IN)) & l_input_mask;
    // Update stability of these buttons
    if(l_buttons_inputs == l_buttons_inputs_prev)
    {
        m_buttons_stability_count[m_button_matrix_out_idx]++;
    }
    else
    {
        m_buttons_stability_count[m_button_matrix_out_idx] = 0;
    }
    // Copy read buttons to raw buttons bit array for next read
    m_buttons_raw &= ~(l_input_mask << (m_button_matrix_out_idx * NB_PIN_BUTTON_MATRIX_IN));
    m_buttons_raw |= l_buttons_inputs << (m_button_matrix_out_idx * NB_PIN_BUTTON_MATRIX_IN);

    // Check if these buttons are stable
    if(m_buttons_stability_count[m_button_matrix_out_idx] == BUTTONS_STABILITY_THRESHOLD)
    {
        // Copy read buttons to raw buttons bit array
        m_buttons &= ~(l_input_mask << (m_button_matrix_out_idx * NB_PIN_BUTTON_MATRIX_IN));
        m_buttons |= (l_buttons_inputs << (m_button_matrix_out_idx * NB_PIN_BUTTON_MATRIX_IN));

        #if DEBUG > 1
        printf("Buttons stable : 0x%08x\n", m_buttons);
        #endif
    }
    #if DEBUG > 1
    else if(m_buttons_stability_count[m_button_matrix_out_idx] < BUTTONS_STABILITY_THRESHOLD)
    {
        printf("Buttons transient (%u) : 0x%08x\n", m_buttons_stability_count[m_button_matrix_out_idx], m_buttons_raw);
    }
    #endif

    // Disconnect gpio from matrix in order to read next row of button matrix
    gpio_put_high_z(PIN_BUTTON_MATRIX_OUT[m_button_matrix_out_idx]);
    // Increment index of the active row
    if(++m_button_matrix_out_idx == NB_PIN_BUTTON_MATRIX_OUT)
    {
        m_button_matrix_out_idx = 0;
    }
    // Set next output to high
    gpio_put_1_from_high_z(PIN_BUTTON_MATRIX_OUT[m_button_matrix_out_idx]);

    #ifdef DEBUG
    if(m_buttons != m_buttons_old)
    {
        printf("Buttons changed : 0x%08x to 0x%08x\n", m_buttons_old, m_buttons);
    }
    #endif

    // Return true if at least one button has changed
    return m_buttons != m_buttons_old;
}


void Controls::process_buttons()
{
    // Indicates if the LEDs must be updated
    bool l_leds_need_refresh = false;

    // Process the key buttons, this loop only works if the keys are next to each other in the m_buttons variables
    for(unsigned int i = BUTTON_KEY_C0_IDX; i <= BUTTON_KEY_C1_IDX; ++i)
    {
        // If button is pressed and was not pressed before
        if((m_buttons & (1<<i)) && !(m_buttons_old & (1<<i)))
        {
            const MidiEvent midi_event = midi_event_note_onoff(
                MIDI_NOTE_ON, MIDI_DEFAULT_CHANNEL, midi_get_note(m_selected_octave, i-BUTTON_KEY_C0_IDX), MIDI_DEFAULT_VELOCITY);
            g_midi_internal_buffer.push(midi_event);
            #ifdef DEBUG
            printf("MIDI NoteOn pushed : 0x%06x\n", midi_event);
            #endif
        }
        // If button was pressed before and is not pressed anymore
        else if(!(m_buttons & (1<<i)) && (m_buttons_old & (1<<i)))
        {
            const MidiEvent midi_event = midi_event_note_onoff(
                MIDI_NOTE_OFF, MIDI_DEFAULT_CHANNEL, midi_get_note(m_selected_octave, i-BUTTON_KEY_C0_IDX), MIDI_DEFAULT_VELOCITY);
            g_midi_internal_buffer.push(midi_event);
            #ifdef DEBUG
            printf("MIDI NoteOff pushed : 0x%06x\n", midi_event);
            #endif
        }
    }

    // Process octave change, and assume octave up and down are not pressed at the same time
    if((m_buttons & (1<<BUTTON_OCTAVE_DOWN_IDX)) && ~(m_buttons_old & (1<<BUTTON_OCTAVE_DOWN_IDX)))
    {
        if(m_selected_octave > -1)
        {
            m_selected_octave--;
        }
        #ifdef DEBUG
        printf("Octave Down ! Is now %d\n", m_selected_octave);
        #endif
    }
    else if((m_buttons & (1<<BUTTON_OCTAVE_UP_IDX)) && ~(m_buttons_old & (1<<BUTTON_OCTAVE_UP_IDX)))
    {
        if(m_selected_octave < 8)
        {
            m_selected_octave++;
        }
        #ifdef DEBUG
        printf("Octave Up ! Is now %d\n", m_selected_octave);
        #endif
    }

    // Process waveform change
    if((m_buttons & (1<<BUTTON_WAVEFORM_SELECT_IDX)) && ~(m_buttons_old & (1<<BUTTON_WAVEFORM_SELECT_IDX)))
    {
        if(m_selected_waveform == &square_wave)
        {
            m_selected_waveform = &saw_wave;
            m_leds &= ~(1<<LED_WAVEFORM_SQUARE_ENABLED_IDX);
            m_leds |= (1<<LED_WAVEFORM_SAW_ENABLED_IDX);
        }
        // There are only two waveforms possible
        else
        {
            m_selected_waveform = &square_wave;
            m_leds &= ~(1<<LED_WAVEFORM_SAW_ENABLED_IDX);
            m_leds |= (1<<LED_WAVEFORM_SQUARE_ENABLED_IDX);
        }
        // Maybe set m_texture to relevant value, although it will be overwritten next time its potentiometer is read
        l_leds_need_refresh = true;
        #ifdef DEBUG
        printf("Waveform change ! Is now %d\n", m_selected_waveform);
        #endif
    }

    // Finally update leds if necessary
    if(l_leds_need_refresh)
    {
        write_leds();
        #ifdef DEBUG
        printf("LEDs refreshed ! Are now 0x%08x\n", m_leds);
        #endif
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


void Controls::set_potentiometer(unsigned int potentiometer_idx, uint8_t value)
{
    #if DEBUG == 3
    printf("ADC %u : %u\n", potentiometer_idx, value);
    #endif

    // Handle each potentiometer value differently
    switch (potentiometer_idx)
    {
    case POTENTIOMETER_ATTACK_IDX:
        // TODO Attack should probably not be linear
        m_attack_fs = ATTACK_MIN_FS + (static_cast<float>(ATTACK_MAX_FS-ATTACK_MIN_FS) * static_cast<float>(value) / std::numeric_limits<uint8_t>::max());
        // While only two pots can be used for ADSR, release is also controlled by attack potentiometer
        m_release_fs = RELEASE_MIN_FS + (static_cast<float>(RELEASE_MAX_FS-RELEASE_MIN_FS) * static_cast<float>(value) / std::numeric_limits<uint8_t>::max());
        break;

    case POTENTIOMETER_SUSTAIN_IDX:
        // Sustain is linear between min and max, comes in fxpt_UQ0.8
        m_sustain = SUSTAIN_MIN + fxpt_convert_n((fxpt64_t)(SUSTAIN_MAX-SUSTAIN_MIN) * fxpt_convert_n((fxpt64_t)value, 8, 31), 62, 31);
        break;

    case POTENTIOMETER_FILTER_CUTOFF_IDX:
        // TODO Filter cutoff frequency should not be linear
        m_filter_cutoff = FILTER_CUTOFF_MIN_HZ + ((FILTER_CUTOFF_MAX_HZ-FILTER_CUTOFF_MIN_HZ) * static_cast<float>(value) / std::numeric_limits<uint8_t>::max());
        break;

    case POTENTIOMETER_TEXTURE_IDX:
        // Update texture parameter according to selected waveform
        if(m_selected_waveform == &square_wave)
        {
            // Square wave can have a duty cycle between 0 and 0.5, so value can be interpreted as fxpt_UQ-1.9
            m_texture = fxpt_convert_n((fxpt_Q0_31)value, 9, 31);
        }else
        if(m_selected_waveform == &square_wave)
        {
            // Saw wave does not have a texture parameter yet
            m_texture = 0;
        }
        else
        {
            // Unhandled case, should not occur
        }
    
    default:
        // Unhandled case, should not occur
        break;
    }
}

bool Controls::have_filter_params_changed()
{
    const bool l_has_changed = (m_filter_cutoff != m_filter_cutoff_old) || (m_filter_Q != m_filter_Q_old);
    m_filter_cutoff_old = m_filter_cutoff;
    m_filter_Q_old = m_filter_Q;
    return l_has_changed;
}


void initialize_controls()
{
    // Setup the outputs for the button matrix
    for(unsigned int i = 0; i < NB_PIN_BUTTON_MATRIX_OUT; ++i)
    {
        gpio_init(PIN_BUTTON_MATRIX_OUT[i]);
        // gpios are not put to GPIO_OUT since high-z state puts them as inputs
        gpio_put_high_z(PIN_BUTTON_MATRIX_OUT[i]);
        // For some reason the buttons matrix rows interfer with the next row if not pulled 
        gpio_pull_down(PIN_BUTTON_MATRIX_OUT[i]);
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

    // Initialize ADC
    adc_init();
    for(unsigned int i = 0; i < NB_PIN_POTENTIOMETERS; ++i)
    {
        adc_gpio_init(PIN_POTENTIOMETERS[i]);
    }
    adc_select_input(0);
    // Set adc conversion speed
    adc_set_clkdiv((static_cast<float>(ADC_BASE_CLOCK_HZ) / POTENTIOMETERS_REFRESH_RATE_HZ) - 1.f);
    // Set ADC to reed all inputs alternatively (mask with NB_PIN_POTENTIOMETERS ones)
    adc_set_round_robin((1<<NB_PIN_POTENTIOMETERS)-1);
    // Disable temperature sensor
    adc_set_temp_sensor_enabled(false);
    // Enable ADC interrupts
    irq_clear(ADC_IRQ_FIFO);
    adc_irq_set_enabled(true);
    irq_set_exclusive_handler(ADC_IRQ_FIFO, adc_irq_handler);
    // Setup ADC to write its results in fifo :
    // - Disable DMA request
    // - Interrupt is raised with 1 sample in the fifo
    // - Disable error bit,
    // - Enable byte shift so that result is on one byte only
    adc_fifo_setup(true, false, 1, false, true);
    // Authorize ADC FIFO to raise interrupts
    irq_set_enabled(ADC_IRQ_FIFO, true);

    // Start ADC in free-running mode
    adc_run(true);
}


void adc_irq_handler()
{
    // A static variable remembering which adc channel is used
    // adc_get_selected_input() cannot be used since next conversion has already started
    static unsigned int sl_adc_channel = 0;

    // Should not block since function is triggered by ADC itself
    const uint8_t l_adc_value = adc_fifo_get_blocking();

    // Send to Controls instance
    Controls::get_instance().set_potentiometer(sl_adc_channel, l_adc_value);

    // A new conversion has started on the next channel
    if(++sl_adc_channel == NB_PIN_POTENTIOMETERS)
    {
        sl_adc_channel = 0;
    }
}