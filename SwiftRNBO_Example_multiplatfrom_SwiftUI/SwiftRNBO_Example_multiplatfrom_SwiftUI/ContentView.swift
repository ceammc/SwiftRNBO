//
//  ContentView.swift
//  SwiftRNBO_Example_multiplatfrom_SwiftUI
//
//  Created by Эльдар Садыков on 19.02.2023.
//

import SwiftUI
import Keyboard

struct ContentView: View {
    @EnvironmentObject var rnbo: RNBOAudioUnitHostModel

    var body: some View {
        VStack {
            #if !os(tvOS)
                Sliders()
            #endif
            Spacer()
            RandomizeButton()
            Spacer()
            MessageTestButtons()
            Spacer()
            Button("Play") {
                rnbo.play()
            }
            Spacer()
            Keyboard { pitch, point in
                rnbo.sendMIDINote(UInt8(pitch.midiNoteNumber), velocity: UInt8(point.y * 127))
            } noteOff: { pitch in
                rnbo.sendMIDINote(UInt8(pitch.midiNoteNumber), velocity: 0)
            }
            .frame(minWidth: 600, minHeight: 200)
        }
        .padding()
        .background()
    }
}
