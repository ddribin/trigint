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

static int16_t sin16_results[NUM_LOOP_ITERATIONS];
static int16_t sinf_results[NUM_LOOP_ITERATIONS];
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
    ddprintf(@"%s, %.3g, %llu, %.3f\n", name, duration, gSum, itersPerSec);
}

#pragma mark -

void dd_sin16_bench_loop()
{
	for (int i = 0; i < NUM_LOOP_ITERATIONS; i++) {
		sin16_results[i] = dd_sin16(i);
		gSum++;
	}
}

void lib_sinf_bench_loop()
{
	float step = (2*M_PI) / ((double)NUM_LOOP_ITERATIONS);
    int i;
    float radians;
	for (i = 0, radians = 0; i < NUM_LOOP_ITERATIONS; i++, radians += step) {
		sin16_results[i] = 32767.0 * sinf(radians);
		gSum++;
	}
}
void lib_sin_bench_loop()
{
	double step = (2*M_PI) / ((double)NUM_LOOP_ITERATIONS);
    int i;
    double radians;
	for (i = 0, radians = 0; i < NUM_LOOP_ITERATIONS; i++, radians += step) {
		sin16_results[i] = 32767.0 * sin(radians);
		gSum++;
	}
}


#pragma mark -

void dd_sin16_bench(uint32_t iters)
{
    bench_loop(dd_sin16_bench_loop, "dd_sin16", iters);
}

void lib_sinf_bench(uint32_t iters)
{
    bench_loop(lib_sinf_bench_loop, "sinf", iters);
}

void lib_sin_bench(uint32_t iters)
{
    bench_loop(lib_sin_bench_loop, "sin", iters);
}

void bench_check_error_of(int16_t table1[], int16_t table2[])
{
    int16_t max_diff = 0;
    double avg_diff = 0;
    for (int i = 0; i < NUM_LOOP_ITERATIONS; i++) {
        int16_t diff = abs(table1[i] - table2[i]);
        // printf("%d, %d, %d, %d\n", i, table1[i], table2[i], diff);
        max_diff = MAX(max_diff, diff);
        avg_diff += diff;
    }
    avg_diff /= NUM_LOOP_ITERATIONS;
    printf("  max_diff: %d\n", max_diff);
    printf("  avg_diff: %.3f\n", avg_diff);

    double std_dev = 0;
    for (int i = 0; i < NUM_LOOP_ITERATIONS; i++) {
        int16_t diff = abs(table1[i] - table2[i]);
        double diff_avg = ((double)diff) - avg_diff;
        double term = pow(diff_avg, 2);
        std_dev += term;
    }
    std_dev /= NUM_LOOP_ITERATIONS;
    std_dev = sqrt(std_dev);
    printf("  std_dev: %.3f\n", std_dev);
}

void bench_check_error()
{
    for (trigint_angle_t angle = 0; angle < NUM_LOOP_ITERATIONS; angle++) {
        double radians = trigint_angle_to_radians_d(angle);
        sin16_results[angle] = dd_sin16(angle);
        sinf_results[angle] = roundf(32767.0 * sinf(radians));
        sin_results[angle] = round(32767.0 * sin(radians));
    }
    
    printf("sinf vs. sin:\n");
    bench_check_error_of(sinf_results, sin_results);
    printf("dd_sin16 vs. sin:\n");
    bench_check_error_of(sin16_results, sin_results);
    printf("dd_sin16 vs. sinf:\n");
    bench_check_error_of(sin16_results, sinf_results);
}
