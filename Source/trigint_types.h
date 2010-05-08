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

#ifndef _TRIGINT_TYPES_H_
#define _TRIGINT_TYPES_H_

#include <stdint.h>

/**
 * @defgroup trigint_types Data types and constants
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
