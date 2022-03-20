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
     * index 5 : z1 (Transposed direct form 2)
     * index 6 : z2 (Transposed direct form 2)
     */
    float m_coeffs[7];

    static constexpr unsigned int B0_IDX = 0;
    static constexpr unsigned int B1_IDX = 1;
    static constexpr unsigned int B2_IDX = 2;
    static constexpr unsigned int A1_IDX = 3;
    static constexpr unsigned int A2_IDX = 4;
    static constexpr unsigned int Z1_IDX = 5;
    static constexpr unsigned int Z2_IDX = 6;

    /**
     * @brief Setters for the filter coefficients.
     * 
     * @{
     */
    inline void set_b0(float b0) { m_coeffs[B0_IDX] = b0; }
    inline void set_b1(float b1) { m_coeffs[B1_IDX] = b1; }
    inline void set_b2(float b2) { m_coeffs[B2_IDX] = b2; }
    inline void set_a1(float a1) { m_coeffs[A1_IDX] = a1; }
    inline void set_a2(float a2) { m_coeffs[A2_IDX] = a2; }
    /**@}*/

    /**
     * @brief Setters for the internal buffers.
     * 
     * @return float 
     * @{
     */
    inline void set_z1(float z1) { m_coeffs[Z1_IDX] = z1; }
    inline void set_z2(float z2) { m_coeffs[Z2_IDX] = z2; }
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
    Biquad(float b0, float b1, float b2, float a0, float a1, float a2);

    /**
     * @brief Getters for the filter coefficients.
     * 
     * @return float 
     * @{
     */
    inline float get_b0() const { return m_coeffs[B0_IDX]; }
    inline float get_b1() const { return m_coeffs[B1_IDX]; }
    inline float get_b2() const { return m_coeffs[B2_IDX]; }
    inline float get_a0() const { return 1.f; }
    inline float get_a1() const { return m_coeffs[A1_IDX]; }
    inline float get_a2() const { return m_coeffs[A2_IDX]; }
    /**@}*/

    /**
     * @brief Getters for the internal buffers.
     * 
     * @return float 
     * @{
     */
    inline float get_z1() const { return m_coeffs[Z1_IDX]; }
    inline float get_z2() const { return m_coeffs[Z2_IDX]; }
    /**@}*/

    /**
     * @brief Get the array where coefficients are stored.
     * 
     * @return const float* 
     */
    inline const float* get_coeffs() const { return m_coeffs; }

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
     * @param Q The quality factor.
     * @return Biquad 
     */
    static Biquad get_low_pass(float freq_cutoff, float sampling_rate, float Q = M_SQRT1_2);

    /**
     * @brief Process given sample.
     * 
     * @param x 
     * @return float 
     */
    float process(float x = 0.f);

    friend std::ostream &operator<<(std::ostream &output, const Biquad &biquad)
    { 
        output << "Biquad(" <<
            biquad.get_b0() << ", " << biquad.get_b1() << ", " <<
            biquad.get_b2() << ", " << biquad.get_a0() << ", " <<
            biquad.get_a1() << ", " << biquad.get_a2() << ")";
        return output;            
    }
};


class DynamicBiquad : public Biquad
{
protected:

    /**
     * @brief Biquad filter coefficients and internal buffers of the target filter.
     * index 0 : b0
     * index 1 : b1
     * index 2 : b2
     * index 3 : a1
     * index 4 : a2
     * index 5 : z1 (Transposed direct form 2)
     * index 6 : z2 (Transposed direct form 2)
     */
    float m_coeffs_target[7];

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
     * 
     * @{
     */
    inline void set_b0_target(float b0) { m_coeffs_target[B0_IDX] = b0; }
    inline void set_b1_target(float b1) { m_coeffs_target[B1_IDX] = b1; }
    inline void set_b2_target(float b2) { m_coeffs_target[B2_IDX] = b2; }
    inline void set_a1_target(float a1) { m_coeffs_target[A1_IDX] = a1; }
    inline void set_a2_target(float a2) { m_coeffs_target[A2_IDX] = a2; }
    /**@}*/

    /**
     * @brief Setters for the internal buffers.
     * 
     * @return float 
     * @{
     */
    inline void set_z1_target(float z1) { m_coeffs_target[Z1_IDX] = z1; }
    inline void set_z2_target(float z2) { m_coeffs_target[Z2_IDX] = z2; }
    /**@}*/

public:

    DynamicBiquad(const Biquad &biquad);

    /**
     * @brief Getters for the target filter coefficients.
     * 
     * @return float 
     * @{
     */
    inline float get_b0_target() const { return m_coeffs_target[B0_IDX]; }
    inline float get_b1_target() const { return m_coeffs_target[B1_IDX]; }
    inline float get_b2_target() const { return m_coeffs_target[B2_IDX]; }
    inline float get_a0_target() const { return 1.f; }
    inline float get_a1_target() const { return m_coeffs_target[A1_IDX]; }
    inline float get_a2_target() const { return m_coeffs_target[A2_IDX]; }
    /**@}*/

    /**
     * @brief Getters for the target filter internal buffers.
     * 
     * @return float 
     * @{
     */
    inline float get_z1_target() const { return m_coeffs_target[Z1_IDX]; }
    inline float get_z2_target() const { return m_coeffs_target[Z2_IDX]; }
    /**@}*/

    /**
     * @brief Sets the target to which this filter must tend.
     * 
     * @param target The target filter.
     * @param transition_duration_fs The duration of the transition in number of samples. The longer the smoother.
     */
    void set_target(const Biquad &target, unsigned int transition_duration_fs=1);

    /**
     * @brief Process given sample and updates filter.
     * 
     * @param x 
     * @return float 
     */
    float process(float x = 0.f);

};


#endif //SYNTHPATHY_BIQUAD_H_