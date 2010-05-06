/*
 *  error_main.c
 *  sin16
 *
 *  Created by Dave Dribin on 5/3/10.
 *  Copyright 2010 Bit Maki, Inc. All rights reserved.
 *
 */

#include "dd_sin16.h"
#include "benchmark.h"
#include <math.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_LOOP_ITERATIONS 0x4000

static int16_t sin16_results[NUM_LOOP_ITERATIONS];
static int16_t sinf_results[NUM_LOOP_ITERATIONS];
static int16_t sin_results[NUM_LOOP_ITERATIONS];

#ifndef MAX
# define MAX(a, b) ((a) < (b) ? (b) : (a))
#endif

#define CHECK_ITERATIONS NUM_LOOP_ITERATIONS
void bench_check_error_of(int16_t table1[], int16_t table2[])
{
    int16_t max_diff = 0;
    double avg_diff = 0;
    for (int i = 0; i < CHECK_ITERATIONS; i++) {
        int16_t diff = abs(table1[i] - table2[i]);
        // printf("%d, %d, %d, %d\n", i, table1[i], table2[i], diff);
        max_diff = MAX(max_diff, diff);
        avg_diff += diff;
    }
    avg_diff /= CHECK_ITERATIONS;
    printf("  max_diff: %d\n", max_diff);
    printf("  avg_diff: %.3f\n", avg_diff);
    
    double std_dev = 0;
    for (int i = 0; i < CHECK_ITERATIONS; i++) {
        int16_t diff = abs(table1[i] - table2[i]);
        double diff_avg = ((double)diff) - avg_diff;
        double term = pow(diff_avg, 2);
        std_dev += term;
    }
    std_dev /= CHECK_ITERATIONS;
    std_dev = sqrt(std_dev);
    printf("  std_dev: %.3f\n", std_dev);
}

void bench_check_error()
{
    for (dd_sin16_angle_t angle = 0; angle < NUM_LOOP_ITERATIONS; angle++) {
        double radians = dd_sin16_angle_to_radians_d(angle);
        sin16_results[angle] = dd_sin16(angle);
        sinf_results[angle] = roundf(32767.0 * sinf(radians));
        sin_results[angle] = round(32767.0 * sin(radians));
    }
    
#if 0
    printf("sinf vs. sin:\n");
    bench_check_error_of(sinf_results, sin_results);
#endif
    printf("dd_sin16 vs. sin:\n");
    bench_check_error_of(sin16_results, sin_results);
#if 0
    printf("dd_sin16 vs. sinf:\n");
    bench_check_error_of(sin16_results, sinf_results);
#endif
}

int main(int argc, char * const argv[])
{
#if 1
    bench_check_error();
#else
    for (dd_sin16_angle_t angle = 0; angle < DD_SIN16_ANGLES_PER_CYCLE; angle++) {
        int16_t sin16_value = dd_sin16(angle);
        
        double radians = dd_sin16_angle_to_radians_d(angle);
        int16_t sin_value = round(32767.0 * sin(radians));
        printf("%lf, %d, %d\n", radians, sin16_value, sin_value);
    }
#endif
    
    return 0;
}

