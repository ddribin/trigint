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
 * trigint is an integer-based trigonometry library for ANSI C.  The
 * trigonometry functions in the standard C library use floating point
 * data types (double or float), which may be too slow or unavailable
 * in an embedded environment.  This library uses only integer
 * parameters, return values, and calculations.  It has been tested on
 * the <a href="http://developer.apple.com/iphone/">iPhone</a> with
 * Xcode and on an <a href="http://www.atmel.com/products/avr/">Atmel
 * AVR</a> microcontroller with <a
 * href="http://www.avrfreaks.net/wiki/index.php/Documentation:AVR_GCC">avr-gcc</a>,
 * but it is written in ANSI C99, and should work anywhere with a
 * modern C compiler.
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
 * estimate the values for speed.  The lookup tables are very small,
 * only 16 entries, to conserve space.  See the @ref
 * performance-ios page for the speed gains on iOS compared
 * to the standard library functions.  The trade-off for linear
 * inerpolation is accuracy, but the accuracy, even with only 16 entry
 * lookup tables, is often sufficient, epsecialy when generating
 * audio. See the @ref accuracy page for more error analysis.
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

/**
 * @page performance-ios Performance of trigint_sin16 on iOS
 *
 * iOS devices run on ARM processors.  While the ARM processor
 * is capable of performing floating point calculations in hardware,
 * it is still faster to execute integer-based calculations.  Also,
 * iOS applications are compiled in Thumb mode, by default.  While
 * thumb mode can reduce the code size by up to 35%, Apple recommends
 * applications that make extensive use of floating point math compile
 * without Thumb mode.
 *
 * Using the trigint library on iOS not only provides much
 * faster trigonometry calculations, but it allows applications to be
 * compiled in Thumb mode, since no floating point is used.
 * 
 * The following graph shows the performance gains on a 1st generation
 * iPod Touch between trigint_sin16() and the standard library sinf()
 * and sin() functions:
 *
 * @image html sin16_perf.png
 *
 * The sinf() and sin() functions were used to calcuate an integer
 * value between -32,767 and +32,767 as such:
 *
 * @code
 int16_t sinf_value = roundf(32767.0f * sinf(angle));
 int16_t sin_value = round(32767.0 * sin(angle));
 * @endcode
 *
 * trigint_sin16() is about 4.4 times faster than sinf() and 6.7 times
 * faster than sin() in Thumb mode.  Without Thumb mode, the gap
 * closes a bit to 3.8 times faster and 6.2 times faster,
 * respectively.
 *
 * Note that the floating point values are converted to an integer
 * using the standard roundf() and round() functions plus a cast.  If
 * you don't need the accuracy, you can skip the roundf() or round()
 * and just use a cast.  This increases performace by about 15% (in
 * Thumb mode), but accuracy is lost as the floating point to integer
 * conversion just truncates the fractional part.  trigint_sin16()
 * does rounding, which is why roundf() and round() were used for the
 * benchmarks.
 */

#include "trigint_sin8.h"
#include "trigint_sin16.h"
#include "trigint_conversions.h"

#endif
