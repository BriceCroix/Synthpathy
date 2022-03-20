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
     * @brief Biquad filter coefficients.
     * 
     */
    float m_b0, m_b1, m_b2, m_a1, m_a2;

    /**
     * @brief Biquad filter coeffcicient a0, always 1 when filter is normalized.
     * 
     */
    static constexpr float m_a0 = 1.f;

    /**
     * @brief The internal buffers.
     * These correspond to the transposed direct form 2.
     */
    float m_z1, m_z2;


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
    inline float get_b0() const { return m_b0; }
    inline float get_b1() const { return m_b1; }
    inline float get_b2() const { return m_b2; }
    inline float get_a0() const { return m_a0; }
    inline float get_a1() const { return m_a1; }
    inline float get_a2() const { return m_a2; }
    /**@}*/

    /**
     * @brief Getters for the internal buffers.
     * 
     * @return float 
     * @{
     */
    inline float get_z1() const { return m_z1; }
    inline float get_z2() const { return m_z2; }
    /**@}*/

    /**
     * @brief Copy the coefficients of another filter on current filter.
     * This does not reset the internal buffer.
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
            biquad.m_b0 << ", " << biquad.m_b1 << ", " <<
            biquad.m_b2 << ", " << biquad.m_a0 << ", " <<
            biquad.m_a1 << ", " << biquad.m_a2 << ")";
        return output;            
    }
};


class DynamicBiquad : public Biquad
{
protected:

    /**
     * @brief Target biquad filter coefficients.
     * 
     */
    float m_b0_target, m_b1_target, m_b2_target, m_a1_target, m_a2_target;

    /**
     * @brief The internal buffers of the target biquad
     * These correspond to the transposed direct form 2.
     */
    float m_z1_target, m_z2_target;

    /**
     * @brief Tells how fast a filter moves to its target.
     * Between 0 (filter does not move) and 1 (filter moves instantly)
     */
    static constexpr float transition_rate = 0.1;

    /**
     * @brief 1 minus transition rate.
     * 
     */
    static constexpr float transition_rate_inv = 1. - transition_rate;

public:

    DynamicBiquad(const Biquad &biquad);

    /**
     * @brief Sets the target to which this filter must tend.
     * 
     * @param target The target filter.
     */
    void set_target(const Biquad &target);

    /**
     * @brief Process given sample and updates filter.
     * 
     * @param x 
     * @return float 
     */
    float process(float x = 0.f);

};


#endif //SYNTHPATHY_BIQUAD_H_