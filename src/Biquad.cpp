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