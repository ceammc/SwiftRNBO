//
//  AudioKitKeyboard.swift
//  SwiftRNBO_Example_multiplatfrom_SwiftUI
//
//  Created by Eldar Sadykov on 17.11.2023.
//

#if !os(tvOS)
    import Keyboard
    import SwiftUI

    struct AudioKitKeyboard: View {
        @EnvironmentObject var rnbo: RNBOAudioUnitHostModel
        @State private var latch = false
        var body: some View {
            VStack {
                HStack {
                    Toggle(isOn: $latch) {
                        Text("Latch keys")
                    }
                    Spacer()
                }
                Keyboard(latching: latch) { pitch, point in
                    let pitch = UInt8(pitch.midiNoteNumber)
                    let velocity = latch ? 60 : UInt8(point.y * 127)
                    rnbo.sendNoteOn(pitch, velocity: velocity)
                } noteOff: { pitch in
                    let pitch = UInt8(pitch.midiNoteNumber)
                    rnbo.sendNoteOff(pitch)
                }
                .frame(height: 100)
                .frame(minWidth: 600)
            }
        }
    }

    #Preview {
        AudioKitKeyboard()
    }
#endif
