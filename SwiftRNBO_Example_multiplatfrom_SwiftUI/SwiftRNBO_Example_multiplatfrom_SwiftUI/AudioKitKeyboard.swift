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

        var body: some View {
            Keyboard { pitch, point in
                rnbo.sendNoteOn(UInt8(pitch.midiNoteNumber), velocity: UInt8(point.y * 127))
            } noteOff: { pitch in
                rnbo.sendNoteOff(UInt8(pitch.midiNoteNumber))
            }
            .frame(height: 100)
            .frame(minWidth: 600)
        }
    }

    #Preview {
        AudioKitKeyboard()
    }
#endif
