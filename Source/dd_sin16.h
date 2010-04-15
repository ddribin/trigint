#ifndef _DD_SIN16_H_
#define _DD_SIN16_H_

#include <stdint.h>

/**
 * dd_sin16_angle_t is a 14-bit angle, 0 - 0x3FFFF. This divides the circle
 * into 16,384 angles, instead of the standard 360 degrees.
 */
typedef uint16_t dd_sin16_angle_t;

#define DD_SIN16_ANGLE_MAX 0x3FFF

/**
 * Returns the sine of angle as signed 16-bit integer. It is scaled to an
 * amplitude of 32767, thus values will range from -32767 to +32767.
 */
int16_t dd_sin16(dd_sin16_angle_t angle);

#endif _DD_SIN16_H_
