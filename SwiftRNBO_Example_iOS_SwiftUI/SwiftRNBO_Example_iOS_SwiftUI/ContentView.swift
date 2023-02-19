//
//  ContentView.swift
//  SwiftRNBO_Example_iOS_SwiftUI
//
//  Created by Эльдар Садыков on 19.02.2023.
//

import SwiftUI

struct ContentView: View {
    @EnvironmentObject var rnbo: RNBOContext

    var body: some View {
        VStack {
            Sliders()
            RandomizeButton()
        }
        .padding()
    }
}
