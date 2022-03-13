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

#include "pico/util/queue.h"

/**
 * @brief The number of cores on the RP2040.
 * 
 */
#define NB_CORES 2U

/**
 * @brief The size of the queues used for multiprocessing.
 * 
 */
#define SIZE_MULTIQORE_QUEUE 2U

/**
 * @brief The type used internaly for the results queue.
 * It is important that this type is 32 bits since the RP2040 is a 32 bits processor.
 */
typedef uint32_t multiqore_results_t;

/**
 * @brief An element of the call queue used for multiprocessing.
 * 
 */
struct multiqore_call_element
{
    /**
     * @brief Function pointer to the method to be called on other core.
     * 
     */
    void (*function)(void*);
    /**
     * @brief Pointer to a parameters structure used by the function
     * 
     */
    void* params;
};

/**
 * @brief The call queue internally used to call methods on other core.
 * 
 */
extern queue_t multiqore_call_queue;

/**
 * @brief The call queue internally used to return results from other core.
 * 
 */
extern queue_t multiqore_results_queue;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initializes other core to handle multiprocessing.
 * 
 */
void multiqore_initialize();

/**
 * @brief Send result from other core to main core.
 * Result should be pointer to either int32_t, uin32_t, or float.
 * Example :
 *     float res = 4.5f;
 *     multiqore_send_result((void*)(&f));
 * @param result 
 */
inline void multiqore_send_result(void* result)
{
    queue_try_add(&multiqore_results_queue, (multiqore_results_t*)(&result));
}

/**
 * @brief Used to get result from other core.
 * This method waits for the other core to finish its task.
 * @return uint32_t The result.
 */
inline uint32_t multiqore_get_result_uint32()
{
    multiqore_results_t result;
    queue_remove_blocking(&multiqore_results_queue, &result);
    return *((uint32_t*)(&result));
}

/**
 * @brief Used to get result from other core.
 * This method waits for the other core to finish its task.
 * @return int32_t The result.
 */
inline int32_t multiqore_get_result_int32()
{
    multiqore_results_t result;
    queue_remove_blocking(&multiqore_results_queue, &result);
    return *((int32_t*)(&result));
}

/**
 * @brief Used to get result from other core.
 * This method waits for the other core to finish its task.
 * @return float The result.
 */
inline float multiqore_get_result_float()
{
    multiqore_results_t result;
    queue_remove_blocking(&multiqore_results_queue, &result);
    return *((float*)(&result));
}

/**
 * @brief Start a task on other core.
 * data at params should remain accessible during all processing.
 * How to use : say you want to parallelize a function that computes the sum of inverses up to N :
 * 
 * // main.cpp
 * 
 * float sum_of_inverses(int i_start, i_end)
 * {
 *     float result = 0;
 *     for(int i = i_start; i < i_end; ++i)
 *     {
 *         result += 1.f / i;
 *     }
 *     return result;
 * }
 * 
 * struct sum_of_inverses_params
 * {
 *     int i_start;
 *     int i_end;
 * }
 * 
 * void sum_of_inverses_wrapper(void* params)
 * {
 *     // Reinterpret pointer to access parameters
 *     const i_start = ((struct sum_of_inverses_params*)params)->i_start;
 *     const i_end = ((struct sum_of_inverses_params*))params->i_end;
 *     const float result = sum_of_inverses(i_start, i_end);
 *     multiqore_send_result((void*)(&result)); 
 * }
 * 
 * int main()
 * {
 *     int N = 1000;
 *     // Core 1 handles second half of sum
 *     struct sum_of_inverses_params params = {N/2, N};
 *     multiqore_start_task(&sum_of_inverses_wrapper, &params);
 *     // Core 0 handles first half of sum
 *     float result = sum_of_inverses(0, N/2);
 *     // Add together the two halves of sum
 *     result += multiqore_get_result_float();
 *     // Print result using other core resources
 *     multiqore_printf("Result is %f\n", result);
 * }
 * 
 * @param task Function pointer to task to perform.
 * @param params Pointer to parameters of function.
 */
inline void multiqore_start_task(void(*task)(void*), void* params)
{
    struct multiqore_call_element e = {task, params};
    queue_try_add(&multiqore_call_queue, &e);
}

/**
 * @brief printf on other core in order not to block main one.
 * 
 */
void multiqore_printf(const char* format, ...);


#ifdef __cplusplus
}
#endif

#endif //MULTIQORE_H_
