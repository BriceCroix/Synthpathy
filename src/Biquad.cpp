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

Biquad::Biquad()
{
    m_b0 = 1.f;
    m_b1, m_b2, m_a1, m_a2, m_z1, m_z2 = 0.f;
}

Biquad::Biquad(float b0, float b1, float b2, float a0, float a1, float a2):
    m_b0(b0), m_b1(b1), m_b2(b2), m_a1(a1), m_a2(a2)
{
    // Normalize if needed
    if(a0 != 1.f)
    {
        m_b0 /= a0;
        m_b1 /= a0;
        m_b2 /= a0;
        m_a1 /= a0;
        m_a2 /= a0;
    }
    // Initialize internal buffers
    m_z1, m_z2 = 0.f;
}

void Biquad::copy_coefficients(const Biquad &other)
{
    m_b0 = other.m_b0;
    m_b1 = other.m_b1;
    m_b2 = other.m_b2;
    m_a1 = other.m_a1;
    m_a2 = other.m_a2;
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
    const float y = m_b0 * x + m_z1;

    m_z1 = m_b1 * x - m_a1 * y + m_z2;
    m_z2 = m_b2 * x - m_a2 * y;

    return y;
}

DynamicBiquad::DynamicBiquad(const Biquad &biquad):
    // Copy given filter as current and target filter
    Biquad(biquad.get_b0(), biquad.get_b1(), biquad.get_b2(), biquad.get_a0(), biquad.get_a1(), biquad.get_a2()),
    m_b0_target(biquad.get_b0()), m_b1_target(biquad.get_b1()), m_b2_target(biquad.get_b2()),
    m_a1_target(biquad.get_a1()), m_a2_target(biquad.get_a2()),
    m_z1_target(biquad.get_z1()), m_z2_target(biquad.get_z2())
{
    m_z1 = biquad.get_z1();
    m_z2 = biquad.get_z2();
}

void DynamicBiquad::set_target(const Biquad &target)
{
    // Copy given filter as target filter
    m_b0_target = target.get_b0();
    m_b1_target = target.get_b1();
    m_b2_target = target.get_b2();
    m_a1_target = target.get_a1();
    m_a2_target = target.get_a2();
    m_z1_target = target.get_z1();
    m_z2_target = target.get_z2();
}

float DynamicBiquad::process(float x)
{
    // Process current filter
    const float y = m_b0 * x + m_z1;
    m_z1 = m_b1 * x - m_a1 * y + m_z2;
    m_z2 = m_b2 * x - m_a2 * y;

    // Process target filter
    const float y_target = m_b0_target * x + m_z1_target;
    m_z1_target = m_b1_target * x - m_a1_target * y_target + m_z2_target;
    m_z2_target = m_b2_target * x - m_a2_target * y_target;

    // Update filter
    m_b0 = transition_rate_inv * m_b0 + transition_rate * m_b0_target;
    m_b1 = transition_rate_inv * m_b1 + transition_rate * m_b1_target;
    m_b2 = transition_rate_inv * m_b2 + transition_rate * m_b2_target;
    m_a1 = transition_rate_inv * m_a1 + transition_rate * m_a1_target;
    m_a2 = transition_rate_inv * m_a2 + transition_rate * m_a2_target;
    m_z1 = transition_rate_inv * m_z1 + transition_rate * m_z1_target;
    m_z2 = transition_rate_inv * m_z2 + transition_rate * m_z2_target;

    // Return updated output
    return transition_rate_inv * y + transition_rate * y_target;
}
