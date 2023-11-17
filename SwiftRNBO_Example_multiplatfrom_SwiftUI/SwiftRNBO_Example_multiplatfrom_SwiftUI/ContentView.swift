//
//  ContentView.swift
//  SwiftRNBO_Example_multiplatfrom_SwiftUI
//
//  Created by Эльдар Садыков on 19.02.2023.
//

import Keyboard
import SwiftUI

struct ContentView: View {
    @EnvironmentObject var rnbo: RNBOAudioUnitHostModel

    var body: some View {
        VStack {
            #if !os(tvOS)
                Sliders()
            #endif
            HStack {
                Button("Randomize") {
                    randomize()
                }
                Button("Play dependency") {
                    let message: [Double] = [220, 330, 0.2, 0.3, 0.5]
                    rnbo.sendMessage(message)
                }
                Button("Play audio input") {
                    rnbo.play()
                }
            }
            Keyboard { pitch, point in
                rnbo.sendNoteOn(UInt8(pitch.midiNoteNumber), velocity: UInt8(point.y * 127))
            } noteOff: { pitch in
                rnbo.sendNoteOff(UInt8(pitch.midiNoteNumber))
            }
            .frame(minWidth: 600, minHeight: 200)
        }
        .padding()
        .background()
    }

    fileprivate func randomize() {
        for i in rnbo.parameters.indices {
            rnbo.setParameterValueNormalized(to: Double.random(in: 0 ... 1), at: i)
        }
    }
}
