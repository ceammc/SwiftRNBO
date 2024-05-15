//
//  XYpad.swift
//  SwiftRNBO_Example_multiplatfrom_SwiftUI
//
//  Created by Eldar Sadykov on 15.05.24.
//

import SwiftUI

struct XYPad: View {
    @EnvironmentObject var rnbo: RNBOAudioUnitHostModel
    @State var location: CGPoint = CGPoint()
    var body: some View {
        GeometryReader { geo in
            Rectangle()
                .foregroundStyle(Color.white)
                .gesture(DragGesture()
                    .onChanged({ value in
                        let xNorm = value.location.x / geo.size.width
                        let yNorm = value.location.y / geo.size.height
                        rnbo.setParameterValueNormalized(to: xNorm, at: 0)
                        rnbo.setParameterValueNormalized(to: yNorm, at: 1)
                        location = value.location
                    })
                )
            Circle()
                .foregroundStyle(.black)
                .frame(width: 50, height: 50)
                .position(location)
        }
    }
}

#Preview {
    XYPad()
}
