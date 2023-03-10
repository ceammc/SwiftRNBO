//
//  SwiftRNBO_Example_multiplatfrom_SwiftUIApp.swift
//  SwiftRNBO_Example_multiplatfrom_SwiftUI
//
//  Created by Эльдар Садыков on 19.02.2023.
//

import SwiftUI

@main
struct SwiftRNBO_Example_multiplatfrom_SwiftUIApp: App {
    @ObservedObject var rnbo = RNBOContext()
    var body: some Scene {
        WindowGroup {
            ContentView()
                .environmentObject(rnbo)
                .frame(minWidth: 600)
        }
    }
}
