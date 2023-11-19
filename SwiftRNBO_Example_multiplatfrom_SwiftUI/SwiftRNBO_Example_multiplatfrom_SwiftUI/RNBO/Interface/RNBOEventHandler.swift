//
//  RNBOEventHandler.swift
//  SwiftRNBO_Example_multiplatfrom_SwiftUI
//
//  Created by Eldar Sadykov on 16.11.2023.
//

import Foundation

class RNBOEventHandler: NSObject, RNBOEventHandlerProtocol {
    var rnbo: RNBOContext?

    func handle(_ event: RNBOParameterEvent) {
        if let rnbo = rnbo {
            DispatchQueue.main.async {
                rnbo.parameters[event.index].value = event.value
            }

            let p = rnbo.parameters[event.index]
            print("\(p.info.displayName): \(p.value)")
        }
    }

    func handle(_ event: RNBOMidiEvent) {
        let data = [event.midiData.0, event.midiData.1, event.midiData.2].prefix(event.length)
        print("Received MIDI: \(data)")

        let statusByte = event.midiData.0
        let channel = statusByte & 0x0F
        guard let command = MidiCommand(statusByte: statusByte) else {
            print("Unknown MIDI Command")
            return
        }

        switch command {
        case .noteOff:
            let note = event.midiData.1
            let velocity = event.midiData.2
            print("Note Off: Note \(note), Velocity \(velocity), Channel \(channel + 1)")

        case .noteOn:
            let note = event.midiData.1
            let velocity = event.midiData.2
            print("Note On: Note \(note), Velocity \(velocity), Channel \(channel + 1)")

        case .polyphonicKeyPressure:
            let note = event.midiData.1
            let pressure = event.midiData.2
            print("Polyphonic Key Pressure: Note \(note), Pressure \(pressure), Channel \(channel + 1)")

        case .controlChange:
            let controller = event.midiData.1
            let value = event.midiData.2
            print("Control Change: Controller \(controller), Value \(value), Channel \(channel + 1)")

        case .programChange:
            let program = event.midiData.1
            print("Program Change: Program \(program), Channel \(channel + 1)")

        case .channelPressure:
            let pressure = event.midiData.1
            print("Channel Pressure: Pressure \(pressure), Channel \(channel + 1)")

        case .pitchBend:
            let lsb = event.midiData.1
            let msb = event.midiData.2
            let value = (Int(msb) << 7) + Int(lsb)
            print("Pitch Bend: Value \(value), Channel \(channel + 1)")
        }
    }

    func handle(_ event: RNBOMessageEvent) {
//        print("Message from outport: \(event.tag): \(event.numValue)")
        // TODO:
    }

    func handle(_ event: RNBOPresetEvent) {
        // TODO:
    }

    func handle(_ event: RNBOTempoEvent) {
        // TODO:
    }

    func handle(_ event: RNBOTransportEvent) {
        // TODO:
    }

    func handle(_ event: RNBOBeatTimeEvent) {
        // TODO:
    }

    func handle(_ event: RNBOTimeSignatureEvent) {
        // TODO:
    }

    func handle(_ event: RNBOStartupEvent) {
        // TODO:
    }
}
