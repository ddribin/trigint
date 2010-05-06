//

#ifndef _TRIGINT_TYPES_H_
#define _TRIGINT_TYPES_H_

#include <stdint.h>

/**
 * trigint_angle_t is a 14-bit angle, 0 - 0x3FFFF. This divides the circle
 * into 16,384 angles, instead of the standard 360 degrees.
 * Thus 1 angle unit =~ 360/16384 = 0.0219727 degrees
 *      1 angle unit =~ 2*M_PI/16384 = 0.0003835 radians
 */
typedef uint16_t trigint_angle_t;
typedef trigint_angle_t dd_sin16_angle_t;

#define DD_SIN16_ANGLE_MAX 0x3FFF
#define DD_SIN16_ANGLES_PER_CYCLE 0x4000


#endif
