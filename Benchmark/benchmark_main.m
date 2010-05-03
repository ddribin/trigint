/*
 *  benchmark.c
 *  sin16
 *
 *  Created by Dave Dribin on 4/27/10.
 *  Copyright 2010 Bit Maki, Inc. All rights reserved.
 *
 */


#import "benchmark.h"

int main(int argc, const char * argv[])
{
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    
    uint32_t iters = 50*1000;
    printf("Mac OS X\n");
    dd_sin16_bench(iters);
    lib_sinf_bench(iters);
    lib_sin_bench(iters);
    
    // bench_check_error();

    [pool drain];
    return 0;
}