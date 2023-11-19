//
//  RNBOEventHandlerProtocol.h
//
//
//  Created by Alex on 21.02.2023.
//

#pragma once

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

//struct OpaqueList;

typedef enum RNBOMessageEventType {
    RNBOMessageEventType_Invalid = -1,
    RNBOMessageEventType_Number  = 0,
    RNBOMessageEventType_List,
    RNBOMessageEventType_Bang,
    RNBOMessageEventType_Max_Type
} RNBOMessageEventType;

typedef enum RNBOPresetEventType {
    RNBOPresetEventType_Invalid = -1,
    RNBOPresetEventType_Set     = 0,
    RNBOPresetEventType_Touched,
    RNBOPresetEventType_Get,
    RNBOPresetEventType_SettingBegin,
    RNBOPresetEventType_SettingEnd,
    RNBOPresetEventType_Max_Type
} RNBOPresetEventType;


typedef struct RNBOParameterEvent {
    bool isValid;
    size_t index;
    double timeMilliseconds;
    double value;
    const void *source;
    // patchereventtarget
} RNBOParameterEvent;

typedef struct RNBOMidiEvent {
    double timeMilliseconds;
    int portIndex;
    size_t length;
    uint8_t midiData[3];
    // patchereventtarget
} RNBOMidiEvent;

typedef struct RNBOMessageEvent {
    uint32_t tag;
    uint32_t objectId;
    double eventTime;
    RNBOMessageEventType type;

    double numValue;
} RNBOMessageEvent;

typedef struct RNBOPresetEvent {
    double eventTime;
} RNBOPresetEvent;

typedef struct RNBOTempoEvent {
} RNBOTempoEvent;

typedef struct RNBOTransportEvent {
} RNBOTransportEvent;

typedef struct RNBOBeatTimeEvent {
} RNBOBeatTimeEvent;

typedef struct RNBOTimeSignatureEvent {
} RNBOTimeSignatureEvent;

typedef struct RNBOStartupEvent {
} RNBOStartupEvent;

///> @new
typedef struct RNBOMessageEventBase {
    uint32_t tag;
    uint32_t objectId;
    double eventTime;
} RNBOMessageEventBase;

@protocol RNBOEventHandlerProtocol



- (void)handleParameterEvent:(RNBOParameterEvent)event;
- (void)handleMidiEvent:(RNBOMidiEvent)event;
- (void)handleMessageEvent:(RNBOMessageEvent)event;
- (void)handlePresetEvent:(RNBOPresetEvent)event;
- (void)handleTempoEvent:(RNBOTempoEvent)event;
- (void)handleTransportEvent:(RNBOTransportEvent)event;
- (void)handleBeatTimeEvent:(RNBOBeatTimeEvent)event;
- (void)handleTimeSignatureEvent:(RNBOTimeSignatureEvent)event;
- (void)handleStartupEvent:(RNBOStartupEvent)event;

@optional
- (void)handleBangMessageEvent:(RNBOMessageEventBase)event;
- (void)handleFloatMessageEvent:(RNBOMessageEventBase)event value:(float)value;
- (void)handleListMessageEvent:(RNBOMessageEventBase)event value:(NSArray<NSNumber *> *)value;
@end

NS_ASSUME_NONNULL_END
