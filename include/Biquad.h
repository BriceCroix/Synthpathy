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

#ifndef SYNTHPATHY_BIQUAD_H_
#define SYNTHPATHY_BIQUAD_H_

#include <math.h>
#include <iostream>

#include "fxpt.h"

/**
 * @brief Digital biquadratic filter.
 * Transfer function is H(z) = (b0 + b1*z^(-1) + b2*z^(-2)) / (a0 + a1*z^(-1) + a2*z^(-2))
 */
class Biquad
{
protected:
    /**
     * @brief Biquad filter coefficients and internal buffers.
     * index 0 : b0
     * index 1 : b1
     * index 2 : b2
     * index 3 : a1
     * index 4 : a2
     * 
     * For low and high pass filter, all coefficients fall in range [-2, 2], hence precision Q1.30.
     */
    fxpt_Q1_30 m_coeffs[5];

    static constexpr unsigned int B0_IDX = 0;
    static constexpr unsigned int B1_IDX = 1;
    static constexpr unsigned int B2_IDX = 2;
    static constexpr unsigned int A1_IDX = 3;
    static constexpr unsigned int A2_IDX = 4;

    /**
     * @brief Internal buffer of transposed direct form 2.
     * Theoretically falls in [-6, 6] according to equations, hence precision Q3.28.
     */
    fxpt_Q3_28 m_z1;

    /**
     * @brief Internal buffer of transposed direct form 2.
     * Theoretically falls in [-2, 2] according to equations, hence precision Q1.30.
     */
    fxpt_Q1_30 m_z2;

    /**
     * @brief Setters for the filter coefficients.
     * 
     * @{
     */
    inline void set_b0(fxpt_Q1_30 b0) { m_coeffs[B0_IDX] = b0; }
    inline void set_b1(fxpt_Q1_30 b1) { m_coeffs[B1_IDX] = b1; }
    inline void set_b2(fxpt_Q1_30 b2) { m_coeffs[B2_IDX] = b2; }
    inline void set_a1(fxpt_Q1_30 a1) { m_coeffs[A1_IDX] = a1; }
    inline void set_a2(fxpt_Q1_30 a2) { m_coeffs[A2_IDX] = a2; }
    /**@}*/

    /**
     * @brief Setters for the internal buffers.
     * 
     * @{
     */
    inline void set_z1(fxpt_Q3_28 z1) { m_z1 = z1; }
    inline void set_z2(fxpt_Q1_30 z2) { m_z2 = z2; }
    /**@}*/


public:
    /**
     * @brief Creates an all-pass filter.
     * 
     */
    Biquad();

    /**
     * @brief Creates filter with given coefficients.
     * 
     * @param b0 
     * @param b1 
     * @param b2 
     * @param a0 
     * @param a1 
     * @param a2 
     */
    Biquad(fxpt_Q1_30 b0, fxpt_Q1_30 b1, fxpt_Q1_30 b2, fxpt_Q1_30 a0, fxpt_Q1_30 a1, fxpt_Q1_30 a2);

    /**
     * @brief Getters for the filter coefficients.
     * 
     * @return fxpt_Q1_30 
     * @{
     */
    inline fxpt_Q1_30 get_b0() const { return m_coeffs[B0_IDX]; }
    inline fxpt_Q1_30 get_b1() const { return m_coeffs[B1_IDX]; }
    inline fxpt_Q1_30 get_b2() const { return m_coeffs[B2_IDX]; }
    inline fxpt_Q1_30 get_a0() const { return fxpt_Q1_30(1<<30); }
    inline fxpt_Q1_30 get_a1() const { return m_coeffs[A1_IDX]; }
    inline fxpt_Q1_30 get_a2() const { return m_coeffs[A2_IDX]; }
    /**@}*/

    /**
     * @brief Getters for the internal buffers.
     * 
     * @{
     */
    inline fxpt_Q3_28 get_z1() const { return m_z1; }
    inline fxpt_Q1_30 get_z2() const { return m_z2; }
    /**@}*/

    /**
     * @brief Get the array where coefficients are stored.
     * 
     * @return const fxpt_Q1_30* 
     */
    inline const fxpt_Q1_30* get_coeffs() const { return m_coeffs; }

    /**
     * @brief Copy the coefficients of another filter on current filter.
     * This does not reset the internal buffers.
     */
    void copy_coefficients(const Biquad &other);

    /**
     * @brief Get low pass filter.
     * 
     * @param freq_cutoff The cutoff frequency.
     * @param sampling_rate The sampling frequency.
     * @param Q The quality factor, that cannot be less than 1/sqrt(2).
     * @return Biquad 
     */
    static Biquad get_low_pass(fxpt_UQ16_16 freq_cutoff, unsigned int sampling_rate, fxpt_UQ3_29 Q = fxpt_from_float(M_SQRT1_2, 29));

    /**
     * @brief Process given sample.
     * 
     * @param x 
     * @return fxpt_Q0_31 
     */
    fxpt_Q0_31 process(fxpt_Q0_31 x = 0);

