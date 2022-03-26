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

#include "ActiveNote.h"
#include "frequencies.h"

#include <limits>

#ifdef DEBUG
#include <stdio.h>
#endif

ActiveNote::ActiveNote()
{
    m_time_stop_fs = 0; 
}

ActiveNote::ActiveNote(MidiByte _midi_note, fxpt_Q0_31 _velocity, unsigned int _time_start_fs, unsigned int _attack_fs, unsigned int _decay_fs) :
    m_midi_note(_midi_note),
    m_velocity(_velocity),
    m_time_start_fs(_time_start_fs),
    m_attack_fs(_attack_fs),
    m_decay_fs(_decay_fs)
{
    m_period_fs = MIDI_PERIODS_FS[_midi_note];

    m_time_released_fs = std::numeric_limits<unsigned int>::max();
    m_time_stop_fs = std::numeric_limits<unsigned int>::max();
    #ifdef DEBUG
    printf("ActiveNote(%d, %d, %d, %d, %d)\n", m_midi_note, m_velocity, m_time_start_fs, m_attack_fs, m_decay_fs);
    #endif
}


fxpt_Q0_31 ActiveNote::get_ADSR_envelope(unsigned int time_fs, fxpt_Q0_31 sustain) const
{
    // While the note has not been released the release time is infinite
    if(time_fs < m_time_released_fs)
    {
        // The time elapsed since the beginning of the note
        const unsigned int l_elapsed = time_fs - m_time_start_fs;

        // If in sustain phase
        if(l_elapsed >= (m_attack_fs + m_decay_fs))
        {
            return sustain;
        }
        else
        {
            // If in decay phase
            if(l_elapsed >= m_attack_fs)
            {
                // return 1 + (sustain-1) * (elapsed-attack) / decay
                constexpr fxpt_Q0_31 l_one = std::numeric_limits<fxpt_Q0_31>::max();
                const fxpt64_t temp = fxpt_convert_n((fxpt64_t)l_elapsed - (fxpt64_t)m_attack_fs, 0, 31) / m_decay_fs;
                // Q0.31 multplied by Q0.31 gives a result in Q0.62
                return l_one + fxpt_convert_n((fxpt64_t)(sustain - l_one) * temp, 62, 31);
            }
            // If in attack phase
            else
            {
                return (fxpt_Q0_31)(fxpt_convert_n((fxpt64_t)l_elapsed, 0, 31) / m_attack_fs);
            }
        }
    }
    else
    {
        // Release phase
        // return (t_released + release - t) * adsr_at_release / release
        return (fxpt_Q0_31)((fxpt64_t)(m_time_released_fs + m_release_fs - time_fs) * m_ADSR_at_release / m_release_fs);
    }
}


void ActiveNote::release(unsigned int time_released_fs, float sustain, unsigned int release)
{
    m_release_fs = release;
    m_ADSR_at_release = get_ADSR_envelope(time_released_fs, sustain);
    m_time_released_fs = time_released_fs;
    m_time_stop_fs = m_time_released_fs + m_release_fs;

    #ifdef DEBUG
    printf("ActiveNote released(%d, %f, %d)\n", m_time_released_fs, sustain, m_release_fs);
    #endif
}


fxpt_Q0_31 ActiveNote::get_audio_value(unsigned int time_fs, fxpt_Q0_31(*waveform)(unsigned int, unsigned int, fxpt_Q0_31), fxpt_Q0_31 texture, fxpt_Q0_31 sustain) const
{
    if (time_fs >= m_time_stop_fs)
    {
        return 0;
    }

    fxpt_Q0_31 l_audio_value = waveform(time_fs, m_period_fs, texture);

    // Apply ADSR and velocity
    l_audio_value = fxpt_convert_n(
            fxpt_convert_n((fxpt64_t)l_audio_value * (fxpt64_t)get_ADSR_envelope(time_fs, sustain), 62, 31) *
            (fxpt64_t)m_velocity,
            62, 31
    );
    return l_audio_value;
}