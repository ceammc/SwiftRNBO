//
//  MIDIHelpers.swift
//  SwiftRNBO_Example_multiplatfrom_SwiftUI
//
//  Created by Eldar Sadykov on 19.11.2023.
//

import Foundation

enum MidiCommand: UInt8 {
    case noteOff = 0x80
    case noteOn = 0x90
    case polyphonicKeyPressure = 0xA0
    case controlChange = 0xB0
    case programChange = 0xC0
    case channelPressure = 0xD0
    case pitchBend = 0xE0

    init?(statusByte: UInt8) {
        switch statusByte & 0xF0 {
        case MidiCommand.noteOff.rawValue: self = .noteOff
        case MidiCommand.noteOn.rawValue: self = .noteOn
        case MidiCommand.polyphonicKeyPressure.rawValue: self = .polyphonicKeyPressure
        case MidiCommand.controlChange.rawValue: self = .controlChange
        case MidiCommand.programChange.rawValue: self = .programChange
        case MidiCommand.channelPressure.rawValue: self = .channelPressure
        case MidiCommand.pitchBend.rawValue: self = .pitchBend
        default: return nil
        }
    }
}
