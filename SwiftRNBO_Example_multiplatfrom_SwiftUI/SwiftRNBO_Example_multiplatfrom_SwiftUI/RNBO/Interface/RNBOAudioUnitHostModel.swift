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
    @Published var showDescription: Bool = false
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
        
        let decoder = JSONDecoder()
        if let codedData = try? Data(contentsOf: RNBOAudioUnitHostModel.dataModelURL()),
           let decoded = try? decoder.decode([RNBOParameter].self, from: codedData) {
                parameters = decoded
        } else {
            parameters = description?.getParametersArray() ?? []
        }
    }

    func playAudioFile() {
        audioEngine.playAudioFile()
    }
    
    func pauseAudioFile() {
        audioEngine.pauseAudioFile()
    }

    func toggleMic(_ on: Bool) {
        if on {
            audioEngine.setMicrophoneAmplitude(1.0)
        } else {
            audioEngine.setMicrophoneAmplitude(0.0)
        }
    }
    
    func saveParameters() {
        let encoder = JSONEncoder()
        if let encoded = try? encoder.encode(parameters) {
            do {
                try encoded.write(to: type(of: self).dataModelURL())
            } catch {
                print("Couldn't write to save file: " + error.localizedDescription)
            }
        }
    }
    
    private static func dataModelURL() -> URL {
        let docURL = documentsDirectory()
        return docURL.appendingPathComponent("UserSettings")
    }
    
    private static func documentsDirectory() -> URL {
        let paths = FileManager.default.urls(for: .documentDirectory, in: .userDomainMask)
        let documentsDirectory = paths[0]
        return documentsDirectory
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

    func sendAftertouch(_ pitch: UInt8, pressure: UInt8, channel: UInt8 = 0) {
        audioUnit.sendAftertouchMessage(withPitch: pitch, pressure: pressure, channel: channel)
    }

    func sendContinuousController(_ number: UInt8, value: UInt8, channel: UInt8 = 0) {
        audioUnit.sendContinuousController(withNumber: number, value: value, channel: channel)
    }

    func sendPatchChange(_ program: UInt8, channel: UInt8 = 0) {
        audioUnit.sendPatchChangeMessage(withProgram: program, channel: channel)
    }

    func sendChannelPressure(_ pressure: UInt8, channel: UInt8 = 0) {
        audioUnit.sendChannelPressureMessage(withPressure: pressure, channel: channel)
    }

    func sendPitchBend(_ value: UInt16, channel: UInt8 = 0) {
        audioUnit.sendPitchBendMessage(withValue: value, channel: channel)
    }

    func connectEventHandler() {
        audioUnit.setEventHandler(eventHandler)
        eventHandler.rnbo = self
    }
}
