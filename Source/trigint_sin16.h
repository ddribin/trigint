//

#ifndef _TRIGINT_SIN16_H_
#define _TRIGINT_SIN16_H_

#include "trigint_types.h"

/**
 * @defgroup trigint16 Trigonometry functions returning 16-bit integer values
 * @{
 */


/**
 * Returns the sine of angle as signed 16-bit integer. It is scaled to an
 * amplitude of 32,767, thus values will range from -32,767 to +32,767.
 *
 * @param angle the angle to compute the sine of
 * @return the sine value, as a signed 16-bit integer
 */
int16_t trigint_sin16(trigint_angle_t angle);

/**
 * Returns the size of the lookup table used for signed 16-bit integers.
 *
 * @return the size of the lookup table used for signed 16-bit integers
 *
 * @note This is generally only needed for debugging purposes.
 */
int trigint_sin16_table_size();

/**
 * Lookup a specific table entry for the given index.
 *
 * @param index
 * @return the 16-bit signed value at the table entry
 *
 * @note This is generally only needed for debugging purposes.
 */
int16_t trigint_sin16_table_lookup(int index);

#ifndef TRIGINT_SIN16_STATIC_TABLE
/**
 * Compile time macro that can be used to disable the static (compile-time)
 * lookup table.  This can be used to reduce compiled code size at the
 * expense of requiring a call to trigint_sin16_init() at runtime.
 */
# define TRIGINT_SIN16_STATIC_TABLE 1
#endif

#if !TRIGINT_SIN16_STATIC_TABLE

/**
 * Initialize the dynamic table. Must be called before any calls to
 * trigint_sin16().  This is only necessary and available if the
 * #TRIGINT_SIN16_STATIC_TABLE macro is set to 0.
 */
void trigint_sin16_init();

#endif

/**
 * @}
 */

#endif
