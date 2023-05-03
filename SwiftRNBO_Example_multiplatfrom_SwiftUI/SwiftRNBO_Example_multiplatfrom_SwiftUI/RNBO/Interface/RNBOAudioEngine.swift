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
    private let playerNode = AVAudioPlayerNode()
    private let audioFile: AVAudioFile?
    private let distortionEffect: AVAudioUnitDistortion
    
    private func initInput() {
        let input = self.engine.inputNode
        //let format = input.inputFormat(forBus: 0)
        let format = avAudioUnit!.inputFormat(forBus: 0)
        
        if (format.channelCount > 0) {
           engine.connect(engine.inputNode, to: avAudioUnit!, format: format)
        }
    }
    init() {
        distortionEffect = AVAudioUnitDistortion()
        distortionEffect.loadFactoryPreset(.multiEcho1)
        if let audioFileURL = Bundle.main.url(forResource: "Synth", withExtension: "aif") {
            do {
                audioFile = try AVAudioFile(forReading: audioFileURL)
            } catch {
                print("Error initializing audio file: \(error)")
                audioFile = nil
            }
        } else {
            print("Audio file not found")
            audioFile = nil
        }

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
//        engine.attach(distortionEffect)
        engine.attach(playerNode)
        engine.attach(avAudioUnit!)
        
        switch AVCaptureDevice.authorizationStatus(for: .audio){
        case .authorized:
            do {
                puts("Inputs: authorized");
                
                initInput()
                
            }
            
        case .notDetermined: do {
            puts("Inputs: not determined");
            AVCaptureDevice.requestAccess(for: .audio) { [self]  granted in
                if (granted) {
                    initInput()
                }
            }
        }
        case .denied: do {
            puts("Inputs: denied");
        }
        case .restricted: do {
            puts("Inputs: restricted");
        }
            
        @unknown default:
            do {
                puts("Inputs: and now for something completely different");
            }
        }
        
        assert(avAudioUnit!.auAudioUnit.inputBusses.count > 0)
        assert(playerNode.outputFormat(forBus: 0).channelCount == 2)
        
        // engine.connect(playerNode, to: avAudioUnit!, format: audioFile?.processingFormat)
        let audioUnitFormat =  avAudioUnit!.inputFormat(forBus: 0)
        let procFormat = audioFile?.processingFormat
        engine.connect(playerNode, to: avAudioUnit!, format: audioUnitFormat)
        engine.connect(avAudioUnit!, to: engine.mainMixerNode, format: audioUnitFormat)
        
        // test directly, works here:
        // engine.connect(playerNode, to: engine.mainMixerNode, format: audioFile?.processingFormat)

        let outputFormat = engine.outputNode.inputFormat(forBus: 0)
        engine.connect(engine.mainMixerNode, to: engine.outputNode, format: outputFormat)

        engine.prepare()
        try! engine.start()

        // must be called only when app is didBecomeActive
        // play()
        
    }

    func getAudioUnit() -> RNBOAudioUnit {
        return avAudioUnit!.auAudioUnit as! RNBOAudioUnit
    }

    func play() {
        guard let audioFile = audioFile else {
            return
        }

        playerNode.rate = 1
        playerNode.scheduleFile(audioFile, at: nil) {
            print("Audio playback finished")
        }

        playerNode.play()

    }

    func pause() {
        playerNode.pause()
    }
}
