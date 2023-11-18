//
//  ParameterView.swift
//  SwiftRNBO_Example_multiplatfrom_SwiftUI
//
//  Created by Eldar Sadykov on 18.11.2023.
//

import SwiftUI

struct SliderView: View {
    @EnvironmentObject var rnbo: RNBOAudioUnitHostModel
    @Binding var parameter: RNBOParameter
    var body: some View {
        HStack {
            #if os(iOS)
                SliderNameLabel(name: parameter.displayName)
            #endif
            Slider(value: $parameter.valueNormalized) {
                SliderNameLabel(name: parameter.displayName)
            } minimumValueLabel: {
                SliderValueLabel(value: parameter.minValue)
            } maximumValueLabel: {
                SliderValueLabel(value: parameter.maxValue)
            }
            .onChange(of: parameter.valueNormalized) { rnbo.setParameterValueNormalized(to: $0, at: parameter.index) }
            SliderValueLabel(value: parameter.value)
        }
    }
}
