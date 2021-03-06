#import "Sin16AppDelegate.h"
#import "DDCoreAudio.h"

static const double SAMPLE_RATE = 44100.0;

@implementation Sin16AppDelegate

@synthesize window = _window;
@synthesize playStopButton= _playStopButton;

static OSStatus MyRenderer(void *							inRefCon,
                           AudioUnitRenderActionFlags *	ioActionFlags,
                           const AudioTimeStamp *			inTimeStamp,
                           UInt32							inBusNumber,
                           UInt32							inNumberFrames,
                           AudioBufferList *				ioData)
{
    Sin16AppDelegate * self = (Sin16AppDelegate *)inRefCon;
    self->_renderCount++;
    
#if 0
    bzero(ioData->mBuffers[0].mData,
          ioData->mBuffers[0].mDataByteSize);
#else
    int16_t * frame = ioData->mBuffers[0].mData;
    for (NSUInteger i = 0; i < inNumberFrames; i++) {
        int16_t sineValue = trigint_sin16(self->_phase);
        
        frame[0] = sineValue;
        frame[1] = sineValue;
        
        self->_phase += self->_phaseIncrement;
        self->_frameCount++;
        frame += 2;
    }
    self->_phase = (self->_phase & 0x3fff);
#endif
    return noErr;
}

- (void)applicationWillFinishLaunching:(NSNotification *)notification
{
    [self setFrequencyToA440:nil];
    NSLog(@"phaseIncrement: %u", _phaseIncrement);
}

- (void)applicationDidFinishLaunching:(NSNotification *)notification
{
#if !TRIGINT_SIN16_STATIC_TABLE
    trigint_sin16_init();
#endif
#if !TRIGINT_SIN8_STATIC_TABLE
    trigint_sin8_init();
#endif
    
    _renderCount = 0;
    _frameCount = 0;
    NSTimer * timer = [NSTimer timerWithTimeInterval:1.0 target:self selector:@selector(timerFired:) userInfo:nil repeats:YES];
    [[NSRunLoop currentRunLoop] addTimer:timer forMode:NSRunLoopCommonModes];

    _graph = [[DDAudioUnitGraph alloc] init];
    
    _outputNode = [_graph addNodeWithType:kAudioUnitType_Output
                                  subType:kAudioUnitSubType_DefaultOutput];
    [_outputNode retain];
    
    
    _converterNode = [_graph addNodeWithType:kAudioUnitType_FormatConverter
                                     subType:kAudioUnitSubType_AUConverter];
    [_converterNode retain];

    [_graph connectNode:_converterNode output:0
                 toNode:_outputNode input:0];
    
    [_graph open];
    
    // 16-bit signed integer, stereo
    AudioStreamBasicDescription streamFormat = {0};
    UInt32 formatFlags = (0
                          | kAudioFormatFlagIsPacked 
                          | kAudioFormatFlagIsSignedInteger 
                          | kAudioFormatFlagsNativeEndian
                          );
    
    streamFormat.mFormatID = kAudioFormatLinearPCM;
    streamFormat.mSampleRate = SAMPLE_RATE;
    streamFormat.mChannelsPerFrame = 2;
    streamFormat.mFormatFlags = formatFlags;
    streamFormat.mBitsPerChannel = 16;
    streamFormat.mFramesPerPacket = 1;
    streamFormat.mBytesPerFrame = streamFormat.mBitsPerChannel * streamFormat.mChannelsPerFrame / 8;
    streamFormat.mBytesPerPacket = streamFormat.mBytesPerFrame * streamFormat.mFramesPerPacket;
    DDAudioUnit * converterUnit = [_converterNode audioUnit];
    [converterUnit setStreamFormatWithDescription:&streamFormat];
    
    [_converterNode setInputCallback:MyRenderer context:self forInput:0];
    
    NSLog(@"graph: %@", _graph);
    
    [_graph update];
    [_graph initialize];
}

- (void)timerFired:(NSTimer *)timer
{
    NSLog(@"calls per second: %u, frames: %llu", _renderCount, _frameCount);
    _renderCount = 0;
}

- (void)setFrequency:(double)frequency
{
    _frequency = frequency;
	_phaseIncrement = round(frequency * TRIGINT_ANGLES_PER_CYCLE / SAMPLE_RATE);
}

- (double)frequency
{
    return _frequency;
}

/*
 * http://en.wikipedia.org/wiki/Piano_key_frequencies
 */

- (IBAction)setFrequencyToA440:(id)sender;
{
    self.frequency = 440.0;
}

- (IBAction)setFrequencyToMiddleC:(id)sender;
{
    self.frequency = 261.626;
}

- (IBAction)playStop:(id)sender;
{
    if ([_graph isRunning]) {
        [_graph stop];
        [_playStopButton setTitle:@"Play"];
    } else {
        [_graph start];
        [_playStopButton setTitle:@"Stop"];
    }
}

@end
