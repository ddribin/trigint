//
//  BenchmarkAppDelegate.m
//  Benchmark
//
//  Created by Dave Dribin on 4/27/10.
//  Copyright Bit Maki, Inc. 2010. All rights reserved.
//

#import "BenchmarkAppDelegate.h"
#import "benchmark.h"

@implementation BenchmarkAppDelegate

@synthesize window;


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {    

	[NSThread detachNewThreadSelector:@selector(benchmark) toTarget:self withObject:nil];
	
    [window makeKeyAndVisible];
	
	return YES;
}

- (void)benchmark
{
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    
    // Give the system a chance to go idle
    [NSThread sleepForTimeInterval:1.0];
    
    ddprintf(@"Thumb mode: %s\n", GCC_THUMB_SUPPORT);
    UIDevice * device = [UIDevice currentDevice];
    ddprintf(@"Device localizedModel: %@, systemName: %@, systemVersion: %@\n",
             device.localizedModel, device.systemName, device.systemVersion);
	ddprintf(@"Function, Duration (secs), Iterations, Iterations/sec\n");
    uint32_t iters = 5*1000;
    bench_trigint_sin16(iters);
    bench_lib_sinf(iters);
    bench_lib_sin(iters);
    
    // bench_check_error();
    
    [pool drain];
}

- (void)dealloc {
    [window release];
    [super dealloc];
}


@end
