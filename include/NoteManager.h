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

#ifndef SYNTHPATHY_NOTEMANAGER_H_
#define SYNTHPATHY_NOTEMANAGER_H_

#include "ActiveNote.h"

/**
 * @brief This classes manages the notes that are currently active.
 * Its purpose is to create, release and kill the notes, as well as to pass
 * them relevant data to process audio.
 * It is a singleton, only one instance can ever be created.
 * This class uses the global midi buffer to read and pop events.
 */
class NoteManager
{
protected:

    NoteManager(); // Prevent construction
    NoteManager(const NoteManager&) = delete; // Prevent construction by copying
    NoteManager& operator=(const NoteManager&) = delete; // Prevent assignment

    // Private constants

    /**
     * @brief The maximum number of notes that can be active at the same time.
     * 
     */
    static constexpr unsigned int NB_ACTIVE_NOTES = 8;

    // Private members -----------------------------------------------------------------------------

    ActiveNote m_active_notes_pool[NB_ACTIVE_NOTES];

    // Private methods -----------------------------------------------------------------------------

public:

    /**
     * @brief Get the NoteManager instance.
     * 
     */
    inline static NoteManager& get_instance()
    {
        static NoteManager instance;
        return instance;
    }

    /**
     * @brief Create, release or update active notes with the global midi buffer.
     * @param time_fs The time in number of periods of the audio sampling frequency.
     * 
     */
    void update_active_notes(unsigned int time_fs);

    /**
     * @brief Returns the sum of all active note audio output.
     *
     * @param time_fs The time in number of periods of the audio sampling frequency.
     * @return float 
     */
    float get_audio(unsigned int time_fs);
};

#endif //SYNTHPATHY_NOTEMANAGER_H_