//
//  MyV3AudioUnit5.h
//  auv3test5
//
//  Created by Ronald Nicholson on 7/31/17.
//  Copyright © 2017 HotPaw Productions.
//

#import <AVFoundation/AVFoundation.h>
#import <Foundation/Foundation.h>

#import "RNBOEventHandlerProtocol.h"

extern long int toneCount;
extern double sampleRateHz;
extern float testFrequency;

extern long int testMagnitude;

extern void processBuffer(float *p, int len);

@interface RNBOAudioUnit : AUAudioUnit {
//    AUAudioUnitBusArray *outputBusArray;
//    AUAudioUnitBusArray *inputBusArray;
    NSObject<RNBOEventHandlerProtocol> *_handler;
}

- (void)setParameterValue:(size_t)number value:(float)v;
- (void)setParameterValueNormalized:(size_t)number valueNormalized:(float)v;
- (size_t)getParameterCount;

- (float)getParameterValue:(size_t)number;

- (float)getParameterInitialValue:(size_t)number;
- (float)getParameterMin:(size_t)number;
- (float)getParameterMax:(size_t)number;
- (float)getParameterExponent:(size_t)number;
- (int)getParameterSteps:(size_t)number;
- (NSString *)getParameterUnit:(size_t)number;
- (NSString *)getParameterDisplayName:(size_t)number;

- (void)sendMessage:(NSString *)tag;
- (void)sendMessage:(NSString *)tag number:(float)number;
- (void)sendMessage:(NSString *)tag list:(NSArray *)list;
- (void)sendMIDINote:(uint8_t)pitch velocity:(uint8_t)velocity;

- (void)setEventHandler:(NSObject<RNBOEventHandlerProtocol> *)handler;
- (void)eventHandlerEventsAvailable;
@end
