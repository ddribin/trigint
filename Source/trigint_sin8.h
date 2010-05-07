//

#ifndef _TRIGINT_SIN8_H_
#define _TRIGINT_SIN8_H_

#include "trigint_types.h"

/**
 * @defgroup trigint8 Trigonometry functions returning 8-bit integer values
 * @{
 */


/**
 * Returns the sine of angle as an unsigned 8-bit integer. It is scaled to an
 * amplitude of 127 and offset by 128 thus values will range from 1 to 255.
 *
 * @param angle the angle to compute the sine of
 * @return the sine value, as an unsigned 8-bit integer
 *
 * @sa http://en.wikipedia.org/wiki/Offset_binary
 */
uint8_t trigint_sin8u(trigint_angle_t angle);

/**
 * Returns the sine of angle as a signed 8-bit integer. It is scaled to an
 * amplitude of 127 thus values will range from -127 to 127.
 *
 * @param angle the angle to compute the sine of
 * @return the sine value, as an unsigned 8-bit integer
 *
 * @note There is no table for signed 8-bit computations.  It is computed
 * from the unsigned sine value.
 */
inline int8_t trigint_sin8(trigint_angle_t angle)
{
    return trigint_sin8u(angle) ^ 0x80;
}

/**
 * Returns the size of the lookup table used for unsigned 8-bit integers.
 *
 * @return the size of the lookup table used for unsigned 8-bit integers
 *
 * @note This is generally only needed for debugging purposes.
 */
int trigint_sin8u_table_size();

/**
 * Lookup a specific table entry for the given index.
 *
 * @param index
 * @return the 8-bit unsigned value at the table entry
 *
 * @note This is generally only needed for debugging purposes.
 */
uint8_t trigint_sin8u_table_lookup(int index);

#ifndef TRIGINT_SIN8_STATIC_TABLE
/**
 * Compile time macro that can be used to disable the static (compile-time)
 * lookup table.  This can be used to reduce compiled code size at the
 * expense of requiring a call to trigint_sin8_init() at runtime.
 */
# define TRIGINT_SIN8_STATIC_TABLE 1
#endif

#if !TRIGINT_SIN8_STATIC_TABLE

/**
 * Initialize the dynamic table. Must be called before any calls to
 * trigint_sin8u() or trigint_sin8().  This is only necessary and available
 * if the #TRIGINT_SIN8_STATIC_TABLE macro is set to 0.
 */
void trigint_sin8_init();

#endif

/**
 * @}
 */

#endif