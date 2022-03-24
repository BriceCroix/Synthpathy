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

#ifndef SYNTHPATHY_FXPT_H_
#define SYNTHPATHY_FXPT_H_

#include "pico/stdlib.h"

/**
 * @brief Converts decimal number in fixed point representation Qmi.ni to Qmo.no.
 * This also works with unsigned fixed-point UQmi.ni to UQmo.no.
 * Notice that for s the total number of bits :
 * - signed Q : n = s-m-1
 * - unsigned UQ : n = s-m
 */
#define fxpt_convert_m(x, mi, mo) (((mo) >= (mi)) ? fxpt_inc_step((x), (mo)-(mi)) : fxpt_dec_step((x),(mi)-(mo)))

/**
 * @brief Converts decimal number in fixed point representation Qmi.ni to Qmo.no.
 * This also works with unsigned fixed-point UQmi.ni to UQmo.no.
 * Notice that for s the total number of bits :
 * - signed Q : n = s-m-1
 * - unsigned UQ : n = s-m
 */
#define fxpt_convert_n(x, ni, no) (((no) > (ni)) ? fxpt_dec_step((x), (no)-(ni)) : fxpt_inc_step((x), (ni)-(no)))

/**
 * @brief Gain decimal precision on a fixed-point value.
 * Decrease the step from one value to the next.
 * Example : fxpt_gain_prec(fxpt_Q5_10, 2) = fxpt_Q3_12.
 */
#define fxpt_dec_step(x, prec) ((x) << (prec))

/**
 * @brief Lose decimal precision on a fixed-point value (truncating).
 * Increase the step from one value to the next.
 * Example : fxpt_lose_prec(fxpt_Q5_10, 2) = fxpt_Q7_8.
 */
#define fxpt_inc_step(x, prec) ((x) >> (prec))

/**
 * @brief Maps signed to unsigned fixed-point values and vice-versa,
 * by adding or subtracting adequatly.
 * For instance, on 8-bit integers, converting from signed to unsigned adds 128, and
 * from unsigned to signed subtracts 128.
 * @{
 */
#define fxpt8_signed_unsigned_map(x)  ((x) ^ (1<<7))
#define fxpt16_signed_unsigned_map(x) ((x) ^ (1<<15))
#define fxpt32_signed_unsigned_map(x) ((x) ^ (1<<31))
/**@}*/

/**
 * @brief Lose decimal precision on a fixed-point value (rounding).
 * Increase the step from one value to the next.
 * Example : fxpt_lose_prec(fxpt_Q5_10, 2) = fxpt_Q7_8.
 */
#define fxpt_inc_step_round(x, prec) (((x) + (1 << ((prec)-1))) >> (prec))

/**
 * @brief Converts fixed-point value with n decimal bits to floating-point value.
 * 
 */
#define fxpt_to_float(x, n) ((n>0) ? ((float)(x) / (1<<(n))) : ((float)(x) * (1<<(-(n)))));

/**
 * @brief Converts floating-point value to fixed-point with n decimal bits.
 * 
 */
#define fxpt_from_float(x, n) (((n)>0) ? ((x) * (1<<(n))) : ((x) / (1<<(-(n)))))

/**
 * @brief Unsigned value in fixed-point representation.
 * 
 */
typedef unsigned int ufxpt;

/**
 * @brief Signed value in fixed-point representation.
 * 
 */
typedef int fxpt;

/**
 * @brief Unsigned value in 8-bits fixed-point representation.
 * @{
 */
typedef uint8_t ufxpt8_t;
typedef uint8_t fxpt_UQ0_8;
typedef uint8_t fxpt_UQ1_7;
typedef uint8_t fxpt_UQ2_6;
typedef uint8_t fxpt_UQ3_5;
typedef uint8_t fxpt_UQ4_4;
typedef uint8_t fxpt_UQ5_3;
typedef uint8_t fxpt_UQ6_2;
typedef uint8_t fxpt_UQ7_1;
/**@}*/

/**
 * @brief Signed value in 8-bits fixed-point representation.
 * @{
 */
