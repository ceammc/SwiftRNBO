//
//  Buttons.swift
//  SwiftRNBO_Example_multiplatfrom_SwiftUI
//
//  Created by Eldar Sadykov on 17.11.2023.
//

import SwiftUI

struct Buttons: View {
    @EnvironmentObject var rnbo: RNBOAudioUnitHostModel
    var body: some View {
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
