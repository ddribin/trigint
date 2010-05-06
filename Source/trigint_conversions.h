//

#ifndef _TRIGINT_CONVERSIONS_H_
#define _TRIGINT_CONVERSIONS_H_

#include "trigint_types.h"

trigint_angle_t dd_sin16_degrees_to_angle_d(double degrees);
trigint_angle_t dd_sin16_degrees_to_angle_i(int degrees);

double dd_sin16_angle_to_degrees_d(trigint_angle_t angle);
int dd_sin16_angle_to_degrees_i(trigint_angle_t angle);

trigint_angle_t dd_sin16_radians_to_angle_d(double radians);
double dd_sin16_angle_to_radians_d(trigint_angle_t angle);

#endif