typedef int8_t fxpt8_t;
typedef int8_t fxpt_Q0_7;
typedef int8_t fxpt_Q1_6;
typedef int8_t fxpt_Q2_5;
typedef int8_t fxpt_Q3_4;
typedef int8_t fxpt_Q4_3;
typedef int8_t fxpt_Q5_2;
typedef int8_t fxpt_Q6_1;
/**@}*/

/**
 * @brief Unsigned value in 16-bits fixed-point representation.
 * @{
 */
typedef uint16_t ufxpt16_t;
typedef uint16_t fxpt_UQ0_16;
typedef uint16_t fxpt_UQ1_15;
typedef uint16_t fxpt_UQ2_14;
typedef uint16_t fxpt_UQ3_13;
typedef uint16_t fxpt_UQ4_12;
typedef uint16_t fxpt_UQ5_11;
typedef uint16_t fxpt_UQ6_10;
typedef uint16_t fxpt_UQ7_9;
typedef uint16_t fxpt_UQ8_8;
typedef uint16_t fxpt_UQ9_7;
typedef uint16_t fxpt_UQ10_6;
typedef uint16_t fxpt_UQ11_5;
typedef uint16_t fxpt_UQ12_4;
typedef uint16_t fxpt_UQ13_3;
typedef uint16_t fxpt_UQ14_2;
typedef uint16_t fxpt_UQ15_1;
/**@}*/

/**
 * @brief Signed value in 16-bits fixed-point representation.
 * @{
 */
typedef int16_t fxpt16_t;
typedef int16_t fxpt_Q0_15;
typedef int16_t fxpt_Q1_14;
typedef int16_t fxpt_Q2_13;
typedef int16_t fxpt_Q3_12;
typedef int16_t fxpt_Q4_11;
typedef int16_t fxpt_Q5_10;
typedef int16_t fxpt_Q6_9;
typedef int16_t fxpt_Q7_8;
typedef int16_t fxpt_Q8_7;
typedef int16_t fxpt_Q9_6;
typedef int16_t fxpt_Q10_5;
typedef int16_t fxpt_Q11_4;
typedef int16_t fxpt_Q12_3;
typedef int16_t fxpt_Q13_2;
typedef int16_t fxpt_Q14_1;
/**@}*/

/**
 * @brief Unsigned value in 32-bits fixed-point representation.
 * @{
 */
typedef uint32_t ufxpt32_t;
typedef uint32_t fxpt_UQ0_32;
typedef uint32_t fxpt_UQ1_31;
typedef uint32_t fxpt_UQ2_30;
typedef uint32_t fxpt_UQ3_29;
typedef uint32_t fxpt_UQ4_28;
typedef uint32_t fxpt_UQ5_27;
typedef uint32_t fxpt_UQ6_26;
typedef uint32_t fxpt_UQ7_25;
typedef uint32_t fxpt_UQ8_24;
typedef uint32_t fxpt_UQ9_23;
typedef uint32_t fxpt_UQ10_22;
typedef uint32_t fxpt_UQ11_21;
typedef uint32_t fxpt_UQ12_20;
typedef uint32_t fxpt_UQ13_19;
typedef uint32_t fxpt_UQ14_18;
typedef uint32_t fxpt_UQ15_17;
typedef uint32_t fxpt_UQ16_16;
typedef uint32_t fxpt_UQ17_15;
typedef uint32_t fxpt_UQ18_14;
typedef uint32_t fxpt_UQ19_13;
typedef uint32_t fxpt_UQ20_12;
typedef uint32_t fxpt_UQ21_11;
typedef uint32_t fxpt_UQ22_10;
typedef uint32_t fxpt_UQ23_9;
typedef uint32_t fxpt_UQ24_8;
typedef uint32_t fxpt_UQ25_7;
typedef uint32_t fxpt_UQ26_6;
typedef uint32_t fxpt_UQ27_5;
typedef uint32_t fxpt_UQ28_4;
typedef uint32_t fxpt_UQ29_3;
typedef uint32_t fxpt_UQ30_2;
typedef uint32_t fxpt_UQ31_1;
/**@}*/

/**
 * @brief Signed value in 32-bits fixed-point representation.
 * @{
 */
