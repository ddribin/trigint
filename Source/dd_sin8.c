/*
 *  trigint_sin8.c
 *  sin16
 *
 *  Created by Dave Dribin on 5/4/10.
 *  Copyright 2010 Bit Maki, Inc. All rights reserved.
 *
 */

#include "dd_sin8.h"
#include <stdbool.h>

#define SINE_INDEX_WIDTH 4
#define SINE_INTERP_WIDTH 4

/*
 * Implementation based off of:
 * http://www.dattalo.com/technical/software/pic/picsine.html
 *
 * dd_sin16_angle_t is a 14-bit angle, 0 - 0x3FFFF
 *
 * xxQQTTTT IIIIPPPP
 * Q - Quadrant, 00 = quandrant 1, 01 = quadrant 2, etc.
 * T - Table index into sine16_table, SINE_INDEX_WIDTH.
 * I - Interpolation between successive entries in the table, SINE_INTERP_WIDTH.
 * P - Phase accumalation, may be zero width. Used for rounding.
 */

#if (SINE_INDEX_WIDTH + SINE_INTERP_WIDTH > 12)
# error Invalid sine widths
#endif

#define SINE_INDEX_OFFSET (12 - SINE_INDEX_WIDTH)
#define SINE_INTERP_OFFSET (SINE_INDEX_OFFSET - SINE_INTERP_WIDTH)

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

#ifndef TRIGINT_SIN8_STATIC_TABLE
# define TRIGINT_SIN8U_STATIC_TABLE 1
#endif

#if TRIGINT_SIN8U_STATIC_TABLE

// Table of the first quadrant values.  Size is + 1 to store the first value of
// the second quadrant, hence we're storing 0 <= degrees <= 90.

static const uint8_t trigint_sine8u_table[SINE_TABLE_SIZE + 1] = {
    128, 140, 153, 165, 177, 188, 199, 209,
    218, 226, 234, 240, 245, 250, 253, 254,
    255
};

#else

uint8_t trigint_sine8u_table[SINE_TABLE_SIZE + 1];

#endif

#define SINE_TABLE_COUNT (sizeof(trigint_sine8u_table)/sizeof(*trigint_sine8u_table))


#define BITS(_VALUE_, _WIDTH_, _BIT_) (((_VALUE_) >> (_BIT_)) & ((1 << (_WIDTH_)) - 1))

int trigint_sin8u_table_size()
{
    return SINE_TABLE_COUNT;
}

inline uint8_t trigint_sin8u_table_lookup(int index)
{
    return trigint_sine8u_table[index];
}


#if 0
uint8_t trigint_sin8u(trigint_angle_t angle)
{
    double radians = dd_sin16_angle_to_radians_d(angle);
    double value = (127.0 * sin(radians)) + 128.0;
    return round(value);
}
#else
uint8_t trigint_sin8u(trigint_angle_t angle)
{
    angle += SINE_ROUNDING;
	uint16_t interp = BITS(angle, SINE_INTERP_WIDTH, SINE_INTERP_OFFSET);
	uint8_t index = BITS(angle, SINE_INDEX_WIDTH, SINE_INDEX_OFFSET);
	uint8_t quadrant = BITS(angle, 2, 12);
    
	bool isOddQuadrant = (quadrant & 0x01) == 0;
	bool isNegativeQuadrant = (quadrant & 0x02) != 0;
    
	if (!isOddQuadrant) {
		index = SINE_TABLE_SIZE - 1 - index;
	}
	
    // Do calculations with 16 bits since the multiplication can overflow 8 bits
	uint16_t x1 = trigint_sin8u_table_lookup(index);
	uint16_t x2 = trigint_sin8u_table_lookup(index+1);
    uint16_t approximation = ((x2-x1) * interp) >> SINE_INTERP_WIDTH;
    
	uint8_t sine;
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
#endif


#if 1
#include <math.h>
#include <stdio.h>


void trigint_sin8_table_gen()
{
    char * sep = "";
	for (int i = 0; i < SINE_TABLE_COUNT; i++) {
		double radians = i * M_PI_2 / SINE_TABLE_SIZE;
		double sinValue = 127.0 * sin(radians) + 128.0;
		uint8_t tableValue = round(sinValue);
		printf("%s%3d", sep, tableValue);
        if (((i+1) % 8) == 0) {
            sep = ",\n";
        } else {
            sep = ", ";
        }
	}
    printf("\n");
}

#if !TRIGINT_SIN8U_STATIC_TABLE
void trigint_sin8u_init()
{
	for (int i = 0; i < SINE_TABLE_COUNT; i++) {
		double radians = i * M_PI_2 / SINE_TABLE_SIZE;
		double sinValue = 127.0 * sin(radians) + 128.0;
		uint8_t tableValue = round(sinValue);
        trigint_sine8u_table[i] = tableValue;
	}
}
#endif
#endif