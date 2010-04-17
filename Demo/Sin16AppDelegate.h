#import <Cocoa/Cocoa.h>
#import "dd_sin16.h"

@class DDAudioUnitGraph;
@class DDAudioUnitNode;
@class DDAudioUnit;

@interface Sin16AppDelegate : NSObject <NSApplicationDelegate>
{
    NSWindow * _window;
    DDAudioUnitGraph * _graph;
    DDAudioUnitNode * _outputNode;
    DDAudioUnitNode * _converterNode;
    DDAudioUnit * _converterUnit;
    
    uint64_t _renderCount;
    uint64_t _frameCount;
    
    double _frequency;
    dd_sin16_angle_t _phase;
    dd_sin16_angle_t _phaseIncrement;
}

@property (assign) IBOutlet NSWindow *window;
@property (nonatomic) double frequency;

- (IBAction)setFrequencyToA440:(id)sender;
- (IBAction)setFrequencyToMiddleC:(id)sender;
- (IBAction)playPause:(id)sender;

@end