typedef int32_t fxpt32_t;
typedef int32_t fxpt_Q0_31;
typedef int32_t fxpt_Q1_30;
typedef int32_t fxpt_Q2_29;
typedef int32_t fxpt_Q3_28;
typedef int32_t fxpt_Q4_27;
typedef int32_t fxpt_Q5_26;
typedef int32_t fxpt_Q6_25;
typedef int32_t fxpt_Q7_24;
typedef int32_t fxpt_Q8_23;
typedef int32_t fxpt_Q9_22;
typedef int32_t fxpt_Q10_21;
typedef int32_t fxpt_Q11_20;
typedef int32_t fxpt_Q12_19;
typedef int32_t fxpt_Q13_18;
typedef int32_t fxpt_Q14_17;
typedef int32_t fxpt_Q15_16;
typedef int32_t fxpt_Q16_15;
typedef int32_t fxpt_Q17_14;
typedef int32_t fxpt_Q18_13;
typedef int32_t fxpt_Q19_12;
typedef int32_t fxpt_Q20_11;
typedef int32_t fxpt_Q21_10;
typedef int32_t fxpt_Q22_9;
typedef int32_t fxpt_Q23_8;
typedef int32_t fxpt_Q24_7;
typedef int32_t fxpt_Q25_6;
typedef int32_t fxpt_Q26_5;
typedef int32_t fxpt_Q27_4;
typedef int32_t fxpt_Q28_3;
typedef int32_t fxpt_Q29_2;
typedef int32_t fxpt_Q30_1;
/**@}*/

/**
 * @brief Unsigned value in 64-bits fixed-point representation.
 * 
 */
typedef uint64_t ufxpt64_t;

/**
 * @brief Signed value in 64-bits fixed-point representation.
 * 
 */
typedef int64_t fxpt64_t;

#define FXPT_SINE_LUT_SIZE 256
#define FXPT_SINE_LUT_IDX_MSK (FXPT_SINE_LUT_SIZE-1)
#define FXPT_SINE_PERIOD (4*FXPT_SINE_LUT_SIZE)

/**
 * @brief Quarter of a period of a sine wave, in fixed-point representation.
 * These values are actually shifted by half a sample in order to preserve symmetries
 * between quarters of period :
 * FXPT_SINE_LUT_QUARTER_Q0_31[i] = sin(2*pi*(2*i+1) / (2*FXPT_SINE_PERIOD))
 */
