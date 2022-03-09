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

#ifndef SYNTHPATHY_TESTS_H_
#define SYNTHPATHY_TESTS_H_

/**
 * @brief The number of times each measurement is performed.
 * 
 */
constexpr unsigned int NB_TESTS = 100000;

/**
 * @brief Perform and print a series of tests and measurement.
 * This method should never be called in a production version.
 */
void perform_tests();

#endif //SYNTHPATHY_TESTS_H_