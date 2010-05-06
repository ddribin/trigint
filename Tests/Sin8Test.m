//
//  Sin8Test.m
//  sin16
//
//  Created by Dave Dribin on 5/4/10.
//  Copyright 2010 Bit Maki, Inc. All rights reserved.
//

#import "Sin8Test.h"

#include "trigint_sin8.h"
#include "trigint_conversions.h"
#include <math.h>

void trigint_sin8u_dump_table()
{
    int sin_table_size = trigint_sin8u_table_size();
	for (int i = 0; i < sin_table_size; i++) {
		double degrees = i * 90.0 / sin_table_size;
		int tableValue = trigint_sin8u_table_lookup(i);
        printf("%.3f, %d\n", degrees, tableValue ^ 0x80);
	}
}


@implementation Sin8Test

// #if !TRIGINT_SIN16_STATIC_TABLE
- (void)setUp
{
#if !TRIGINT_SIN8_STATIC_TABLE
    trigint_sin8u_init();
    trigint_sin8u_dump_table();
#endif
    
#if 0
    trigint_sin8_table_gen();
#endif
}
// #endif

- (uint8_t)sin:(double)degrees
{
    double radians = degrees * 2 * M_PI / 360.0;
    double sinValue = (127.0 * sin(radians)) + 128.0;
    return (uint8_t)round(sinValue);
}

- (uint8_t)sin8u:(double)degrees
{
    trigint_angle_t angle = trigint_degrees_to_angle_d(degrees);
    uint8_t sinValue = trigint_sin8u(angle);
    return sinValue;
}

- (void)testSinUnsigned8WithNoInterpolation
{
    STAssertEquals((int)[self sin8u:0],     128, nil);
    STAssertEquals((int)[self sin8u:90.0],  255, nil);
    STAssertEquals((int)[self sin8u:180.0], 128, nil);
    STAssertEquals((int)[self sin8u:270.0], 1, nil);
    STAssertEquals((int)[self sin8u:360.0], 128, nil);
}

- (void)assertSineWithinError:(double)degrees
{
    static const int accuracy = 2;
    int16_t value = [self sin8u:degrees];
    int16_t expected = [self sin:degrees];
    int16_t error = abs(value - expected);
    STAssertTrue(error <= accuracy,
                 [NSString stringWithFormat:@"sin(%.2f) is %u, should be %u +- %u, error was %u",
                  degrees, value, expected, accuracy, error]);
}

- (void)testSin8WithInterpolation
{
    for (double degrees = 0; degrees <= 360.0; degrees += 0.1) {
        [self assertSineWithinError:degrees];
    }
}

@end