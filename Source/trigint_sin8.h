#ifndef _TRIGINT_SIN8_H_
#define _TRIGINT_SIN8_H_

#include "trigint_types.h"


/**
 * Returns the sine of angle as an unsigned 8-bit integer. It is scaled to an
 * amplitude of 127 and offset by 128 thus values will range from 1 to 255.
 */
uint8_t trigint_sin8u(trigint_angle_t angle);

inline int8_t trigint_sin8(trigint_angle_t angle)
{
    return trigint_sin8u(angle) ^ 0x80;
}

int trigint_sin8u_table_size();
uint8_t trigint_sin8u_table_lookup(int index);

#ifndef TRIGINT_SIN8_STATIC_TABLE
# define TRIGINT_SIN8_STATIC_TABLE 0
#endif

#if !TRIGINT_SIN8_STATIC_TABLE

/**
 * Initialize the dynamic table. Must be called before any calls to trigint_sin8u().
 */
void trigint_sin8u_init();

#endif

#endif
