#ifndef _TRIGINT_SIN16_H_
#define _TRIGINT_SIN16_H_

#include "trigint_types.h"


/**
 * Returns the sine of angle as signed 16-bit integer. It is scaled to an
 * amplitude of 32,767, thus values will range from -32,767 to +32,767.
 */
int16_t dd_sin16(trigint_angle_t angle);

int trigint_sin16_table_size();
int16_t trigint_sin16_table_lookup(int index);

#ifndef DD_SIN16_STATIC_TABLE
# define DD_SIN16_STATIC_TABLE 1
#endif

#if !DD_SIN16_STATIC_TABLE

/**
 * Initialize the dynamic table. Must be called before any calls to dd_sin16().
 */
void trigint_sin16_init();

#endif

#endif // _DD_SIN16_H_
