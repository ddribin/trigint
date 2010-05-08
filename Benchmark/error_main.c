/*
 *  error_main.c
 *  sin16
 *
 *  Created by Dave Dribin on 5/3/10.
 *  Copyright 2010 Bit Maki, Inc. All rights reserved.
 *
 */

#include "trigint.h"
#include "benchmark.h"
#include <math.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_LOOP_ITERATIONS 0x4001

static int16_t sin16_results[NUM_LOOP_ITERATIONS];
static int16_t sinf_results[NUM_LOOP_ITERATIONS];
static int16_t sin_results[NUM_LOOP_ITERATIONS];

#ifndef MAX
# define MAX(a, b) ((a) < (b) ? (b) : (a))
#endif

#define CHECK_ITERATIONS NUM_LOOP_ITERATIONS
void bench_check_error_of(int16_t approx_table[], int16_t actual_table[])
{
    int16_t max_abs_error = 0;
    double avg_abs_error = 0;
    double max_rel_error = 0;
    double avg_rel_error = 0;
    int rel_error_iterations = 0;
    for (int i = 0; i < CHECK_ITERATIONS; i++) {
        int16_t approx = approx_table[i];
        int16_t actual = actual_table[i];

        // Calculate absolute and relative errors:
        // http://en.wikipedia.org/wiki/Approximation_error
        int16_t abs_error = abs(approx - actual);
        double rel_error = 1.0 - ((double)approx)/((double)actual);
        
        // printf("%5d, %5d, %5d, %3d %.5g\n", i, approx, actual, abs_error, rel_error);
        // printf("%d, %d, %d\n", i, approx, abs_error);
        max_abs_error = MAX(max_abs_error, abs_error);
        max_rel_error = fmax(max_rel_error, rel_error);
        avg_abs_error += abs_error;
        if (!isnan(rel_error)) {
            avg_rel_error += rel_error;
            rel_error_iterations++;
        }
    }
    avg_abs_error /= CHECK_ITERATIONS;
    avg_rel_error /= rel_error_iterations;
    printf("  max_abs_error: %d\n", max_abs_error);
    printf("  avg_abs_error: %.5g\n", avg_abs_error);
    printf("  max_rel_error: %.5g\n", max_rel_error);
    printf("  avg_rel_error: %.5g\n", avg_rel_error);
    
    double std_dev = 0;
    for (int i = 0; i < CHECK_ITERATIONS; i++) {
        int16_t abs_error = abs(approx_table[i] - actual_table[i]);
        double diff_avg = ((double)abs_error) - avg_abs_error;
        double term = pow(diff_avg, 2);
        std_dev += term;
    }
    std_dev /= CHECK_ITERATIONS;
    std_dev = sqrt(std_dev);
    printf("  std_dev: %.3f\n", std_dev);
}

void bench_check_error()
{
    for (trigint_angle_t angle = 0; angle < NUM_LOOP_ITERATIONS; angle++) {
        sin16_results[angle] = trigint_sin16(angle);
        double radians = trigint_angle_to_radians_d(angle);
        sin_results[angle] = round(32767.0 * sin(radians));
        sinf_results[angle] = roundf(32767.0 * sinf(radians));
    }
    
#if 0
    printf("sinf vs. sin:\n");
    bench_check_error_of(sinf_results, sin_results);
#endif
    printf("sin16 vs. sin:\n");
    bench_check_error_of(sin16_results, sin_results);
#if 0
    printf("sin16 vs. sinf:\n");
    bench_check_error_of(sin16_results, sinf_results);
#endif
}

int main(int argc, char * const argv[])
{
#if !TRIGINT_SIN16_STATIC_TABLE
    trigint_sin16_init();
#endif
    bench_check_error();
    
    return 0;
}

