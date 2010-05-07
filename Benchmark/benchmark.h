//
//  benchmark.h
//  sin16
//
//  Created by Dave Dribin on 4/27/10.
//  Copyright 2010 Bit Maki, Inc. All rights reserved.
//



#ifdef __OBJC__
#import <Foundation/Foundation.h>
void ddprintf(NSString * format, ...);
#endif

void bench_trigint_sin16(uint32_t iters);
void bench_lib_sin(uint32_t iters);
void bench_lib_sinf(uint32_t iters);
