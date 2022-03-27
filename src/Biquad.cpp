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
#include <limits>
#include "pico/stdlib.h"

Biquad::Biquad()
{
    // Initialize coefficients
    m_coeffs[B0_IDX] = fxpt_Q1_30(1<<30);
    for(unsigned int i = B1_IDX; i <= A2_IDX; ++i)
    {
        m_coeffs[i] = 0;
    }
    // Initialize internal buffers
    set_z1(0);
    set_z2(0);
}

Biquad::Biquad(fxpt_Q1_30 b0, fxpt_Q1_30 b1, fxpt_Q1_30 b2, fxpt_Q1_30 a0, fxpt_Q1_30 a1, fxpt_Q1_30 a2)
{
    set_b0(b0);
    set_b1(b1);
    set_b2(b2);
    set_a1(a1);
    set_a2(a2);
    // Normalize if needed
    if(a0 != fxpt_Q1_30(1<<30))
    {
        for(unsigned int i = B0_IDX; i <= A2_IDX; ++i)
        {
            // Q1_30 times Q1_30 gives Q2_60, for division a conversion to Q_2_60 must be done first
            m_coeffs[i] = fxpt_convert_n((fxpt64_t)m_coeffs[i], 30, 60) / a0;
        }
    }
    // Initialize internal buffers
    set_z1(0);
    set_z2(0);
}

void Biquad::copy_coefficients(const Biquad &other)
{
    memcpy(m_coeffs, other.m_coeffs, (A2_IDX-B0_IDX+1)*sizeof(fxpt_Q1_30));
}

Biquad Biquad::get_low_pass(fxpt_UQ16_16 freq_cutoff, unsigned int sampling_rate, fxpt_UQ3_29 Q)
{
    // Formulas can be found at :
    // https://webaudio.github.io/Audio-EQ-Cookbook/audio-eq-cookbook.html

    // const float w_cutoff = 2.f * M_PI * freq_cutoff / sampling_rate;
    // const float cos_w = cos(w_cutoff);
    // const float alpha = sin(w_cutoff) / (2 * Q);
    // return Biquad((1 - cos_w)/2, 1 - cos_w, (1 - cos_w)/2, 1 + alpha, -2*cos_w, 1 - alpha);

    // fxpt_sin and fxpt_cos have period 1, 2*pi is hence unecessary
    const fxpt_Q21_10 w_cutoff = fxpt_convert_n(fxpt_convert_n((fxpt64_t)freq_cutoff, 16, 48) / sampling_rate, 48, 10);
    // 1 integer bit is given for compatibility with Biquad constructor
    const fxpt_Q1_30 cos_w = fxpt_convert_n(fxpt_cos(w_cutoff), 31, 30);
    // Q is in [1/sqrt(2) ; 8], sin is in [-1 ; 1], so alpha is in [-0.707 ; 0.707], and needs 0 integer bits, but 1 is given for constructor
    const fxpt_Q1_30 alpha = fxpt_convert_n((fxpt64_t)fxpt_sin(w_cutoff), 31, 59) / ((fxpt64_t)2 * (fxpt64_t)Q);
    constexpr fxpt_Q1_30 one = 1<<30;
    return Biquad((one - cos_w)/2, one - cos_w, (one - cos_w)/2, one + alpha, -2*cos_w, one - alpha);
}

fxpt_Q0_31 Biquad::process(fxpt_Q0_31 x)
{
    // These equations are of the transposed direct form 2.
    // const float y = get_b0() * x + get_z1();
    // set_z1(get_b1() * x - get_a1() * y + get_z2());
    // set_z2(get_b2() * x - get_a2() * y);

    const fxpt_Q0_31 y = 
        + fxpt_convert_n((fxpt64_t)get_b0() * (fxpt64_t)x, 61, 31)
        + fxpt_convert_n((fxpt64_t)get_z1(), 28, 31);

    set_z1(
        + fxpt_convert_n((fxpt64_t)get_b1() * (fxpt64_t)x, 61, 28)
        - fxpt_convert_n((fxpt64_t)get_a1() * (fxpt64_t)y, 61, 28)
        + fxpt_convert_n((fxpt64_t)get_z2(), 30, 28)
    );

    set_z2(
        + fxpt_convert_n((fxpt64_t)get_b2() * (fxpt64_t)x, 61, 30)
        - fxpt_convert_n((fxpt64_t)get_a2() * (fxpt64_t)y, 61, 30)
    );

    // TODO : fix non-zero output when input is zero for a long time
    return y;
}

