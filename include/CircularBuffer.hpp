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

#ifndef SYNTHPATHY_CIRCULARBUFFER_HPP_
#define SYNTHPATHY_CIRCULARBUFFER_HPP_

/**
 * @brief A circular buffer class.
 * 
 * @tparam T The datatype to be stored.
 * @tparam size The size of the buffer, with size > 1.
 */
template<class T, unsigned int size>
class CircularBuffer
{
public:

    CircularBuffer()
    {
        m_read_idx, m_write_idx = 0;
    }

    /**
     * @brief Indicate whether the buffer is empty or not.
     * 
     * @return true if empty.
     * @return false if not empty.
     */
    inline bool is_empty() const
    {
        return m_read_idx == m_write_idx;
    }

    /**
     * @brief Returns the number of available data. 
     * It is better to first check is_empty() for efficiency.
     * @return unsigned int number of available data.
     */
    inline unsigned int count() const
    {
        return (m_write_idx >= m_read_idx) ? (m_write_idx - m_read_idx) : (m_write_idx + size - m_read_idx);
    }

    /**
     * @brief Push new data in the buffer.
     * 
     * @param data The data to be pushed.
     */
    inline void push(const T& data)
    {
        if(m_write_idx == size) m_write_idx = 0;
        m_data[m_write_idx++] = data;
    }

    /**
     * @brief Pop data from the buffer.
     * There is no guard there, so check for available data with is_empty() first. 
     */
    inline T pop()
    {
        if(m_read_idx == size) m_read_idx = 0;
        return m_data[m_read_idx++];
    }

    /**
     * @brief Read data from the buffer without popping it.
     * 
     * @return const T& The data to be read
     */
    inline const T& read() const
    {
        return m_data[m_read_idx];
    }

    /**
     * @brief Empty the buffer.
     * 
     */
    inline void empty()
    {
        m_read_idx = m_write_idx;
    }

    /**
     * @brief Get the size of the buffer.
     * 
     * @return unsigned int The buffer size.
     */
    inline unsigned int get_size() const
    {
        return size;
    }

    /**
     * @brief Get the raw buffer array.
     * 
     * @return T* Pointer to the raw buffer array.
     */
    inline T* get_raw_buffer()
    {
        return m_data;
    }

    /**
     * @brief Get the write index of the next value.
     * 
     * @return unsigned int The write index.
     */
    inline unsigned int get_write_idx()
    {
        return (m_write_idx != size) ? m_write_idx : 0;
    }

    /**
     * @brief Get the read index of the next value.
     * 
     * @return unsigned int The read index.
     */
    inline unsigned int get_read_idx()
    {
        return (m_read_idx != size) ? m_read_idx : 0;
    }

protected:
    /**
     * @brief The data array.
     * 
     */
    T m_data[size];

    /**
     * @brief Where to write the next value.
     * 
     */
    unsigned int m_write_idx;

    /**
     * @brief Where to read the next value.
     * 
     */
    unsigned int m_read_idx;

};

#endif //SYNTHPATHY_CIRCULARBUFFER_HPP_