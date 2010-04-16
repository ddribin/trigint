#ifndef _DD_SIN16_H_
#define _DD_SIN16_H_

#include <stdint.h>

/**
 * dd_sin16_angle_t is a 14-bit angle, 0 - 0x3FFFF. This divides the circle
 * into 16,384 angles, instead of the standard 360 degrees.
 * Thus 1 angle unit =~ 360/16384 = 0.0219727 degrees
 *      1 angle unit =~ 2*M_PI/16384 = 0.0003835 radians
 */
typedef uint16_t dd_sin16_angle_t;

#define DD_SIN16_ANGLE_MAX 0x3FFF

dd_sin16_angle_t dd_sin16_degrees_to_angle_d(double degrees);
dd_sin16_angle_t dd_sin16_degrees_to_angle_i(int degrees);

double dd_sin16_angle_to_degrees_d(dd_sin16_angle_t angle);
int dd_sin16_angle_to_degrees_i(dd_sin16_angle_t angle);

dd_sin16_angle_t dd_sin16_radians_to_angle_d(double radians);
double dd_sin16_angle_to_radians_d(dd_sin16_angle_t angle);


/**
 * Returns the sine of angle as signed 16-bit integer. It is scaled to an
 * amplitude of 32,767, thus values will range from -32,767 to +32,767.
 */
int16_t dd_sin16(dd_sin16_angle_t angle);

/**
 * Prints the table values.
 */
void dd_sin16_table();

#endif _DD_SIN16_H_
