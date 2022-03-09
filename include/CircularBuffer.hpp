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
        m_count, m_write_idx = 0;
    }

    /**
     * @brief Indicate whether the buffer is empty or not.
     * 
     * @return true if empty.
     * @return false if not empty.
     */
    inline bool is_empty() const
    {
        return !m_count;
    }

    /**
     * @brief Indicates whether the buffer is full or not.
     * 
     * @return true if full.
     * @return false if not full.
     */
    inline bool is_full() const
    {
        return m_count == size;
    }

    /**
     * @brief Returns the number of element in the buffer. 
     * @return unsigned int number of available data.
     */
    inline unsigned int get_count() const
    {
        return m_count;
    }

    /**
     * @brief Push element in the buffer.
     * @param element The element to be pushed.
     */
    void push(const T& element)
    {
        if(m_count < size)
        {
            m_data[m_write_idx++] = element;
            if(m_write_idx == size) m_write_idx = 0;
            m_count++;
        }
    }

    /**
     * @brief Push element in the buffer.
     * This method does not check whether there is space available or not,
     * this may result in a loss of data.
     * @param element The element to be pushed.
     */
    inline void push_fast(const T& element)
    {
        m_data[m_write_idx++] = element;
        if(m_write_idx == size) m_write_idx = 0;
        m_count++;
    }

    /**
     * @brief Pop element from the buffer if available.
     * Returns a default element of template class if empty.
     */
    T pop()
    {
        if(m_count)
        {
            const unsigned int l_read_idx = get_read_idx();
            m_count--;
            return m_data[l_read_idx];
        }
        else
        {
            return T();
        }
    }

    /**
     * @brief Pop element from the buffer.
     * There is no guard there, so check for available data with is_empty() first.
     * A count overflow will happen if called on an empty buffer.
     */
    inline T pop_fast()
    {
        const unsigned int l_read_idx = get_read_idx();
        m_count--;
        return m_data[l_read_idx];
    }

    /**
     * @brief Read data from the buffer without popping it.
     * There is no guard there, so check for available data with is_empty() first.
     * @return const T& The data to be read
     */
    inline const T& read() const
    {
        return m_data[get_read_idx()];
    }

    /**
     * @brief Empty the buffer.
     * 
     */
    inline void empty()
    {
        m_count = 0;
    }

    /**
     * @brief Fill the buffer with given value.
     * 
     * @param val 
     */
    void fill(T val)
    {
        while(m_count != size)
        {
            push_fast(val);
        }
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
    inline unsigned int get_write_idx() const
    {
        return m_write_idx;
    }

    /**
     * @brief Get the read index of the next value.
     * 
     * @return unsigned int The read index.
     */
    inline unsigned int get_read_idx() const
    {
        return (m_write_idx >= m_count) ? (m_write_idx - m_count) : (size + m_write_idx - m_count);
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
     * @brief The number of elements in the buffer.
     * 
     */
    unsigned int m_count;

};

#endif //SYNTHPATHY_CIRCULARBUFFER_HPP_