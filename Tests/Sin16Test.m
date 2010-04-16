//

#import "Sin16Test.h"
#include "dd_sin16.h"
#include <math.h>


@implementation Sin16Test

- (int16_t)sin:(double)degrees
{
    double radians = degrees * 2 * M_PI / 360.0;
    double sinValue = sin(radians) * 32767.0;
    return (int16_t)sinValue;
}

- (int16_t)sin16:(double)degrees
{
    dd_sin16_angle_t angle = dd_sin16_degrees_to_angle_d(degrees);
    int16_t sinValue = dd_sin16(angle);
    return sinValue;
}

- (void)testSin16WithNoInterpolation
{
    STAssertEquals([self sin16:0],     [self sin:0], nil);
    STAssertEquals([self sin16:90.0],  [self sin:90.0], nil);
    STAssertEquals([self sin16:180.0], [self sin:180.0], nil);
    STAssertEquals([self sin16:270.0], [self sin:270.0], nil);
    STAssertEquals([self sin16:360.0], [self sin:360.0], nil);
}

- (void)assertSine:(double)degrees
{
    static const int accuracy = 100;
    int16_t value = [self sin16:degrees];
    int16_t expected = [self sin:degrees];
    int16_t error = abs(value - expected);
    STAssertTrue(error <= accuracy,
                 [NSString stringWithFormat:@"sin(%.2f) is %u, should be %u +- %u, error was %u",
                  degrees, value, expected, accuracy, error]);
}

- (void)testSin16WithInterpolation
{
    for (double degrees = 0; degrees <= 360.0; degrees += 1.0) {
        [self assertSine:degrees];
    }
}

@end
