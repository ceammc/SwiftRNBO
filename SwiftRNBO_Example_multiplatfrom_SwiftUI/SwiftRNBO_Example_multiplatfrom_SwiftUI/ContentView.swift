//
//  ContentView.swift
//  SwiftRNBO_Example_multiplatfrom_SwiftUI
//
//  Created by Эльдар Садыков on 19.02.2023.
//

import SwiftUI

struct ContentView: View {
    @EnvironmentObject var rnbo: RNBOContext

    var body: some View {
        VStack {
            #if !os(tvOS)
                Sliders()
            #endif
            RandomizeButton()
        }
        .padding()
    }
}