static fxpt_Q0_31 FXPT_SINE_LUT_QUARTER_Q0_31[FXPT_SINE_LUT_SIZE] =
{
    0x006487E2, 0x012D96B0, 0x01F6A296, 0x02BFA9A4, 0x0388A9E9, 0x0451A176, 0x051A8E5B, 0x05E36EA9, 
    0x06AC406F, 0x077501BE, 0x083DB0A7, 0x09064B3A, 0x09CECF89, 0x0A973BA5, 0x0B5F8D9F, 0x0C27C389, 
    0x0CEFDB75, 0x0DB7D376, 0x0E7FA99D, 0x0F475BFE, 0x100EE8AD, 0x10D64DBC, 0x119D8940, 0x1264994D, 
    0x132B7BF9, 0x13F22F57, 0x14B8B17F, 0x157F0086, 0x16451A83, 0x170AFD8D, 0x17D0A7BB, 0x18961727, 
    0x195B49E9, 0x1A203E1B, 0x1AE4F1D5, 0x1BA96334, 0x1C6D9053, 0x1D31774D, 0x1DF5163F, 0x1EB86B46, 
    0x1F7B7480, 0x203E300D, 0x21009C0B, 0x21C2B69C, 0x22847DDF, 0x2345EFF7, 0x24070B07, 0x24C7CD32, 
    0x2588349D, 0x26483F6C, 0x2707EBC6, 0x27C737D2, 0x288621B9, 0x2944A7A2, 0x2A02C7B8, 0x2AC08025, 
    0x2B7DCF17, 0x2C3AB2B9, 0x2CF72939, 0x2DB330C7, 0x2E6EC792, 0x2F29EBCC, 0x2FE49BA6, 0x309ED555, 
    0x3158970D, 0x3211DF03, 0x32CAAB6F, 0x3382FA88, 0x343ACA87, 0x34F219A7, 0x35A8E624, 0x365F2E3B, 
    0x3714F029, 0x37CA2A2F, 0x387EDA8E, 0x3932FF87, 0x39E6975D, 0x3A99A057, 0x3B4C18B9, 0x3BFDFECD, 
    0x3CAF50DA, 0x3D600D2B, 0x3E10320D, 0x3EBFBDCC, 0x3F6EAEB8, 0x401D0320, 0x40CAB957, 0x4177CFB0, 
    0x42244480, 0x42D0161E, 0x437B42E1, 0x4425C923, 0x44CFA73F, 0x4578DB93, 0x4621647C, 0x46C9405C, 
    0x47706D93, 0x4816EA85, 0x48BCB598, 0x4961CD32, 0x4A062FBD, 0x4AA9DBA1, 0x4B4CCF4D, 0x4BEF092D, 
    0x4C9087B1, 0x4D31494B, 0x4DD14C6E, 0x4E708F8F, 0x4F0F1126, 0x4FACCFAA, 0x5049C998, 0x50E5FD6C, 
    0x518169A4, 0x521C0CC1, 0x52B5E545, 0x534EF1B5, 0x53E73097, 0x547EA073, 0x55153FD4, 0x55AB0D46, 
    0x56400757, 0x56D42C99, 0x57677B9C, 0x57F9F2F7, 0x588B913F, 0x591C550D, 0x59AC3CFD, 0x5A3B47AA, 
    0x5AC973B4, 0x5B56BFBD, 0x5BE32A67, 0x5C6EB258, 0x5CF95638, 0x5D8314B0, 0x5E0BEC6E, 0x5E93DC1E, 
    0x5F1AE273, 0x5FA0FE1E, 0x60262DD5, 0x60AA704F, 0x612DC446, 0x61B02876, 0x62319B9D, 0x62B21C7B, 
    0x6331A9D4, 0x63B0426D, 0x642DE50D, 0x64AA907F, 0x6526438E, 0x65A0FD0A, 0x661ABBC5, 0x66937E90, 
    0x670B4443, 0x67820BB6, 0x67F7D3C4, 0x686C9B4B, 0x68E06129, 0x69532442, 0x69C4E37A, 0x6A359DB9, 
    0x6AA551E8, 0x6B13FEF4, 0x6B81A3CD, 0x6BEE3F62, 0x6C59D0A9, 0x6CC45697, 0x6D2DD027, 0x6D963C53, 
    0x6DFD9A1B, 0x6E63E87F, 0x6EC92682, 0x6F2D532C, 0x6F906D84, 0x6FF27496, 0x70536771, 0x70B34524, 
    0x71120CC5, 0x716FBD67, 0x71CC5626, 0x7227D61C, 0x72823C66, 0x72DB8828, 0x7333B883, 0x738ACC9E, 
    0x73E0C3A3, 0x74359CBD, 0x7489571B, 0x74DBF1EF, 0x752D6C6C, 0x757DC5CA, 0x75CCFD42, 0x761B1211, 
    0x76680376, 0x76B3D0B3, 0x76FE790E, 0x7747FBCE, 0x7790583D, 0x77D78DAA, 0x781D9B64, 0x786280BF, 
    0x78A63D10, 0x78E8CFB1, 0x792A37FE, 0x796A7554, 0x79A98715, 0x79E76CA6, 0x7A24256E, 0x7A5FB0D8, 
    0x7A9A0E4F, 0x7AD33D45, 0x7B0B3D2C, 0x7B420D7A, 0x7B77ADA8, 0x7BAC1D31, 0x7BDF5B94, 0x7C116853, 
    0x7C4242F2, 0x7C71EAF8, 0x7CA05FF1, 0x7CCDA168, 0x7CF9AEF0, 0x7D24881A, 0x7D4E2C7E, 0x7D769BB5, 
    0x7D9DD55A, 0x7DC3D90D, 0x7DE8A670, 0x7E0C3D29, 0x7E2E9CDF, 0x7E4FC53E, 0x7E6FB5F3, 0x7E8E6EB1, 
    0x7EABEF2C, 0x7EC8371A, 0x7EE34635, 0x7EFD1C3C, 0x7F15B8ED, 0x7F2D1C0E, 0x7F434563, 0x7F5834B6, 
    0x7F6BE9D4, 0x7F7E648B, 0x7F8FA4AF, 0x7F9FAA15, 0x7FAE7494, 0x7FBC040A, 0x7FC85853, 0x7FD37152, 
    0x7FDD4EEC, 0x7FE5F108, 0x7FED5790, 0x7FF38273, 0x7FF871A1, 0x7FFC250F, 0x7FFE9CB2, 0x7FFFD885, 
};

