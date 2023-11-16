//
//  MessageTestButtons.swift
//  SwiftRNBO_Example_multiplatfrom_SwiftUI
//
//  Created by Эльдар Садыков on 21.02.2023.
//

import SwiftUI

struct MessageTestButtons: View {
    @EnvironmentObject var rnbo: RNBOContext
    var body: some View {
        HStack {
            Button("Send message") {
                let message: [Double] = [220, 330, 0.2, 0.3, 0.5]
                rnbo.sendMessage(message)
            }
        }
    }
}
