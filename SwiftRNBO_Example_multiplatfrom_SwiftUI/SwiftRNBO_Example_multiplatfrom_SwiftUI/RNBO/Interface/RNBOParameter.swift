//
//  Parameter.swift
//  RNBO_AVAudioEngine
//
//  Created by Eldar Sadykov on 13.02.2023.
//

import Foundation

struct RNBOParameter: Equatable {
    let index: Int
    let initialValue: Double
    var value: Double
    let minValue: Double
    let maxValue: Double
    let exponent: Double
    let unit: String
    let name: String
    let displayName: String
    let steps: Int

    var valueNormalized: Double {
        get {
            value.toNormalised(minValue: minValue, maxValue: maxValue, factor: exponent)
        }
        set {
            value = newValue.fromNormalised(minValue: minValue, maxValue: maxValue, factor: exponent)
        }
    }

    init(index: Int, initialValue: Double, minValue: Double, maxValue: Double, exponent: Double, unit: String, name: String, displayName: String, steps: Int) {
        self.index = index
        self.minValue = minValue
        self.maxValue = maxValue
        self.exponent = exponent
        self.initialValue = initialValue.clip(from: minValue, to: maxValue)
        value = self.initialValue
        self.unit = unit
        self.name = name
        self.displayName = displayName
        self.steps = steps
    }
}

extension RNBODescription {
    func getParametersArray() -> [RNBOParameter] {
        var parameters: [RNBOParameter] = []
        for i in 0 ..< numParameters {
            let parameter = self.parameters[i]
            parameters.append(
                RNBOParameter(
                    index: i,
                    initialValue: parameter.initialValue,
                    minValue: parameter.minimum,
                    maxValue: parameter.maximum,
                    exponent: parameter.exponent,
                    unit: parameter.unit,
                    name: parameter.name,
                    displayName: parameter.displayName,
                    steps: parameter.steps
                )
            )
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
