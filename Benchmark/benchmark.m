//
//  benchmark.m
//  sin16
//
//  Created by Dave Dribin on 4/27/10.
//  Copyright 2010 Bit Maki, Inc. All rights reserved.
//

#import "benchmark.h"
#include "trigint.h"
#include <math.h>

static uint64_t gSum;

#define NUM_LOOP_ITERATIONS 0x4000

static int16_t sin_results[NUM_LOOP_ITERATIONS];

void ddprintf(NSString * format, ...)
{
    va_list arguments;
    va_start(arguments, format);
    NSString * string = [[NSString alloc] initWithFormat: format
                                               arguments: arguments];
    va_end(arguments);
    
    printf("%s", [string UTF8String]);
    [string release];
}

static NSString * formatFloat(float f)
{
    static NSNumberFormatter * formatter = nil;
    if (formatter == nil) {
        formatter = [[NSNumberFormatter alloc] init];
        [formatter setNumberStyle:NSNumberFormatterDecimalStyle];
    }
    NSNumber * n = [NSNumber numberWithFloat:f];
    return [formatter stringFromNumber:n];
}

#pragma mark -

typedef void (bench_loop_t)();


void bench_loop(bench_loop_t bench_loop, const char * name, uint32_t iters)
{
	gSum = 0;
	NSTimeInterval start = [NSDate timeIntervalSinceReferenceDate];
	for (uint32_t i = 0; i < iters; i++) {
		bench_loop();
	}
	NSTimeInterval end = [NSDate timeIntervalSinceReferenceDate];
	NSTimeInterval duration = end - start;
    float itersPerSec = ((float)gSum)/duration;
	// NSLog(@"%s: duration: %.3g, iters: %llu, per sec: %@", name, duration, gSum, formatFloat(itersPerSec));
    ddprintf(@"%s, %.4g, %llu, %.3f\n", name, duration, gSum, itersPerSec);
}

#pragma mark -

void trigint_sin16_bench_loop()
{
	for (int i = 0; i < NUM_LOOP_ITERATIONS; i++) {
		sin_results[i] = trigint_sin16(i);
		gSum++;
	}
}

void lib_sinf_bench_loop()
{
	float step = (2*M_PI) / ((float)NUM_LOOP_ITERATIONS);
    int i;
    float radians;
	for (i = 0, radians = 0; i < NUM_LOOP_ITERATIONS; i++, radians += step) {
		sin_results[i] = roundf(32767.0f * sinf(radians));
		gSum++;
	}
}
void lib_sin_bench_loop()
{
	double step = (2*M_PI) / ((double)NUM_LOOP_ITERATIONS);
    int i;
    double radians;
	for (i = 0, radians = 0; i < NUM_LOOP_ITERATIONS; i++, radians += step) {
		sin_results[i] = round(32767.0 * sin(radians));
		gSum++;
	}
}


#pragma mark -

void bench_trigint_sin16(uint32_t iters)
{
    bench_loop(trigint_sin16_bench_loop, "trigint_sin16", iters);
}

void bench_lib_sinf(uint32_t iters)
{
    bench_loop(lib_sinf_bench_loop, "sinf", iters);
}

void bench_lib_sin(uint32_t iters)
{
    bench_loop(lib_sin_bench_loop, "sin", iters);
}
