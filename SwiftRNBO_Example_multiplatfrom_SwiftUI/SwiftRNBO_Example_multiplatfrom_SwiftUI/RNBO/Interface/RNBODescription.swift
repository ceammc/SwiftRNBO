//
//  RNBODescription.swift
//  SwiftRNBO_Example_multiplatfrom_SwiftUI
//
//  Created by Eldar Sadykov on 18.11.2023.
//

import Foundation

// Define the main struct and its related sub-structs
struct RNBODescription: Codable {
    let parameters: [ParameterInfo]
    let numParameters, numSignalInParameters, numSignalOutParameters: Int
    let numInputChannels, numOutputChannels, numMidiInputPorts, numMidiOutputPorts: Int
    let externalDataRefs: [ExternalDataRef]
    let patcherSerial: Int
    let inports, outports: [Port]
    let inlets, outlets: [InletOutlet]
    let presetid: String
    let meta: Meta
}

// Define sub-structs used in RNBODescription
struct ParameterInfo: Codable {
    let type: String
    let index: Int
    let name, paramId: String
    let minimum, maximum, exponent: Double
    let steps: Int
    let initialValue: Double
    let isEnum: Bool
    let enumValues: [EnumValue]
    let displayName, unit: String
    let order: Int
    let debug, visible: Bool
    let signalIndex: Int?
    let ioType: String
}

extension ParameterInfo: Identifiable {
    var id: String { paramId }
}

struct ExternalDataRef: Codable {
    let id, file, type, tag: String
}

struct Port: Codable {
    let tag, meta: String
}

struct InletOutlet: Codable {
    let type: String
    let index: Int?
    let tag, meta: String?

    private enum CodingKeys: String, CodingKey {
        case type, index, tag, meta
    }
}

struct Meta: Codable {
    let architecture, filename, rnboobjname, maxversion: String
    let rnboversion, name: String
}

// Helper structs for handling JSON values and nulls
struct JSONNull: Codable, Hashable {}

struct EnumValue: Codable {
    let string: String

    init(from decoder: Decoder) throws {
        let container = try decoder.singleValueContainer()
        if let intVal = try? container.decode(Int.self) {
            string = String(intVal)
        } else if let doubleVal = try? container.decode(Double.self) {
            string = String(doubleVal)
        } else if let stringVal = try? container.decode(String.self) {
            string = stringVal
        } else if container.decodeNil() {
            string = "null"
        } else {
            throw DecodingError.typeMismatch(EnumValue.self, DecodingError.Context(codingPath: decoder.codingPath, debugDescription: "Failed to decode JSONAny"))
        }
    }

    func encode(to encoder: Encoder) throws {
        var container = encoder.singleValueContainer()
        try container.encode(string)
    }
}
