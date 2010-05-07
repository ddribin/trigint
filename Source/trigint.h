//

#ifndef _TRIGINT_H_
#define _TRIGINT_H_

/**
 * @mainpage TrigInt: An Integer-based Trigonometry Library
 *
 * TrigInt is an integer-based trigonometry library.  The trigonometry
 * functions in the standard C library use floating point data types
 * (double or float), which may be too slow or unavailable in an
 * embedded environment.  This library uses only integer parameters,
 * return values, and calculations.  It uses lookup tables plus linear
 * interoplation to estimate the values.  The trade-off is accuracy,
 * but the accuracy, even with only 16 entry lookup tables, is often
 * sufficient.
 *
 * Because the standard C library uses radians as the angle unit, they
 * must be represented with a floating point types.  To avoid using
 * floating point for angles, a new angle unit is used,
 * ::trigint_angle_t.  This splits the circle into 16,384 angle units,
 * instead of 2*PI radians or 360 degrees.  Thus, the angle parameters
 * can be safetly stored in an unsigned 16-bit data type.
 *
 * This library is essentially a C version of the Scott Dattalo's <a
 * href="http://www.dattalo.com/technical/software/pic/picsine.html">
 * sine wave routine for the PIC microcontroller</a>.  Credit goes to
 * Scott for coming up with the algorithm.  He's also got a whole
 * write up of <a
 * href="http://www.dattalo.com/technical/theory/sinewave.html"> sine
 * wave theory</a>.
 */

#include "trigint_sin8.h"
#include "trigint_sin16.h"
#include "trigint_conversions.h"

#endif
