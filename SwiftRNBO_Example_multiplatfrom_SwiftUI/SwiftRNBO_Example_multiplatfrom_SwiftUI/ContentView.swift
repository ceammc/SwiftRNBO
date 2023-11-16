//
//  ContentView.swift
//  SwiftRNBO_Example_multiplatfrom_SwiftUI
//
//  Created by Эльдар Садыков on 19.02.2023.
//

import SwiftUI

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
            HStack {
                Button(action: {
                    rnbo.sendMIDINote(60, velocity: 127)
                }, label: {
                    Text("60")
                })
                Button(action: {
                    rnbo.sendMIDINote(70, velocity: 127)
                }, label: {
                    Text("70")
                })
                Button(action: {
                    rnbo.sendMIDINote(40, velocity: 127)
                }, label: {
                    Text("40")
                })
                Button(action: {
                    rnbo.sendMIDINote(50, velocity: 127)
                }, label: {
                    Text("50")
                })
            }
        }
        .padding()
    }
}
