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
                ForEach(rnbo.parameters.indices, id: \.self) { i in
                    HStack {
                        #if os(iOS)
                            SliderNameLabel(name: rnbo.parameters[i].displayName)
                        #endif
                        Slider(value: $rnbo.parameters[i].valueNormalized) {
                            SliderNameLabel(name: rnbo.parameters[i].displayName)
                        } minimumValueLabel: {
                            SliderValueLabel(value: rnbo.parameters[i].minValue)
                        } maximumValueLabel: {
                            SliderValueLabel(value: rnbo.parameters[i].maxValue)
                        }
                        .onChange(of: rnbo.parameters[i].valueNormalized) { rnbo.setParameterValueNormalized(to: $0, at: i) }
                        SliderValueLabel(value: rnbo.parameters[i].value)
                    }
                }
            }
            .padding()
            .background()
            .padding(.bottom)
//            .clipShape(RoundedRectangle(cornerSize: CGSize(width: 8, height: 8)))
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
