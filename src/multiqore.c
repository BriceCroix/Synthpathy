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

#include "multiqore.h"

#include "pico/multicore.h"

#define MULTIQORE_PRINTF_BUFFER 128U

/**
 * @brief The task internally used by the other core.
 * 
 */
static void core1_task()
{
    multicore_fifo_drain();
    while(1)
    {
        // Wait for order from core 0, cast to function ptr that returns and take void, and call
        const void (*task)(void) = (void (*)(void))multicore_fifo_pop_blocking();
        //printf("C1 : received task 0x%x\n", task);
        (*task)();
        //printf("C1 : finished task 0x%x\n", task);
    }
}


void multiqore_initialize()
{
    multicore_fifo_drain();
    multicore_launch_core1(core1_task);
}