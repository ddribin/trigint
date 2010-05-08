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

#ifndef _TRIGINT_H_
#define _TRIGINT_H_

/**
 * @mainpage trigint: An Integer-based Trigonometry Library
 *
 * trigint is an integer-based trigonometry library.  The trigonometry
 * functions in the standard C library use floating point data types
 * (double or float), which may be too slow or unavailable in an
 * embedded environment.  This library uses only integer parameters,
 * return values, and calculations.
 *
 * Because the standard C library uses radians as the angle unit, they
 * must be represented with a floating point types.  To avoid using
 * floating point for angles, a new angle unit is used,
 * ::trigint_angle_t.  This splits the circle into 16,384 angle units,
 * instead of 2*PI radians or 360 degrees.  Thus, the angle parameters
 * can be safetly stored in an unsigned 16-bit data type.
 *
 * The original purpose of this library was to generate sine waves for
 * audio, so the main functions are:
 *
 *   - trigint_sin16(), a function that returns sine values as a signed 16-bit integer
 *   - trigint_sin8u(), a function that returns sine values as an unsigned 8-bit integer
 *
 * @see @ref trigint_sin16
 * @see @ref trigint_sin8
 *
 * These functions use lookup tables plus linear interoplation to
 * estimate the values.  The trade-off is accuracy, but the accuracy,
 * even with only 16 entry lookup tables, is often sufficient. See the
 * @ref accuracy page for more error analysis.
 *
 * This library is essentially a C version of the Scott Dattalo's <a
 * href="http://www.dattalo.com/technical/software/pic/picsine.html">
 * sine wave routine for the PIC microcontroller</a>.  Credit goes to
 * Scott for coming up with the algorithm.  He's also got a whole
 * write up of <a
 * href="http://www.dattalo.com/technical/theory/sinewave.html"> sine
 * wave theory</a>.
 */

/**
 * @page accuracy Accuracy of trigint_sin16
 *
 * The <a
 * href="http://en.wikipedia.org/wiki/Approximation_error">absolute
 * error</a> for a given angle can be calculated as follows:
 *
 * @code
 int16_t sin16_value = trigint_sin16(angle);
 double radians = trigint_angle_to_radians_d(angle);
 int16_t sin_value = round(32767.0 * sin(radians));
 int16_t absolute_error = abs(sin16_value - sin_value);
 * @endcode 
 *
 * Here's a plot of the absolute error for an entire sine wave cycle,
 * superimposed on top of the actual trigint_sin16() values.  As you
 * can see, the maximum absolute error is 40, which is very good,
 * given a range of -32,767 to +32,767 for the sine values.  This is
 * certainly good enough for music synthesis.
 *
 * @image html sin16_error.png
 *
 */

#include "trigint_sin8.h"
#include "trigint_sin16.h"
#include "trigint_conversions.h"

#endif
