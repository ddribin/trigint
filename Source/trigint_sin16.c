/*
 * Copyright (c) 2010 Dave Dribin
 * 
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "trigint_sin16.h"
#include <stdbool.h>

/*
 * Implementation based off of:
 * http://www.dattalo.com/technical/software/pic/picsine.html
 *
 * trigint_angle_t is a 14-bit angle, 0 - 0x3FFFF
 *
 * xxQQTTTT IIIIPPPP
 * Q - Quadrant, 00 = quandrant 1, 01 = quadrant 2, etc.
 * T - Table index into sine16_table, SINE_INDEX_WIDTH.
 * I - Interpolation between successive entries in the table, SINE_INTERP_WIDTH.
 * P - Phase accumalation, may be zero width. Used for rounding.
 */

#define SINE_INDEX_WIDTH 4
#define SINE_INTERP_WIDTH 8

#if (SINE_INDEX_WIDTH + SINE_INTERP_WIDTH > 12)
# error Invalid sine widths
#endif
 
#define SINE_INDEX_OFFSET (12 - SINE_INDEX_WIDTH)
#define SINE_INTERP_OFFSET (SINE_INDEX_OFFSET - SINE_INTERP_WIDTH)
#define QUADRANT_HIGH_MASK (1 << 13)
#define QUADRANT_LOW_MASK (1 << 12)

/* Define a MAX macro if we don't already have one */
#ifndef MAX
# define MAX(a, b) ((a) < (b) ? (b) : (a))
#endif

#if SINE_INTERP_OFFSET > 0
# define SINE_ROUNDING (1 << (SINE_INTERP_OFFSET-1))
#else
# define SINE_ROUNDING (0)
#endif

#define SINE_TABLE_SIZE (1 << SINE_INDEX_WIDTH)

#ifndef TRIGINT_SIN16_STATIC_TABLE
# define TRIGINT_SIN16_STATIC_TABLE 1
#endif

#if TRIGINT_SIN16_STATIC_TABLE

// Table of the first quadrant values.  Size is + 1 to store the first value of
// the second quadrant, hence we're storing 0 <= degrees <= 90.

static const int16_t trigint_sin16_table[SINE_TABLE_SIZE + 1] = {
        0,  3211,  6392,  9511, 12539, 15446, 18204, 20787,
    23169, 25329, 27244, 28897, 30272, 31356, 32137, 32609,
    32767
};

#else

static int16_t trigint_sin16_table[SINE_TABLE_SIZE + 1];

#endif

#define SINE_TABLE_COUNT (sizeof(trigint_sin16_table)/sizeof(*trigint_sin16_table))


#define BITS(_VALUE_, _WIDTH_, _BIT_) (((_VALUE_) >> (_BIT_)) & ((1 << (_WIDTH_)) - 1))


int trigint_sin16_table_size()
{
    return SINE_TABLE_COUNT;
}

inline int16_t trigint_sin16_table_lookup(int index)
{
    return trigint_sin16_table[index];
}

int16_t trigint_sin16(trigint_angle_t angle)
{
    angle += SINE_ROUNDING;
	int32_t interp = BITS(angle, SINE_INTERP_WIDTH, SINE_INTERP_OFFSET);
	uint8_t index = BITS(angle, SINE_INDEX_WIDTH, SINE_INDEX_OFFSET);

	bool isOddQuadrant = (angle & QUADRANT_LOW_MASK) == 0;
	bool isNegativeQuadrant = (angle & QUADRANT_HIGH_MASK) != 0;
    
	if (!isOddQuadrant) {
		index = SINE_TABLE_SIZE - 1 - index;
	}
	
    // Do calculations with 32 bits since the multiplication can overflow 16 bits
	int32_t x1 = trigint_sin16_table_lookup(index);
	int32_t x2 = trigint_sin16_table_lookup(index+1);
    int32_t approximation = ((x2-x1) * interp) >> SINE_INTERP_WIDTH;
    
	int16_t sine;
	if (isOddQuadrant) {
		sine = x1 + approximation;
	} else {
		sine = x2 - approximation;
	}
    
	if (isNegativeQuadrant) {
		sine *= -1;
	}

	return sine;
}

#pragma mark -

#if !TRIGINT_SIN16_STATIC_TABLE
#include <math.h>

void trigint_sin16_init()
{
	for (int i = 0; i < SINE_TABLE_COUNT; i++) {
		double radians = i * M_PI_2 / SINE_TABLE_SIZE;
		double sinValue = 32767.0 * sin(radians);
		int16_t tableValue = round(sinValue);
        trigint_sin16_table[i] = tableValue;
	}
}

#endif
