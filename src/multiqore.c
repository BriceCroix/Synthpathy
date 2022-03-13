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
#include "pico/util/queue.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define MULTIQORE_PRINTF_BUFFER 128U


queue_t multiqore_call_queue;

queue_t multiqore_results_queue;

/**
 * @brief The task internally used by the other core.
 * 
 */
static void core1_task()
{
    struct multiqore_call_element call_element;
    multiqore_results_t result;
    while(1)
    {
        // Wait for order from core 0
        queue_remove_blocking(&multiqore_call_queue, &call_element);
        // Execute order
        (call_element.function)(call_element.params);
    }
}


void multiqore_initialize()
{
    queue_init(&multiqore_call_queue, sizeof(struct multiqore_call_element), SIZE_MULTIQORE_QUEUE);
    queue_init(&multiqore_results_queue, sizeof(multiqore_results_t), SIZE_MULTIQORE_QUEUE);
    multicore_launch_core1(core1_task);
}
