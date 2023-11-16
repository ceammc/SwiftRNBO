//
//  RNBOController.swift
//  SwiftUI_RNBO_FromScratch_Test
//
//  Created by Eldar Sadykov on 13.02.2023.
//

import Foundation

typealias RNBOContext = RNBOAudioUnitHostModel

class RNBOAudioUnitHostModel: ObservableObject {
    private let audioEngine: RNBOAudioEngine
    private let audioUnit: RNBOAudioUnit
    private let eventHandler: RNBOEventHandler
    @Published var parameters: RNBOParameters
    //    @Published var description: RNBODescription

    init() {
        audioEngine = RNBOAudioEngine()
        audioUnit = audioEngine.getAudioUnit()
        parameters = RNBOParameters(list: audioUnit.getParametersArray())
        eventHandler = RNBOEventHandler()
        audioUnit.setEventHandler(eventHandler)
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
    
    func sendMIDINote(_ pitch: UInt8, velocity: UInt8) {
        audioUnit.sendMIDINote(pitch, velocity: velocity)
    }
    
    func connect() {
        parameters.rnbo = self
        eventHandler.rnbo = self
    }
}

// TODO: Description import from json
// struct RNBODescription {
//
// }
