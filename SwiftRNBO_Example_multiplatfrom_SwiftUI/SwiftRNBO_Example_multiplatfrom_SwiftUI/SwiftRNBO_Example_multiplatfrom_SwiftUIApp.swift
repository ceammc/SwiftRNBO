//
//  SwiftRNBO_Example_multiplatfrom_SwiftUIApp.swift
//  SwiftRNBO_Example_multiplatfrom_SwiftUI
//
//  Created by Эльдар Садыков on 19.02.2023.
//

import SwiftUI

@main
struct SwiftRNBO_Example_multiplatfrom_SwiftUIApp: App {
    @ObservedObject var rnbo = RNBOAudioUnitHostModel()
    var body: some Scene {
        WindowGroup {
            ContentView()
                .onAppear { rnbo.connectEventHandler() }
                .environmentObject(rnbo)
        }
    }
}
