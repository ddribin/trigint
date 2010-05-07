//

#import "ConversionsTest.h"
#include "trigint_conversions.h"
#include <math.h>


@implementation ConversionsTest

- (void)testDegreesToAngleInt
{
    STAssertEquals(trigint_degrees_to_angle_i(0),   (trigint_angle_t)0x0000, nil);
    STAssertEquals(trigint_degrees_to_angle_i(90),  (trigint_angle_t)0x1000, nil);
    STAssertEquals(trigint_degrees_to_angle_i(180), (trigint_angle_t)0x2000, nil);
    STAssertEquals(trigint_degrees_to_angle_i(270), (trigint_angle_t)0x3000, nil);
}

- (void)testDegreesToAngleIntDoesNotWrap
{
    STAssertEquals(trigint_degrees_to_angle_i(360), (trigint_angle_t)0x4000, nil);
}

- (void)testDegreesToAngleDouble
{
    STAssertEquals(trigint_degrees_to_angle_d(0.0),   (trigint_angle_t)0x0000, nil);
    STAssertEquals(trigint_degrees_to_angle_d(90.0),  (trigint_angle_t)0x1000, nil);
    STAssertEquals(trigint_degrees_to_angle_d(180.0), (trigint_angle_t)0x2000, nil);
    STAssertEquals(trigint_degrees_to_angle_d(270.0), (trigint_angle_t)0x3000, nil);
}

- (void)testDegreesToAngleDoubleDoesNotWrap
{
    STAssertEquals(trigint_degrees_to_angle_d(360.0), (trigint_angle_t)0x4000, nil);
}

#pragma mark -

- (void)testAngleToDegreesInt
{
    STAssertEquals(trigint_angle_to_degrees_i(0x0000),   0, nil);
    STAssertEquals(trigint_angle_to_degrees_i(0x1000),  90, nil);
    STAssertEquals(trigint_angle_to_degrees_i(0x2000), 180, nil);
    STAssertEquals(trigint_angle_to_degrees_i(0x3000), 270, nil);
}

- (void)testAngleToDegreesDouble
{
    static const double ACCURACY_DELTA = 0.0000001;
    
    STAssertEqualsWithAccuracy(trigint_angle_to_degrees_d(0x0000),   0.0, ACCURACY_DELTA, nil);
    STAssertEqualsWithAccuracy(trigint_angle_to_degrees_d(0x1000),  90.0, ACCURACY_DELTA, nil);
    STAssertEqualsWithAccuracy(trigint_angle_to_degrees_d(0x2000), 180.0, ACCURACY_DELTA, nil);
    STAssertEqualsWithAccuracy(trigint_angle_to_degrees_d(0x3000), 270.0, ACCURACY_DELTA, nil);
    
    STAssertEqualsWithAccuracy(trigint_angle_to_degrees_d(0x0001), 0.0219727, ACCURACY_DELTA, nil);
    STAssertEqualsWithAccuracy(trigint_angle_to_degrees_d(0x0002), 0.0439453, ACCURACY_DELTA, nil);
    STAssertEqualsWithAccuracy(trigint_angle_to_degrees_d(0x0003), 0.0659180, ACCURACY_DELTA, nil);
}

#pragma mark -

- (void)testRadiansToAngleDouble
{
    STAssertEquals(trigint_radians_to_angle_d(    0.0),  (trigint_angle_t)0x0000, nil);
    STAssertEquals(trigint_radians_to_angle_d( M_PI_2),  (trigint_angle_t)0x1000, nil);
    STAssertEquals(trigint_radians_to_angle_d( M_PI),    (trigint_angle_t)0x2000, nil);
    STAssertEquals(trigint_radians_to_angle_d(3*M_PI_2), (trigint_angle_t)0x3000, nil);
}

- (void)testRadiansToAngleDoubleDoesNotWrap
{
    STAssertEquals(trigint_radians_to_angle_d(2*M_PI), (trigint_angle_t)0x4000, nil);
}

- (void)testAngleToRadiansDouble
{
    static const double ACCURACY_DELTA = 0.0000001;
    
    STAssertEqualsWithAccuracy(trigint_angle_to_radians_d(0x0000),     0.0,  ACCURACY_DELTA, nil);
    STAssertEqualsWithAccuracy(trigint_angle_to_radians_d(0x1000),   M_PI_2, ACCURACY_DELTA, nil);
    STAssertEqualsWithAccuracy(trigint_angle_to_radians_d(0x2000),   M_PI,   ACCURACY_DELTA, nil);
    STAssertEqualsWithAccuracy(trigint_angle_to_radians_d(0x3000), 3*M_PI_2, ACCURACY_DELTA, nil);
    STAssertEqualsWithAccuracy(trigint_angle_to_radians_d(0x4000), 2*M_PI,   ACCURACY_DELTA, nil);
    
    STAssertEqualsWithAccuracy(trigint_angle_to_radians_d(0x0001), 0.0003835, ACCURACY_DELTA, nil);
    STAssertEqualsWithAccuracy(trigint_angle_to_radians_d(0x0002), 0.0007670, ACCURACY_DELTA, nil);
    STAssertEqualsWithAccuracy(trigint_angle_to_radians_d(0x0003), 0.0011505, ACCURACY_DELTA, nil);
}

@end
