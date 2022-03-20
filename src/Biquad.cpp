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

#include "Biquad.h"

#include <math.h>
#include <string.h>
#include "pico/stdlib.h"

Biquad::Biquad()
{
    m_coeffs[B0_IDX] = 1.f;
    for(unsigned int i = B1_IDX; i <= Z2_IDX; ++i)
    {
        m_coeffs[i] = 0.f;
    }
}

Biquad::Biquad(float b0, float b1, float b2, float a0, float a1, float a2)
{
    set_b0(b0);
    set_b1(b1);
    set_b2(b2);
    set_a1(a1);
    set_a2(a2);
    // Normalize if needed
    if(a0 != 1.f)
    {
        for(unsigned int i = B0_IDX; i <= A2_IDX; ++i)
        {
            m_coeffs[i] /= a0;
        }
    }
    // Initialize internal buffers
    set_z1(0.f);
    set_z2(0.f);
}

void Biquad::copy_coefficients(const Biquad &other)
{
    memcpy(m_coeffs, other.m_coeffs, (A2_IDX-B0_IDX+1)*sizeof(float));
}

Biquad Biquad::get_low_pass(float freq_cutoff, float sampling_rate, float Q)
{
    // Formulas can be found at :
    // https://webaudio.github.io/Audio-EQ-Cookbook/audio-eq-cookbook.html

    const float w_cutoff = 2.f * M_PI * freq_cutoff / sampling_rate;
    const float cos_w = cos(w_cutoff);
    const float alpha = sin(w_cutoff) / (2 * Q);
    return Biquad((1 - cos_w)/2, 1 - cos_w, (1 - cos_w)/2, 1 + alpha, -2*cos_w, 1 - alpha);
}

float Biquad::process(float x)
{
    // These equations are of the transposed direct form 2.
    const float y = get_b0() * x + get_z1();

    set_z1(get_b1() * x - get_a1() * y + get_z2());
    set_z2(get_b2() * x - get_a2() * y);

    return y;
}

DynamicBiquad::DynamicBiquad(const Biquad &biquad):
    // Copy given filter as current and target filter
    Biquad()
{
    memcpy(m_coeffs, biquad.get_coeffs(), (Z2_IDX-B0_IDX+1)*sizeof(float));
    memcpy(m_coeffs_target, biquad.get_coeffs(), (Z2_IDX-B0_IDX+1)*sizeof(float));
    // Initialize transition as instantaneous and over
    m_transition_duration_fs = 1;
    m_transition_elapsed_fs = 1;
}

void DynamicBiquad::set_target(const Biquad &target, unsigned int transition_duration_fs)
{
    // If transition was already in progress
    if(m_transition_elapsed_fs < m_transition_duration_fs)
    {
        // Copy current transition state as base filter
        const float l_ratio = static_cast<float>(m_transition_elapsed_fs) / m_transition_duration_fs;
        const float l_ratio_inv = 1.f - l_ratio;
        set_b0(l_ratio_inv*get_b0() + l_ratio*get_b0_target());
        set_b1(l_ratio_inv*get_b1() + l_ratio*get_b1_target());
        set_b2(l_ratio_inv*get_b2() + l_ratio*get_b2_target());
        set_a1(l_ratio_inv*get_a1() + l_ratio*get_a1_target());
        set_a2(l_ratio_inv*get_a2() + l_ratio*get_a2_target());
        set_z1(l_ratio_inv*get_z1() + l_ratio*get_z1_target());
        set_z2(l_ratio_inv*get_z2() + l_ratio*get_z2_target());
    }
    // If last transition is over
    else
    {
        // Copy target filter as base filter
        //memcpy(m_coeffs, m_coeffs_target, (Z2_IDX-B0_IDX+1)*sizeof(float));
        set_b0(get_b0_target());
        set_b1(get_b1_target());
        set_b2(get_b2_target());
        set_a1(get_a1_target());
        set_a2(get_a2_target());
        set_z1(get_z1_target());
        set_z2(get_z2_target());
    }
    // Copy given filter as target filter
    //memcpy(m_coeffs_target, target.get_coeffs(), (Z2_IDX-B0_IDX+1)*sizeof(float));
    set_b0_target(target.get_b0());
    set_b1_target(target.get_b1());
    set_b2_target(target.get_b2());
    set_a1_target(target.get_a1());
    set_a2_target(target.get_a2());
    set_z1_target(target.get_z1());
    set_z2_target(target.get_z2());
    // Reinitialize transition
    m_transition_duration_fs = transition_duration_fs;
    m_transition_elapsed_fs = 0;
}

float DynamicBiquad::process(float x)
{
    // Process target filter
    const float y_target = get_b0_target() * x + get_z1_target();
    set_z1_target(get_b1_target() * x - get_a1_target() * y_target + get_z2_target());
    set_z2_target(get_b2_target() * x - get_a2_target() * y_target);

    // If transition is over
    if(m_transition_elapsed_fs == m_transition_duration_fs)
    {
        return y_target;
    }
    // If transition in progress
    else
    {
        // Process base filter
        const float y = get_b0() * x + get_z1();
        set_z1(get_b1() * x - get_a1() * y + get_z2());
        set_z2(get_b2() * x - get_a2() * y);

        // Average both filters and increment transition elapsed time
        float l_ratio = static_cast<float>(++m_transition_elapsed_fs) / m_transition_duration_fs;
        return (1-l_ratio)*y + l_ratio*y_target;
    }
}
