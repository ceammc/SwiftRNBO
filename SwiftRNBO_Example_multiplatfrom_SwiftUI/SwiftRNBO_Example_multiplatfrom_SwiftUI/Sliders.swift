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
            ScrollView {
                VStack {
                    ForEach($rnbo.parameters) { $parameter in
                        SliderView(parameter: $parameter)
                    }
                }
                .padding()
                .background()
                .padding(.bottom)
            }
            .frame(minHeight: 100)
            .padding(.bottom)
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
