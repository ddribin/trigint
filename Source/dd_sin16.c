#include "dd_sin16.h"
#include <stdbool.h>

/*
 * http://www.dattalo.com/technical/software/pic/picsine.html
 */

/*
 * dd_sin16_angle_t is a 14-bit angle, 0 - 0x3FFFF
 *
 * xxQQTTTT IIIIIIII
 * QQ - Quadrant, 00 = quandrant 1, 01 = quadrant 2, etc.
 * TTTT - Table index into sine16_table
 * IIIIIIII - Interpolation between successive entries in the table 
 */

#define SINE_INDEX_WIDTH 4
#define SINE_INTERP_WIDTH 8

#if (SINE_INDEX_WIDTH + SINE_INTERP_WIDTH > 12)
# error Invalid sine widths
#endif

#define SINE_INDEX_OFFSET (12 - SINE_INDEX_WIDTH)
#define SINE_INTERP_OFFSET (SINE_INDEX_OFFSET - SINE_INTERP_WIDTH)

#define SINE_TABLE_SIZE (1 << SINE_INDEX_WIDTH)
static int16_t sine16_table[SINE_TABLE_SIZE + 1];

#define BITS(_V_, _W_, _O_) (((_V_) >> (_O_)) & ((1 << (_W_)) - 1))


dd_sin16_angle_t dd_degrees_to_angle_d(double degrees)
{
	dd_sin16_angle_t angle = (dd_sin16_angle_t)((degrees * 0x4000) / 360.0);
	return angle;
}

dd_sin16_angle_t dd_degrees_to_angle_i(int degrees)
{
	dd_sin16_angle_t angle = (dd_sin16_angle_t)((degrees * 0x4000) / 360);
	return angle;
}

int16_t dd_sin16(dd_sin16_angle_t angle)
{
#if 0
	uint8_t interp = (angle >> 0) & 0xff;
	uint8_t index = (angle >> 8) & 0x0f;
	uint8_t quadrant = (angle >> 12) & 0x03;
#else
	int32_t interp = BITS(angle, SINE_INTERP_WIDTH, SINE_INTERP_OFFSET);
	uint8_t o_index = BITS(angle, SINE_INDEX_WIDTH, SINE_INDEX_OFFSET);
	uint8_t quadrant = BITS(angle, 2, 12);
#endif
	bool isOdd = (quadrant & 0x01) == 0;
	bool isNeg = (quadrant & 0x02) != 0;
	uint8_t index = o_index;
	if (!isOdd) {
		index = SINE_TABLE_SIZE - 1 - o_index;
	}
	
	
	int32_t x1 = sine16_table[index];
	int32_t x2 = sine16_table[index+1];
#if 0
	int32_t diff = (x2-x1);
	int32_t step = diff * (int32_t)interp;
	int32_t shift = step >> SINE_INTERP_WIDTH;
	int32_t sine = x1 + shift;
#elif 0
	int16_t sine = x1 + (((int32_t)(x2-x1)) * (int32_t)interp) >> SINE_INTERP_WIDTH;
#else
	int32_t shift = ((x2-x1) * interp) >> SINE_INTERP_WIDTH;
	int16_t sine;
	if (isOdd) {
		sine = x1 + shift;
	}
	else {
		sine = x2 - shift;
	}
	if (isNeg) {
		sine *= -1;
	}
#endif
	return sine;
}
