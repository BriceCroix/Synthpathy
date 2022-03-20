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
}

void DynamicBiquad::set_target(const Biquad &target)
{
    // Copy given filter as target filter
    memcpy(m_coeffs_target, target.get_coeffs(), (Z2_IDX-B0_IDX+1)*sizeof(float));
}

float DynamicBiquad::process(float x)
{
    // Process current filter
    const float y = get_b0() * x + get_z1();
    set_z1(get_b1() * x - get_a1() * y + get_z2());
    set_z2(get_b2() * x - get_a2() * y);

    // Process target filter
    const float y_target = get_b0_target() * x + get_z1_target();
    set_z1_target(get_b1_target() * x - get_a1_target() * y + get_z2_target());
    set_z2_target(get_b2_target() * x - get_a2_target() * y);

    // Update filter
    set_b0(transition_rate_inv * get_b0() + transition_rate * get_b0_target());
    set_b1(transition_rate_inv * get_b1() + transition_rate * get_b1_target());
    set_b2(transition_rate_inv * get_b2() + transition_rate * get_b2_target());
    set_a1(transition_rate_inv * get_a1() + transition_rate * get_a1_target());
    set_a2(transition_rate_inv * get_a2() + transition_rate * get_a2_target());;
    set_z1(transition_rate_inv * get_z1() + transition_rate * get_z1_target());
    set_z2(transition_rate_inv * get_z2() + transition_rate * get_z2_target());

    // Return updated output
    return transition_rate_inv * y + transition_rate * y_target;
}
