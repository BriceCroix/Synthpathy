/**
 * multiqore is a very light library for raspberry pico for multiprocessing using pico sdk's queues. 
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

#ifndef MULTIQORE_H_
#define MULTIQORE_H_

#include "pico/multicore.h"


/**
 * @brief The number of cores on the RP2040.
 * 
 */
#define NB_CORES 2U

/**
 * @brief The type used internaly for the fifos.
 * It is important that this type is 32 bits since the RP2040 is a 32 bits processor.
 */
typedef uint32_t multiqore_fifo_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initializes other core to handle multiprocessing.
 * 
 */
void multiqore_initialize();

/**
 * @brief Send data from one core to the other.
 * 
 * @param data Pointer to the data to send.
 * @param data_size Size of the data in number of bytes.
 */
inline void multiqore_send(const void* data, size_t data_size)
{
    for(const multiqore_fifo_t* ptr = (multiqore_fifo_t*)data; ptr < (multiqore_fifo_t*)((char*)data + data_size); ptr++)
    {
        //printf("C1 : Sending 0x%08x from @0x%p\n", *ptr, ptr);
        multicore_fifo_push_blocking(*ptr);
    }
}
#define multiqore_send_params multiqore_send
#define multiqore_send_result multiqore_send

/**
 * @brief Get data from the other core.
 * 
 * @param data Pointer where to store data.
 * @param data_size Size of the data in number of bytes.
 */
inline void multiqore_get(void* data, size_t data_size)
{
    for(multiqore_fifo_t* ptr = (multiqore_fifo_t*)data; ptr < (multiqore_fifo_t*)((char*)data + data_size); ptr++)
    {
        (*ptr) = multicore_fifo_pop_blocking();
        //printf("C1 : Storing 0x%08x at @0x%p\n", *ptr, ptr);
    }
}
#define multiqore_get_params multiqore_get
#define multiqore_get_result multiqore_get


/**
 * @brief Start a task on other core.
 * 
 * @param task Function pointer to be executed on second core.
 */
inline void multiqore_start_task(void(*task)(void))
{
    multicore_fifo_push_blocking((multiqore_fifo_t)task);
}


#ifdef __cplusplus
}
#endif

#endif //MULTIQORE_H_
