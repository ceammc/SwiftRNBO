//
//  RNBOEventHandler.h
//
//
//  Created by Alex on 21.02.2023.
//

#pragma once

#import "RNBOEventHandlerProtocol.h"

#include "RNBO.h"

#import <Foundation/Foundation.h>

class RNBOEventHandler: public RNBO::EventHandler {
    NSObject<RNBOEventHandlerProtocol> *_obj;

public:
    RNBOEventHandler(NSObject<RNBOEventHandlerProtocol> *handler = nil);

    inline void setEventHandler(NSObject<RNBOEventHandlerProtocol> *obj) {
        _obj = obj;
    }

    virtual void eventsAvailable() override final;

    virtual void handleParameterEvent(const RNBO::ParameterEvent& event) override final;
    virtual void handleMidiEvent(const RNBO::MidiEvent& event) override final;
    virtual void handleMessageEvent(const RNBO::MessageEvent& event) override final;
    virtual void handlePresetEvent(const RNBO::PresetEvent& event) override final;
    virtual void handleTempoEvent(const RNBO::TempoEvent& event) override final;
    virtual void handleTransportEvent(const RNBO::TransportEvent& event) override final;
    virtual void handleBeatTimeEvent(const RNBO::BeatTimeEvent& event) override final;
    virtual void handleTimeSignatureEvent(const RNBO::TimeSignatureEvent& event) override final;
    virtual void handleStartupEvent(const RNBO::StartupEvent& event) override final;
};
