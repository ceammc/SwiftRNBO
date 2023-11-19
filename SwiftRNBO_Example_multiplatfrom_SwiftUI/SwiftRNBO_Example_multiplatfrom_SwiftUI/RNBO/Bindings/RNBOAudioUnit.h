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

typedef NS_ENUM(uint8_t, MidiCommand) {
    MidiCommandNoteOff              = 0x80,
    MidiCommandNoteOn               = 0x90,
    MidiCommandAftertouch           = 0xA0,
    MidiCommandContinuousController = 0xB0,
    MidiCommandPatchChange          = 0xC0,
    MidiCommandChannelPressure      = 0xD0,
    MidiCommandPitchBend            = 0xE0
};

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

- (void)sendMidiMessageWithCommand:(MidiCommand)command byte1:(uint8_t)byte1 byte2:(uint8_t)byte2 channel:(uint8_t)channel;
- (void)sendTwoByteMidiMessageWithCommand:(MidiCommand)command byte1:(uint8_t)byte1 channel:(uint8_t)channel;

- (void)sendNoteOnMessageWithPitch:(uint8_t)pitch velocity:(uint8_t)velocity channel:(uint8_t)channel;
- (void)sendNoteOffMessageWithPitch:(uint8_t)pitch releaseVelocity:(uint8_t)releaseVelocity channel:(uint8_t)channel;
- (void)sendAftertouchMessageWithPitch:(uint8_t)pitch pressure:(uint8_t)pressure channel:(uint8_t)channel;
- (void)sendContinuousControllerWithNumber:(uint8_t)number value:(uint8_t)value channel:(uint8_t)channel;
- (void)sendPatchChangeMessageWithProgram:(uint8_t)program channel:(uint8_t)channel;
- (void)sendChannelPressureMessageWithPressure:(uint8_t)pressure channel:(uint8_t)channel;
- (void)sendPitchBendMessageWithValue:(uint16_t)value channel:(uint8_t)channel;

- (void)setEventHandler:(NSObject<RNBOEventHandlerProtocol> *)handler;
- (void)eventHandlerEventsAvailable;
@end
