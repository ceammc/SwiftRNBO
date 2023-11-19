//
//  RNBOEventHandler.m
//
//
//  Created by Alex on 21.02.2023.
//

#import "RNBOEventHandler.hpp"
#include "RNBOEventHandlerProtocol.h"

RNBOParameterEvent convertEvent(const RNBO::ParameterEvent& event) {
    RNBOParameterEvent ret {};

    ret.index = event.getIndex();
    ret.timeMilliseconds = event.getTime();
    ret.value = event.getValue();
    ret.source = event.getSource();

    return ret;
}

RNBOMidiEvent convertEvent(const RNBO::MidiEvent& event) {
    RNBOMidiEvent ret {};

    ret.length = event.getLength();

    for (uint8_t i = 0; i < ret.length; i++) {
        ret.midiData[i] = event.getData()[i];
    }

    ret.portIndex = event.getPortIndex();
    ret.timeMilliseconds = event.getTime();

    return ret;
}

RNBOMessageEvent convertEvent(const RNBO::MessageEvent& event) {
    RNBOMessageEvent ret {};

    ret.tag = event.getTag();
    ret.eventTime = event.getTime();
    ret.objectId = event.getObjectId();

    RNBOMessageEventBase base {};

    if (event.getType() == RNBO::MessageEvent::Type::List) {
        base.tag = event.getTag();
        // ...

        NSMutableArray *a = [NSMutableArray new];

        for (int i = 0; i < event.getListValue()->length; i++) {
            auto e = event.getListValue()->operator[](i);
            [a addObject:[NSNumber numberWithFloat:e]];
        }
    }

    return ret;
}

RNBOPresetEvent convertEvent(const RNBO::PresetEvent& event) {
    RNBOPresetEvent ret {};

    return ret;
}

RNBOTempoEvent convertEvent(const RNBO::TempoEvent& event) {
    RNBOTempoEvent ret {};

    return ret;
}

RNBOTransportEvent convertEvent(const RNBO::TransportEvent& event) {
    RNBOTransportEvent ret {};

    return ret;
}

RNBOBeatTimeEvent convertEvent(const RNBO::BeatTimeEvent& event) {
    RNBOBeatTimeEvent ret {};

    return ret;
}

RNBOTimeSignatureEvent convertEvent(const RNBO::TimeSignatureEvent& event) {
    RNBOTimeSignatureEvent ret {};

    return ret;
}

RNBOStartupEvent convertEvent(const RNBO::StartupEvent& event) {
    RNBOStartupEvent ret {};

    return ret;
}

#pragma mark -

void RNBOEventHandler::eventsAvailable() {
    // N.B. must be called not in the audio thread!
    drainEvents();
}

#pragma mark -

RNBOEventHandler::RNBOEventHandler(NSObject<RNBOEventHandlerProtocol> *handler) {
    _obj = handler;
}

#pragma mark -

void RNBOEventHandler::handleParameterEvent(const RNBO::ParameterEvent& event) {
    [_obj handleParameterEvent:convertEvent(event)];
}

void RNBOEventHandler::handleMidiEvent(const RNBO::MidiEvent& event) {
    [_obj handleMidiEvent:convertEvent(event)];
}

void RNBOEventHandler::handleMessageEvent(const RNBO::MessageEvent& event) {
    [_obj handleMessageEvent:convertEvent(event)];
}

void RNBOEventHandler::handlePresetEvent(const RNBO::PresetEvent& event) {
    [_obj handlePresetEvent:convertEvent(event)];
}

void RNBOEventHandler::handleTempoEvent(const RNBO::TempoEvent& event) {
    [_obj handleTempoEvent:convertEvent(event)];
}

void RNBOEventHandler::handleTransportEvent(const RNBO::TransportEvent& event) {
    [_obj handleTransportEvent:convertEvent(event)];
}

void RNBOEventHandler::handleBeatTimeEvent(const RNBO::BeatTimeEvent& event) {
    [_obj handleBeatTimeEvent:convertEvent(event)];
}

void RNBOEventHandler::handleTimeSignatureEvent(const RNBO::TimeSignatureEvent& event) {
    [_obj handleTimeSignatureEvent:convertEvent(event)];
}

void RNBOEventHandler::handleStartupEvent(const RNBO::StartupEvent& event) {
    [_obj handleStartupEvent:convertEvent(event)];
}
