//
//  RNBOController.swift
//  SwiftUI_RNBO_FromScratch_Test
//
//  Created by Eldar Sadykov on 13.02.2023.
//

import Foundation

class RNBOAudioUnitHostModel: ObservableObject {
    private let audioEngine: RNBOAudioEngine
    private let audioUnit: RNBOAudioUnit
    @Published var parameters: [RNBOParameter]
    //    @Published var description: RNBODescription

    init() {
        audioEngine = RNBOAudioEngine()
        audioUnit = audioEngine.getAudioUnit()
        parameters = audioUnit.getParametersArray()
    }
    
    func play() {
        audioEngine.play()
    }

    func setParameterValue(to value: Double, at parameterIndex: Int) {
        audioUnit.setParameterValue(parameterIndex, valueNormalized: Float(value))
        parameters[parameterIndex].value = Double(audioUnit.getParameterValue(parameterIndex))
    }

    func setParameterValueNormalized(to valueNormalized: Double, at parameterIndex: Int) {
        audioUnit.setParameterValueNormalized(parameterIndex, valueNormalized: Float(valueNormalized))
        parameters[parameterIndex].value = Double(audioUnit.getParameterValue(parameterIndex))
    }
}

// TODO: Description import from json
// struct RNBODescription {
//
// }
