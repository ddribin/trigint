#import "Sin16AppDelegate.h"
#import "dd_sin16.h"

@implementation Sin16AppDelegate

@synthesize window;

- (void)applicationDidFinishLaunching:(NSNotification *)notification
{
#if !DD_SIN16_STATIC_TABLE
        dd_sin16_init();
#endif
    
#if 0
    dd_sin16_table();
#endif

#if 0
    extern void dd_sin16_dump_table();
    dd_sin16_dump_table();
    printf("\n");
#endif
    
#if 0
    for (dd_sin16_angle_t angle = 0x0000; angle <= 0x1000; angle += 0x0001) {
        double degrees = dd_sin16_angle_to_degrees_d(angle);
        int16_t value = dd_sin16(angle);
        printf("%.3f, %d\n", degrees, value);
    }
    printf("\n");
#endif

#if 0
    for (double degrees = 0.0; degrees <= 90.0; degrees += 0.1) {
        dd_sin16_angle_t angle = dd_sin16_degrees_to_angle_d(degrees);
        int16_t value = dd_sin16(angle);
        printf("%.3f, %d\n", degrees, value);
    }
#endif
}

@end
