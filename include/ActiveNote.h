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

#ifndef SYNTHPATHY_ACTIVENOTE_H_
#define SYNTHPATHY_ACTIVENOTE_H_

#include "waveforms.h"

#include <limits>

class ActiveNote
{
protected:
    
    // Private members -----------------------------------------------------------------------------

    /**
     * @brief The midi number of the note.
     * 
     */
    MidiByte m_midi_note;

    /**
     * @brief The period of the note in number of samples.
     * 
     */
    unsigned int m_period_fs;

    /**
     * @brief The velocity of the note between 0 and 1.
     * 
     */
    float m_velocity;

    /**
     * @brief Time at which the note started, in number of periods of the audio sampling frequency.
     * 
     */
    unsigned int m_time_start_fs;
    
    /**
     * @brief Time at which the note was released, in number of periods of the audio sampling frequency.
     * 
     */
    unsigned int m_time_released_fs;

    /**
     * @brief Time at which the note is completely dead, in number of periods of the audio sampling frequency.
     * 
     */
    unsigned int m_time_stop_fs;

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
     * @brief The release value of the ADSR envelope, in number of periods of the audio sampling frequency.
     * 
     */
    unsigned int m_release_fs;

    /**
     * @brief The value of the ADSR envelope at release time.
     * 
     */
    float m_ADSR_at_release;


    // Private methods -----------------------------------------------------------------------------

    /**
     * @brief Get the value level of the ADSR envelope
     * 
     * @param time_fs Current time in number of periods of the audio sampling frequency.
     * @param sustain Sustain level between 0 and 1.
     * @return float 
     */
    float get_ADSR_envelope(unsigned int time_fs, float sustain) const;

public:

    /**
     * @brief Active Note default constructor.
     * This constructor create a note already dead.
     */
    ActiveNote();

    /**
     * @brief ActiveNote constructor
     * 
     * @param midi_note The midi number of the note to be created.
     * @param velocity The velocity of the note between 0 and 1.
     * @param time_start Time at which the note started in number of periods of the audio sampling frequency.
     * @param attack_fs Attack duration in number of periods of the audio sampling frequency.
     * @param decay_fs Decay duration in number of periods of the audio sampling frequency.
     */
    ActiveNote(MidiByte midi_note, float velocity, unsigned int time_start_fs, unsigned int attack_fs, unsigned int decay_fs);

    ~ActiveNote() = default;

    /**
     * @brief The midi number of the note.
     * 
     * @return MidiByte 
     */
    inline MidiByte get_midi_note() const { return m_midi_note; }

    /**
     * @brief Release the current note
     * 
     * @param time_released_fs The time the note was released at, in number of periods of the audio sampling frequency.
     * @param sustain Sustain level at release between 0 and 1.
     * @param release_fs Release duration in number of periods of the audio sampling frequency.
     */
    void release(unsigned int time_released_fs, float sustain, unsigned int release_fs);

    /**
     * @brief Kills the note.
     * 
     */
    inline void kill()
    {
        m_time_stop_fs = 0;
    }

    /**
     * @brief Get the audio value at the given time.
     * 
     * @param time_fs The time in number of periods of the audio sampling frequency.
     * @param waveform The selected type of waveform.
     * @param texture The texture parameter of the waveform.
     * @param sustain Sustain level between 0 and 1.
     * @return float 
     */
    float get_audio_value(unsigned int time_fs, float(*waveform)(unsigned int, unsigned int, float), float texture, float sustain) const;

    /**
     * @brief Indicates whether the note is still alive or not.
     * 
     * @param time_fs The time in number of periods of the audio sampling frequency.
     * @return true The note is alive.
     * @return false The note is dead.
     */
    inline bool is_alive(unsigned int time_fs)
    {
        return time_fs <= m_time_stop_fs;
    }

    /**
     * @brief Indicates whether the note has already been released or not.
     * 
     * @return true The note is already released.
     * @return false The note has not been released yet.
     */
    inline bool is_released()
    {
        return m_time_released_fs != std::numeric_limits<unsigned int>::max();
    }

};

#endif //SYNTHPATHY_ACTIVENOTE_H_