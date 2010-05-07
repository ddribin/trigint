//

#ifndef _TRIGINT_TYPES_H_
#define _TRIGINT_TYPES_H_

#include <stdint.h>

/**
 * @defgroup types Data types and constants
 * @{
 */

/**
 * A 14-bit angle, 0 - 0x3FFFF. This divides the circle
 * into 16,384 angle units, instead of the standard 360 degrees.
 * Thus:
 *   - 1 angle unit =~ 360/16384 =~ 0.0219727 degrees
 *   - 1 angle unit =~ 2*M_PI/16384 =~ 0.0003835 radians
 */
typedef uint16_t trigint_angle_t;

/**
 * The number of angle units per sine wave cycle.  In other words, the number
 * of angle units in a circle.
 */
#define TRIGINT_ANGLES_PER_CYCLE 0x4000

/**
 * The maximum angle value, before rolling over to the next cycle.  Can
 * be used as a mask to keep the angle within the nominal values:
 *
 * @code
 * trigint_angle_t angle = ... ;
 * angle += phaseOffset;
 * angle &= TRIGINT_ANGLE_MAX;
 * @endcode
 */
#define TRIGINT_ANGLE_MAX 0x3FFF

/**
 * @}
 */

#endif
