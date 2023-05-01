//
//  AudioEngine.swift
//  RNBO_AVAudioEngine
//
//  Created by Alex Nadzharov on 13.02.2023.
//

import AVFoundation

class RNBOAudioEngine {
    private let engine = AVAudioEngine()
    private var avAudioUnit: AVAudioUnit?

    init() {
        #if os(tvOS)
            let type = kAudioUnitType_Generator
        #else
            let type = kAudioUnitType_Effect
        #endif
        let subType: OSType = 0x71717171
        let manufacturer: OSType = 0x70707070

        let description = AudioComponentDescription(componentType: type, componentSubType: subType, componentManufacturer: manufacturer, componentFlags: 0, componentFlagsMask: 0)

        let subclass = RNBOAudioUnit.self

        AUAudioUnit.registerSubclass(subclass, as: description, name: "RNBOAudioUnit", version: 1)

        AVAudioUnit.instantiate(with: description, options: AudioComponentInstantiationOptions.loadOutOfProcess) { avAudioUnit, _ in
            self.avAudioUnit = avAudioUnit! // save AVAudioUnit
        }

        engine.attach(avAudioUnit!)
        #if !os(tvOS)
            let input = engine.inputNode
            let format = input.inputFormat(forBus: 0)

            engine.connect(engine.inputNode, to: avAudioUnit!, format: format)
        #endif
        engine.connect(avAudioUnit!, to: engine.mainMixerNode, format: engine.mainMixerNode.outputFormat(forBus: 0))

        let outputFormat = engine.outputNode.inputFormat(forBus: 0)
        engine.connect(engine.mainMixerNode,
                       to: engine.outputNode,
                       format: outputFormat)

        engine.prepare()
        try! engine.start()
    }

    func getAudioUnit() -> RNBOAudioUnit {
        return avAudioUnit!.auAudioUnit as! RNBOAudioUnit
    }
}
