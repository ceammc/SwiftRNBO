//
//  Buttons.swift
//  SwiftRNBO_Example_multiplatfrom_SwiftUI
//
//  Created by Eldar Sadykov on 17.11.2023.
//

import SwiftUI

struct Buttons: View {
    @EnvironmentObject var rnbo: RNBOAudioUnitHostModel
    @State private var enableMic: Bool = false
    var body: some View {
        HStack {
            Button("Test MIDI") {
                print("CC")
                rnbo.sendContinuousController(11, value: 60)
                print("PitchBend")
                rnbo.sendPitchBend(8192)
                print("Patch")
                rnbo.sendPatchChange(1)
                print("Pressure")
                rnbo.sendChannelPressure(60)
                print("Aftertouch")
                rnbo.sendAftertouch(60, pressure: 50)
            }
            Button("Randomize") {
                randomize()
            }
            Button("Send message") {
                let message: [Double] = [220, 330, 0.2, 0.3, 0.5]
                rnbo.sendMessage(message)
            }
            Button("Play Input") {
                rnbo.playAudioFile()
            }
            Button("Pause Input") {
                rnbo.pauseAudioFile()
            }
            Toggle(isOn: $rnbo.showDescription) {
                Text("Show description")
            }
            Toggle(isOn: $enableMic) {
                Text("Mic")
            }
            .onChange(of: enableMic) { newValue in
                rnbo.toggleMic(newValue)
            }
        }
        .padding(.bottom)
    }

    fileprivate func randomize() {
        for i in rnbo.parameters.indices {
            rnbo.setParameterValueNormalizedHot(to: Double.random(in: 0 ... 1), at: i)
        }
    }
}

#Preview {
    Buttons()
}