    friend std::ostream &operator<<(std::ostream &output, const Biquad &biquad)
    { 
        output << "Biquad(" <<
            fxpt_to_float(biquad.get_b0(), 30) << ", " << fxpt_to_float(biquad.get_b1(), 30) << ", " <<
            fxpt_to_float(biquad.get_b2(), 30) << ", " << fxpt_to_float(biquad.get_a0(), 30) << ", " <<
            fxpt_to_float(biquad.get_a1(), 30) << ", " << fxpt_to_float(biquad.get_a2(), 30) << ")";
        return output;            
    }
};


class DynamicBiquad : public Biquad
{
protected:

    /**
     * @brief Biquad filter coefficients and internal buffers of the target filter.
     * Ranges are given for low and high pass filters.
     * index 0 : b0 in [ 0, 1]
     * index 1 : b1 in [-2, 2]
     * index 2 : b2 in [ 0, 1]
     * index 3 : a1 in [-2, 2]
     * index 4 : a2 in [-1, 1]
     */
    fxpt_Q1_30 m_coeffs_target[5];

    /**
     * @brief Internal buffer of target filter, of transposed direct form 2.
     * Theoretically falls in [-6, 6] according to equations, hence precision Q3.28.
     */
    fxpt_Q3_28 m_z1_target;

    /**
     * @brief Internal buffer of target filter, of transposed direct form 2.
     * Theoretically falls in [-2, 2] according to equations, hence precision Q1.30.
     */
    fxpt_Q1_30 m_z2_target;

    /**
     * @brief The duration of the transition in number of samples.
     * 
     */
    unsigned int m_transition_duration_fs;

    /**
     * @brief The transition elapsed time in number of samples.
     * 
     */
    unsigned int m_transition_elapsed_fs;

    /**
     * @brief Setters for the filter coefficients.
     * @{
     */
    inline void set_b0_target(fxpt_Q1_30 b0) { m_coeffs_target[B0_IDX] = b0; }
    inline void set_b1_target(fxpt_Q1_30 b1) { m_coeffs_target[B1_IDX] = b1; }
    inline void set_b2_target(fxpt_Q1_30 b2) { m_coeffs_target[B2_IDX] = b2; }
    inline void set_a1_target(fxpt_Q1_30 a1) { m_coeffs_target[A1_IDX] = a1; }
    inline void set_a2_target(fxpt_Q1_30 a2) { m_coeffs_target[A2_IDX] = a2; }
    /**@}*/

    /**
     * @brief Setters for the internal buffers of the target filter.
     * @{
     */
    inline void set_z1_target(fxpt_Q3_28 z1) { m_z1_target = z1; }
    inline void set_z2_target(fxpt_Q1_30 z2) { m_z2_target = z2; }
    /**@}*/

public:

    DynamicBiquad(const Biquad &biquad);

    /**
     * @brief Getters for the target filter coefficients.
     * 
     * @return fxpt_Q1_30 
     * @{
     */
    inline fxpt_Q1_30 get_b0_target() const { return m_coeffs_target[B0_IDX]; }
    inline fxpt_Q1_30 get_b1_target() const { return m_coeffs_target[B1_IDX]; }
    inline fxpt_Q1_30 get_b2_target() const { return m_coeffs_target[B2_IDX]; }
    inline fxpt_Q1_30 get_a0_target() const { return fxpt_Q1_30(1<<30); }
    inline fxpt_Q1_30 get_a1_target() const { return m_coeffs_target[A1_IDX]; }
    inline fxpt_Q1_30 get_a2_target() const { return m_coeffs_target[A2_IDX]; }
    /**@}*/

    /**
     * @brief Getters for the target filter internal buffers.
     * @{
     */
    inline fxpt_Q3_28 get_z1_target() const { return m_z1_target; }
    inline fxpt_Q1_30 get_z2_target() const { return m_z2_target; }
    /**@}*/

    /**
     * @brief Sets the target to which this filter must tend.
     * 
     * @param target The target filter.
     * @param transition_duration_fs The duration of the transition in number of samples. The longer the smoother.
     */
    void set_target(const Biquad &target, unsigned int transition_duration_fs=1);

    /**
     * @brief Process given sample and updates transition progress.
     * 
     * @param x 
     * @return fxpt_Q0_31 
     */
    fxpt_Q0_31 process(fxpt_Q0_31 x = 0);

    friend std::ostream &operator<<(std::ostream &output, const DynamicBiquad &biquad)
    { 
        output << "DynamicBiquad(" <<
            fxpt_to_float(biquad.get_b0_target(), 30) << ", " << fxpt_to_float(biquad.get_b1_target(), 30) << ", " <<
            fxpt_to_float(biquad.get_b2_target(), 30) << ", " << fxpt_to_float(biquad.get_a0_target(), 30) << ", " <<
            fxpt_to_float(biquad.get_a1_target(), 30) << ", " << fxpt_to_float(biquad.get_a2_target(), 30) << ")";
        return output;            
    }
};


#endif //SYNTHPATHY_BIQUAD_H_