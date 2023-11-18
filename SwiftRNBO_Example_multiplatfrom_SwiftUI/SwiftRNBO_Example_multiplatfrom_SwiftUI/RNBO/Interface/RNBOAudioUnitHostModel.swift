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
    let description: RNBODescription?

    init() {
        do {
            let url = Bundle.main.url(forResource: "description", withExtension: "json")!
            let data = try Data(contentsOf: url)
            description = try JSONDecoder().decode(RNBODescription.self, from: data)
        } catch {
            print("Error decoding JSON from URL: \(error)")
            description = nil
        }

        audioUnit = audioEngine.getAudioUnit()
        parameters = audioUnit.getParametersArray()
    }

    func play() {
        audioEngine.play()
    }

    func refreshParameterValue(at parameterIndex: Int) {
        parameters[parameterIndex].value = Double(audioUnit.getParameterValue(parameterIndex))
    }

    func setParameterValue(to value: Double, at parameterIndex: Int) {
        audioUnit.setParameterValue(parameterIndex, value: Float(value))
    }

    func setParameterValueHot(to value: Double, at parameterIndex: Int) {
        setParameterValue(to: value, at: parameterIndex)
        refreshParameterValue(at: parameterIndex)
    }

    func setParameterValueNormalized(to valueNormalized: Double, at parameterIndex: Int) {
        audioUnit.setParameterValueNormalized(parameterIndex, valueNormalized: Float(valueNormalized))
    }

    func setParameterValueNormalizedHot(to valueNormalized: Double, at parameterIndex: Int) {
        setParameterValueNormalized(to: valueNormalized, at: parameterIndex)
        refreshParameterValue(at: parameterIndex)
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
