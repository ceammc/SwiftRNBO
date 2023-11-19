//
//  Parameter.swift
//  RNBO_AVAudioEngine
//
//  Created by Eldar Sadykov on 13.02.2023.
//

import Foundation

struct RNBOParameter {
    var value: Double
    let info: ParameterInfo

    var valueNormalized: Double {
        get {
            value.toNormalised(minValue: info.minimum, maxValue: info.maximum, factor: info.exponent)
        }
        set {
            value = newValue.fromNormalised(minValue: info.minimum, maxValue: info.maximum, factor: info.exponent)
        }
    }

    init(_ info: ParameterInfo) {
        value = info.initialValue.clip(from: info.minimum, to: info.maximum)
        self.info = info
    }
}

extension RNBOParameter: Equatable {
    static func == (lhs: RNBOParameter, rhs: RNBOParameter) -> Bool {
        (lhs.value == rhs.value) && (lhs.id == rhs.id)
    }
}

extension RNBOParameter: Identifiable {
    var id: String { info.paramId }
}

extension RNBODescription {
    func getParametersArray() -> [RNBOParameter] {
        var parameters: [RNBOParameter] = []
        for i in 0 ..< numParameters {
            let parameter = self.parameters[i]
            parameters.append(RNBOParameter(parameter))
        }
        return parameters
    }
}

extension Double {
    func clip(from minValue: Double, to maxValue: Double) -> Double {
        min(maxValue, max(self, minValue))
    }

    func fromNormalised(minValue: Double, maxValue: Double, factor: Double) -> Double {
        let exponentiatedValue = pow(self, factor)
        let scaledValue = minValue + (maxValue - minValue) * exponentiatedValue
        return scaledValue
    }

    func toNormalised(minValue: Double, maxValue: Double, factor: Double) -> Double {
        let normalizedValue = (self - minValue) / (maxValue - minValue)
        let inverseScaledValue = pow(normalizedValue, 1 / factor)
        return inverseScaledValue
    }
}
