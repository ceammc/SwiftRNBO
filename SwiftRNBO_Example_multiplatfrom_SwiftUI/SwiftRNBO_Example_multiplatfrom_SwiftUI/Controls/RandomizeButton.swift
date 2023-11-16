//
//  RandomizeButton.swift
//  SwiftUI_RNBO_FromScratch_Test
//
//  Created by Эльдар Садыков on 13.02.2023.
//

import SwiftUI

struct RandomizeButton: View {
    @EnvironmentObject var rnbo: RNBOAudioUnitHostModel

    fileprivate func randomize() {
        for i in rnbo.parameters.list.indices {
            rnbo.setParameterValueNormalized(to: Double.random(in: 0 ... 1), at: i)
        }
    }

    var body: some View {
        Button("Randomize") {
            randomize()
        }
    }
}