/**
 * @brief Fixed-point sine function of period 1 ( fxpt_sin(x) = sin(2*pi*x) )
 * Divide input by 2pi for true sine function.
 * This uses a look-up table of size 256, which allows for a period of 1024 samples (using sine properties).
 * @param x The phase between in fixed-point representation (or index in the period of size 1024).
 * @return fxpt_Q0_31 
 */
inline fxpt_Q0_31 fxpt_sin(fxpt_Q5_10 x)
{
    // Inspired from https://zipcpu.com/dsp/2017/08/26/quarterwave.html

    // NB : following computation only work with LUT of sizes power of two
    // Compute index in LUT (if x in second or fourth period quarter, idx = -x-1, else idx = x)
    const uint8_t l_idx = ((x & (FXPT_SINE_PERIOD>>2)) ? ~x : x) & FXPT_SINE_LUT_IDX_MSK;
    // Handle minus sign on second half of period
    return (x & (FXPT_SINE_PERIOD>>1)) ? -FXPT_SINE_LUT_QUARTER_Q0_31[l_idx] : FXPT_SINE_LUT_QUARTER_Q0_31[l_idx];
}

/**
 * @brief Fixed-point cosine function of period 1 ( fxpt_sin(x) = sin(2*pi*x) )
 * Divide input by 2pi for true cosine function.
 * This calls fxpt_sin using sine-cosine relations.
 * @param x The phase between in fixed-point representation (or index in the period of size 1024).
 * @return fxpt_Q0_31 
 */
inline fxpt_Q0_31 fxpt_cos(fxpt_UQ6_10 x)
{
    return fxpt_sin(x + FXPT_SINE_LUT_SIZE);
}

/**
 * @brief Base two logarithm on integers.
 * This actually returns the position of the mostly significant 1 bit.
 * Warning : this returns 0 if x is 0, although bit 0 is not set.
 * @param x 
 * @return unsigned int 
 */
inline unsigned int fxpt_log2(unsigned int x)
{
    // It is possible on ARM to use clz instruction (Count Leading Zero), for optimization

    unsigned int res = 0;
    while (x > 1)
    {
        x >>= 1;
        res++;
    }
    return res;
}

/**
 * @brief Decimal precision of base two logarithm on 8 bits integers.
 * log2int is written on 3 bits (log2(8) = 3), it remains 5 bits for more precision.
 */
#define FXPT8_LOG2_DEC_PREC 5

/**
 * @brief Piece-wise linear base two logarithm on 8 bits unsigned integers.
 * 
 * @param x 
 * @return fxpt_UQ3_5
 */
inline fxpt_UQ3_5 fxpt8_log2(uint8_t x)
{
    // Compute position of mostly significant 1 bit
    const uint8_t msb = fxpt_log2(x);
    // A mask to recover bits behind msb
    const uint8_t msk = (1<<(msb)) - 1;
    /*
    if(msb < FXPT8_LOG2_DEC_PREC)
    {
        return (msb<<FXPT8_LOG2_DEC_PREC) | ((x & msk) << (FXPT8_LOG2_DEC_PREC-msb));
    }
    else
    {
        return (msb<<FXPT8_LOG2_DEC_PREC) | ((x & msk) >> (msb-FXPT8_LOG2_DEC_PREC));
    }
    */
    // Handle right/left shift
    return (msb<<FXPT8_LOG2_DEC_PREC) |
        ((msb < FXPT8_LOG2_DEC_PREC) ? ((x & msk) << (FXPT8_LOG2_DEC_PREC-msb)) : ((x & msk) >> (msb-FXPT8_LOG2_DEC_PREC)));
}

