//
//  RNBOController.swift
//  SwiftUI_RNBO_FromScratch_Test
//
//  Created by Eldar Sadykov on 13.02.2023.
//

import Foundation

typealias RNBOContext = RNBOAudioUnitHostModel

class RNBOAudioUnitHostModel: ObservableObject {
    private let audioEngine = RNBOAudioEngine()
    private let audioUnit: RNBOAudioUnit
    private let eventHandler = RNBOEventHandler()
    @Published var parameters: [RNBOParameter]
    //    @Published var description: RNBODescription

    init() {
        audioUnit = audioEngine.getAudioUnit()
        parameters = audioUnit.getParametersArray()
    }

    func play() {
        audioEngine.play()
    }

    func setParameterValue(to value: Double, at parameterIndex: Int) {
        audioUnit.setParameterValue(parameterIndex, value: Float(value))
//        parameters[parameterIndex].value = Double(audioUnit.getParameterValue(parameterIndex))
    }

    func setParameterValueNormalized(to valueNormalized: Double, at parameterIndex: Int) {
        audioUnit.setParameterValueNormalized(parameterIndex, valueNormalized: Float(valueNormalized))
//        parameters[parameterIndex].value = Double(audioUnit.getParameterValue(parameterIndex))
    }

    func sendMessage(_ message: [Double]) {
        audioUnit.sendMessage("foo", list: message)
    }

    func sendNoteOn(_ pitch: UInt8, velocity: UInt8 = 127, channel: UInt8 = 0) {
        audioUnit.sendNoteOnMessage(withPitch: pitch, velocity: velocity, channel: channel)
    }
    
    func sendNoteOff(_ pitch: UInt8, releaseVelocity: UInt8 = 0, channel: UInt8 = 0) {
        audioUnit.sendNoteOffMessage(withPitch: pitch, releaseVelocity: releaseVelocity, channel: channel)
    }

    func connectEventHandler() {
        audioUnit.setEventHandler(eventHandler)
        eventHandler.rnbo = self
    }
}

// TODO: Description import from json
// struct RNBODescription {
//
// }

extension RNBOAudioUnitHostModel: RNBOEventHandlerProtocol {
    func handle(_ event: RNBOParameterEvent) {
        DispatchQueue.main.async {
            self.parameters[event.index].value = event.value
        }

        let p = parameters[event.index]
        print("\(p.displayName): \(p.value)")
    }

    func handle(_ event: RNBOMidiEvent) {
        print("Received MIDI: \(event.midiData)")
    }

    func handle(_ event: RNBOMessageEvent) {
    }

    func handle(_ event: RNBOPresetEvent) {
    }

    func handle(_ event: RNBOTempoEvent) {
    }

    func handle(_ event: RNBOTransportEvent) {
    }

    func handle(_ event: RNBOBeatTimeEvent) {
    }

    func handle(_ event: RNBOTimeSignatureEvent) {
    }

    func handle(_ event: RNBOStartupEvent) {
    }
}
