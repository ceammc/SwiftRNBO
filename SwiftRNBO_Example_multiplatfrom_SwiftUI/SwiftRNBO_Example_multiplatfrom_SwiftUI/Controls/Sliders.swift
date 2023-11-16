//
//  Sliders.swift
//  SwiftUI_RNBO_FromScratch_Test
//
//  Created by Эльдар Садыков on 13.02.2023.
//

#if !os(tvOS)
    import SwiftUI

    struct Sliders: View {
        @EnvironmentObject var rnbo: RNBOAudioUnitHostModel

        var body: some View {
            VStack {
                ForEach(rnbo.parameters.list.indices, id: \.self) { i in
                    HStack {
                        #if os(iOS)
                            SliderNameLabel(name: rnbo.parameters[i].displayName)
                        #endif
                        Slider(value: $rnbo.parameters.list[i].valueNormalized) {
                            SliderNameLabel(name: rnbo.parameters.list[i].displayName)
                        } minimumValueLabel: {
                            SliderValueLabel(value: rnbo.parameters.list[i].minValue)
                        } maximumValueLabel: {
                            SliderValueLabel(value: rnbo.parameters.list[i].maxValue)
                        }
                        .onChange(of: rnbo.parameters.list[i].valueNormalized) { rnbo.setParameterValueNormalized(to: $0, at: i) }
                        SliderValueLabel(value: rnbo.parameters.list[i].value)
                    }
                }
            }
        }
    }

    struct SliderValueLabel: View {
        let value: Double
        var body: some View {
            Text(String(format: "%.2f", value))
                .frame(minWidth: 50)
        }
    }

    struct SliderNameLabel: View {
        let name: String
        var body: some View {
            Text(name)
                .frame(minWidth: 100)
        }
    }
#endif
