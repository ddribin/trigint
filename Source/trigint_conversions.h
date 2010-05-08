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

#ifndef _TRIGINT_CONVERSIONS_H_
#define _TRIGINT_CONVERSIONS_H_

#include "trigint_types.h"
#include <math.h>

/**
 * @defgroup trigint_conversions Functions to convert between angle units
 * @{
 */

/**
 * Converts an angle from degrees, as a double, to trigint_angle_t.
 *
 * @param degrees an angle in degrees, as a double
 * @returns the angle as a trigint_angle_t
 */
inline trigint_angle_t trigint_degrees_to_angle_d(double degrees)
{
	trigint_angle_t angle = (trigint_angle_t)((degrees * TRIGINT_ANGLES_PER_CYCLE) / 360.0);
	return angle;
}

/**
 * Converts an angle from degrees, as an int to trigint_angle_t.
 *
 * @param degrees an anle in degrees, as an int
 * @returns the angle as a trigint_angle_t
 */
inline trigint_angle_t trigint_degrees_to_angle_i(int degrees)
{
	trigint_angle_t angle = (trigint_angle_t)((degrees * TRIGINT_ANGLES_PER_CYCLE) / 360);
	return angle;
}

/**
 * Converts an angle from trigint_angle_t to degrees, as a double.
 *
 * @param angle an angle as a trigint_angle_t
 * @returns the angle in degrees as a double
 */
inline double trigint_angle_to_degrees_d(trigint_angle_t angle)
{
    double angle_d = angle;
    double degrees = angle_d * 360 / TRIGINT_ANGLES_PER_CYCLE;
    return degrees;
}

/**
 * Converts an angle from trigint_angle_t to degrees, as an int.
 *
 * @param angle an angle as a trigint_angle_t
 * @returns the angle in degrees as an int
 */
inline int trigint_angle_to_degrees_i(trigint_angle_t angle)
{
    int angle_i = angle;
    int degrees = angle_i * 360 / TRIGINT_ANGLES_PER_CYCLE;
    return degrees;
}

/**
 * Converts an angle from radians, as a double to trigint_angle_t.
 *
 * @param radians an angle in radians, as a double
 * @returns the angle as a trigint_angle_t
 */
inline trigint_angle_t trigint_radians_to_angle_d(double radians)
{
	trigint_angle_t angle = (trigint_angle_t)((radians * TRIGINT_ANGLES_PER_CYCLE) / (2*M_PI));
	return angle;
}

/**
 * Converts an angle from trigint_angle_t to radians, as a double.
 *
 * @param angle an angle as a trigint_angle_t
 * @returns the angle in radians as a double
 */
inline double trigint_angle_to_radians_d(trigint_angle_t angle)
{
    double angle_d = angle;
    double radians = (angle_d * 2.0 * M_PI) / TRIGINT_ANGLES_PER_CYCLE;
    return radians;
}

/**
 * @}
 */

#endif
