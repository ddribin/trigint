#import "Sin16AppDelegate.h"
#import "dd_sin16.h"

@implementation Sin16AppDelegate

@synthesize window;

- (void)applicationDidFinishLaunching:(NSNotification *)notification
{
    dd_sin16_init();
}

@end
