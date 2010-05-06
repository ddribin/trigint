//

#import "Sin16Test.h"
#include "trigint_sin16.h"
#include "trigint_conversions.h"
#include <math.h>



void trigint_sin16_dump_table()
{
    int table_size = trigint_sin16_table_size();
	for (int i = 0; i < table_size; i++) {
		double degrees = i * 90.0 / table_size;
		int16_t tableValue = trigint_sin16_table_lookup(i);
        printf("%.3f, %d\n", degrees, tableValue);
	}
}

@implementation Sin16Test

#if !TRIGINT_SIN16_STATIC_TABLE
- (void)setUp
{
    trigint_sin16_init();
}
#endif

- (int16_t)sin:(double)degrees
{
    double radians = degrees * 2 * M_PI / 360.0;
    double sinValue = sin(radians) * 32767.0;
    return (int16_t)round(sinValue);
}

- (int16_t)sin16:(double)degrees
{
    trigint_angle_t angle = trigint_degrees_to_angle_d(degrees);
    int16_t sinValue = trigint_sin16(angle);
    return sinValue;
}

- (void)testSin16WithNoInterpolation
{
    STAssertEquals([self sin16:0],     (int16_t)0, nil);
    STAssertEquals([self sin16:90.0],  (int16_t)32767, nil);
    STAssertEquals([self sin16:180.0], (int16_t)0, nil);
    STAssertEquals([self sin16:270.0], (int16_t)-32767, nil);
    STAssertEquals([self sin16:360.0], (int16_t)0, nil);
}

- (void)assertSineWithinError:(double)degrees
{
    static const int accuracy = 42;
    int16_t value = [self sin16:degrees];
    int16_t expected = [self sin:degrees];
    int16_t error = abs(value - expected);
    STAssertTrue(error <= accuracy,
                 [NSString stringWithFormat:@"sin(%.2f) is %u, should be %u +- %u, error was %u",
                  degrees, value, expected, accuracy, error]);
}

- (void)testSin16WithInterpolation
{
    for (double degrees = 0; degrees <= 360.0; degrees += 0.1) {
        [self assertSineWithinError:degrees];
    }
}

@end