/**
 * @brief Fixed-point power of 2 function on 8-bit values.
 * fxpt_pow2(x) = pow(2, x);
 * @param x 
 * @return uint8_t 
 */
inline uint8_t fxpt8_pow2(fxpt_UQ3_5 x)
{
    // Recover position of most significant set bit (in output)
    const uint8_t l_msb = x >> FXPT8_LOG2_DEC_PREC;
    return (1 << l_msb) | ((l_msb>FXPT8_LOG2_DEC_PREC) ?
            (x & ((1<<FXPT8_LOG2_DEC_PREC)-1)) << l_msb-FXPT8_LOG2_DEC_PREC :
            (x & ((1<<FXPT8_LOG2_DEC_PREC)-1)) >> FXPT8_LOG2_DEC_PREC-l_msb);
}

/**
 * @brief Decimal precision of base two logarithm on 16 bits integers.
 * log2int is written on 4 bits (log2(16) = 4), it remains 12 bits for more precision.
 */
#define FXPT16_LOG2_DEC_PREC 12

/**
 * @brief Piece-wise linear base two logarithm on 16 bits unsigned integers.
 * 
 * @param x 
 * @return fxpt_UQ4_12
 */
inline fxpt_UQ4_12 fxpt16_log2(uint16_t x)
{
    const uint16_t msb = fxpt_log2(x);
    const uint16_t msk = (1<<(msb)) - 1;
    return (msb<<FXPT16_LOG2_DEC_PREC) |
        ((msb < FXPT16_LOG2_DEC_PREC) ? ((x & msk) << (FXPT16_LOG2_DEC_PREC-msb)) : ((x & msk) >> (msb-FXPT16_LOG2_DEC_PREC)));
}

/**
 * @brief Fixed-point power of 2 function on 16-bit values.
 * fxpt_pow2(x) = pow(2, x);
 * @param x 
 * @return uint16_t 
 */
inline uint16_t fxpt16_pow2(fxpt_UQ4_12 x)
{
    const uint8_t l_msb = x >> FXPT16_LOG2_DEC_PREC;
    return (1 << l_msb) | ((l_msb>FXPT16_LOG2_DEC_PREC) ?
            (x & ((1<<FXPT16_LOG2_DEC_PREC)-1)) << l_msb-FXPT16_LOG2_DEC_PREC :
            (x & ((1<<FXPT16_LOG2_DEC_PREC)-1)) >> FXPT16_LOG2_DEC_PREC-l_msb);
}

/**
 * @brief Decimal precision of base two logarithm on 32 bits integers.
 * log2int is written on 5 bits (log2(32) = 5), it remains 27 bits for more precision.
 */
#define FXPT32_LOG2_DEC_PREC 27

/**
 * @brief Piece-wise linear base two logarithm on 32 bits unsigned integers.
 * 
 * @param x 
 * @return fxpt_UQ5_27
 */
inline fxpt_UQ5_27 fxpt32_log2(uint32_t x)
{
    const uint16_t msb = fxpt_log2(x);
    const uint16_t msk = (1<<(msb)) - 1;
    return (msb<<FXPT32_LOG2_DEC_PREC) |
        ((msb < FXPT32_LOG2_DEC_PREC) ? ((x & msk) << (FXPT32_LOG2_DEC_PREC-msb)) : ((x & msk) >> (msb-FXPT32_LOG2_DEC_PREC)));
}

/**
 * @brief Fixed-point power of 2 function on 32-bit values.
 * fxpt_pow2(x) = pow(2, x);
 * @param x 
 * @return uint32_t 
 */
inline uint32_t fxpt32_pow2(fxpt_UQ5_27 x)
{
    const uint8_t l_msb = x >> FXPT32_LOG2_DEC_PREC;
    return (1 << l_msb) | ((l_msb>FXPT32_LOG2_DEC_PREC) ?
            (x & ((1<<FXPT32_LOG2_DEC_PREC)-1)) << l_msb-FXPT32_LOG2_DEC_PREC :
            (x & ((1<<FXPT32_LOG2_DEC_PREC)-1)) >> FXPT32_LOG2_DEC_PREC-l_msb);
}

#endif //SYNTHPATHY_FXPT_H_