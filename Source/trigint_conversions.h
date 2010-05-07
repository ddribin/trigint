//

#ifndef _TRIGINT_CONVERSIONS_H_
#define _TRIGINT_CONVERSIONS_H_

#include "trigint_types.h"
#include <math.h>

/**
 * @defgroup conversion Functions to convert between angle units
 * @{
 */

/**
 * Converts an angle from degrees, as a double, to trigint_angle_t.
 *
 * @param degrees Degress, as a double
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
 * @param degrees Degress, as an int
 * @returns the angle as a trigint_angle_t
 */
inline trigint_angle_t trigint_degrees_to_angle_i(int degrees)
{
	trigint_angle_t angle = (trigint_angle_t)((degrees * TRIGINT_ANGLES_PER_CYCLE) / 360);
	return angle;
}

/**
 * Converts an angle from trigint_angle_t to degrees, as a double
 *
 * @param angle an angle as a trigint_angle_t
 * @returns the angle as a double
 */
inline double trigint_angle_to_degrees_d(trigint_angle_t angle)
{
    double angle_d = angle;
    double degrees = angle_d * 360 / 0x4000;
    return degrees;
}

/**
 */
inline int trigint_angle_to_degrees_i(trigint_angle_t angle)
{
    int angle_i = angle;
    int degrees = angle_i * 360 / 0x4000;
    return degrees;
}

/**
 */
inline trigint_angle_t trigint_radians_to_angle_d(double radians)
{
	trigint_angle_t angle = (trigint_angle_t)((radians * 0x4000) / (2*M_PI));
	return angle;
}

/**
 */
inline double trigint_angle_to_radians_d(trigint_angle_t angle)
{
    double angle_d = angle;
    double radians = (angle_d * 2.0 * M_PI) / 0x4000;
    return radians;
}

/**
 * @}
 */

#endif