DynamicBiquad::DynamicBiquad(const Biquad &biquad):
    Biquad()
{
    // Copy given filter as target filter, current filter is unecessary since it will be overwritten later
    set_b0_target(biquad.get_b0());
    set_b1_target(biquad.get_b1());
    set_b2_target(biquad.get_b2());
    set_a1_target(biquad.get_a1());
    set_a2_target(biquad.get_a2());
    set_z1_target(0);
    set_z2_target(0);
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
        const fxpt_Q0_31 l_ratio = fxpt_convert_n((fxpt64_t)m_transition_elapsed_fs, 0, 31) / m_transition_duration_fs;
        // 1 - ratio
        const fxpt_Q0_31 l_ratio_inv = std::numeric_limits<fxpt_Q0_31>::max() - l_ratio;
        set_b0(fxpt_convert_n((fxpt64_t)l_ratio_inv*(fxpt64_t)get_b0(), 61, 30) + fxpt_convert_n((fxpt64_t)l_ratio*(fxpt64_t)get_b0_target(), 61, 30));
        set_b1(fxpt_convert_n((fxpt64_t)l_ratio_inv*(fxpt64_t)get_b1(), 61, 30) + fxpt_convert_n((fxpt64_t)l_ratio*(fxpt64_t)get_b1_target(), 61, 30));
        set_b2(fxpt_convert_n((fxpt64_t)l_ratio_inv*(fxpt64_t)get_b2(), 61, 30) + fxpt_convert_n((fxpt64_t)l_ratio*(fxpt64_t)get_b2_target(), 61, 30));
        set_a1(fxpt_convert_n((fxpt64_t)l_ratio_inv*(fxpt64_t)get_a1(), 61, 30) + fxpt_convert_n((fxpt64_t)l_ratio*(fxpt64_t)get_a1_target(), 61, 30));
        set_a2(fxpt_convert_n((fxpt64_t)l_ratio_inv*(fxpt64_t)get_a2(), 61, 30) + fxpt_convert_n((fxpt64_t)l_ratio*(fxpt64_t)get_a2_target(), 61, 30));
        set_z1(fxpt_convert_n((fxpt64_t)l_ratio_inv*(fxpt64_t)get_z1(), 59, 28) + fxpt_convert_n((fxpt64_t)l_ratio*(fxpt64_t)get_z1_target(), 59, 28));
        set_z2(fxpt_convert_n((fxpt64_t)l_ratio_inv*(fxpt64_t)get_z2(), 61, 30) + fxpt_convert_n((fxpt64_t)l_ratio*(fxpt64_t)get_z2_target(), 61, 30));
    }
    // If last transition is over
    else
    {
        // Copy target filter as base filter
        set_b0(get_b0_target());
        set_b1(get_b1_target());
        set_b2(get_b2_target());
        set_a1(get_a1_target());
        set_a2(get_a2_target());
        set_z1(get_z1_target());
        set_z2(get_z2_target());
    }
    // Copy given filter as target filter
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

fxpt_Q0_31 DynamicBiquad::process(fxpt_Q0_31 x)
{
    // Process target filter
    const fxpt_Q0_31 y_target = 
        + fxpt_convert_n((fxpt64_t)get_b0_target() * (fxpt64_t)x, 61, 31)
        + fxpt_convert_n((fxpt64_t)get_z1_target(), 28, 31);

    set_z1_target(
        + fxpt_convert_n((fxpt64_t)get_b1_target() * (fxpt64_t)x, 61, 28)
        - fxpt_convert_n((fxpt64_t)get_a1_target() * (fxpt64_t)y_target, 61, 28)
        + fxpt_convert_n((fxpt64_t)get_z2_target(), 30, 28)
    );

    set_z2_target(
        + fxpt_convert_n((fxpt64_t)get_b2_target() * (fxpt64_t)x, 61, 30)
        - fxpt_convert_n((fxpt64_t)get_a2_target() * (fxpt64_t)y_target, 61, 30)
    );

    // If transition is over
    if(m_transition_elapsed_fs == m_transition_duration_fs)
    {
        return y_target;
    }
    // If transition in progress
    else
    {
        // Process base filter
        const fxpt_Q0_31 y = 
        + fxpt_convert_n((fxpt64_t)get_b0() * (fxpt64_t)x, 61, 31)
        + fxpt_convert_n((fxpt64_t)get_z1(), 28, 31);

        set_z1(
            + fxpt_convert_n((fxpt64_t)get_b1() * (fxpt64_t)x, 61, 28)
            - fxpt_convert_n((fxpt64_t)get_a1() * (fxpt64_t)y, 61, 28)
            + fxpt_convert_n((fxpt64_t)get_z2(), 30, 28)
        );

        set_z2(
            + fxpt_convert_n((fxpt64_t)get_b2() * (fxpt64_t)x, 61, 30)
            - fxpt_convert_n((fxpt64_t)get_a2() * (fxpt64_t)y, 61, 30)
        );

        // Average both filters and increment transition elapsed time
        // The -1 is to prevent overflow when elapsed == duration
        const fxpt_Q0_31 l_ratio = (fxpt_convert_n((fxpt64_t)(++m_transition_elapsed_fs), 0, 31)-1) / m_transition_duration_fs;
        const fxpt_Q0_31 l_ratio_inv = std::numeric_limits<fxpt_Q0_31>::max() - l_ratio;
        // TODO : fix non-zero output when input is zero for a long time
        return fxpt_convert_n((fxpt64_t)l_ratio_inv * (fxpt64_t)y, 62, 31)
             + fxpt_convert_n((fxpt64_t)l_ratio * (fxpt64_t)y_target, 62, 31);
    }
}
