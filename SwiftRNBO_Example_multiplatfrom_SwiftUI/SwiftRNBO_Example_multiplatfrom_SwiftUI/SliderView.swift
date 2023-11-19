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
//            let displayName = parameter.displayName != "" ? parameter.displayName : parameter.name.capitalizedSentence
            let displayName = parameter.info.paramId
            #if os(iOS)
                SliderNameLabel(name: displayName)
            #endif
            Slider(value: $parameter.valueNormalized) {
                SliderNameLabel(name: displayName)
            } minimumValueLabel: {
                SliderValueLabel(value: parameter.info.minimum)
            } maximumValueLabel: {
                SliderValueLabel(value: parameter.info.maximum)
            }
            .onChange(of: parameter.valueNormalized) { rnbo.setParameterValueNormalized(to: $0, at: parameter.info.index) }
            SliderValueLabel(value: parameter.value)
        }
    }
}
