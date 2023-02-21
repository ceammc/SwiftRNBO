//
//  AudioEngine.swift
//  RNBO_AVAudioEngine
//
//  Created by Alex Nadzharov on 13.02.2023.
//

import AudioToolbox
import AVFoundation

class RNBOAudioEngine {
    let audioEngine = AVAudioEngine()
    var customEffect: AVAudioUnit?

    init() {
        #if os(tvOS)
            let myUnitType = kAudioUnitType_Generator
        #else
            let myUnitType = kAudioUnitType_Effect
        #endif
        let mySubType: OSType = 0x71717171
        let myManu: OSType = 0x70707070

        let compDesc = AudioComponentDescription(componentType: myUnitType,
                                                 componentSubType: mySubType,
                                                 componentManufacturer: myManu,
                                                 componentFlags: 0,
                                                 componentFlagsMask: 0)

        let cls = RNBOAudioUnit.self
        AUAudioUnit.registerSubclass(cls,
                                     as: compDesc,
                                     name: "RNBOAudioUnit", // my AUAudioUnit subclass
                                     version: 1)

        AVAudioUnit.instantiate(with: compDesc,
                                options: AudioComponentInstantiationOptions.loadOutOfProcess) { audiounit, _ in

            self.customEffect = audiounit! // save AVAudioUnit
        }

        audioEngine.attach(customEffect!)
        #if !os(tvOS)
            let input = audioEngine.inputNode
            let format = input.inputFormat(forBus: 0)

            audioEngine.connect(audioEngine.inputNode, to: customEffect!, format: format)
        #endif
        audioEngine.connect(customEffect!, to: audioEngine.mainMixerNode, format: audioEngine.mainMixerNode.outputFormat(forBus: 0))

        let outputFormat = audioEngine.outputNode.inputFormat(forBus: 0)
        audioEngine.connect(audioEngine.mainMixerNode,
                            to: audioEngine.outputNode,
                            format: outputFormat)

        audioEngine.prepare()
        try! audioEngine.start()
    }

    func getAudioUnit() -> RNBOAudioUnit {
        return customEffect!.auAudioUnit as! RNBOAudioUnit
    }
}
