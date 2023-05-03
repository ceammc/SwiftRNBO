# SwiftRNBO

## About

SwiftRNBO is a compatibility layer between a _Swift-based_ Apple platform project and C++ code that can be exported using [Cycling '74 RNBO](https://cycling74.com/products/rnbo) software. It requires no knowledge of C++ to use and allows any Apple platform developer familiar with the [Cycling '74 Max](https://cycling74.com/products/max) programming environment to build sophisticated and efficient audio applications with the ease of use of Swift and SwiftUI.

## Supported platfroms

iOS, macOS and tvOS are fully supported. However, all universal platform restrictions apply, such as tvOS lacking audio input and MIDI.

## Starting from a sample project

The easiest way to start using SwiftRNBO is to simply download _the sample project_. This frees you from having to set up the project yourself: everything related to the translation layer is contained in a separate folder that does not require any manual changes. The only thing that will need to be done is to replace the contents of the `Export` folder with the result of your RNBO patcher export.

If you want to create a project from scratch, please refer to [Creating a new project](#creating-a-new-project).

## Folder structure

    ...
    ├── RNBO
    │   ├── Export              # replace this folder's content with your RNBO C++ Source Code Export results
    │   ├── Bindings            # Objective-C++ files, the actual translation layer
    │   └── Interface           # Swift classes and structures to use in your Swift-based app
    ...

## Interacting with the exported patcher

`RNBOAudioUnit` is the Objective-C++ wrapper for the exported RNBO C++ Source Code. It is the main class to interact with in order to control the exported patcher's behavior.

It is accessed through the `RNBOAudioEngine` Swift class:

```Swift
let audioEngine = RNBOAudioEngine()
let audioUnit = audioEngine.getAudioUnit()
```

`RNBOParameter` is a Swift data structure for storing values and other attributes of RNBO parameters such as their initial, minimum and maximum values, normalization exponent, steps, displayed name, etc. It is used only by Swift part of your application and changing it directly has no effect on the RNBO patcher.

In order get an array of all of the parameters an `RNBOAudioUnit`'s `getParametersArray()` method can be used.

Since the initialization of an `RNBOAudioEngine` instance, getting an `RNBOAudioUnit` from it and storing its parameters in an array is usually done in one time during the initial setup, all of these operations are performed during the `RNBOContext` structure's initialization. Therefore, it is suggested just to store an instance of this structure in some always accessible place, for example:

```Swift
import SwiftUI

@main
struct SwiftRNBOApp: App {
    @ObservedObject var rnbo = RNBOAudioUnitHostModel()

    var body: some Scene {
        WindowGroup {
            ContentView()
                .environmentObject(rnbo)
        }
    }
}
```

Then use this `RNBOAudioUnitHostModel` instance's methods to interact with the RNBO patcher:

```Swift
var rnbo = RNBOContext()
rnbo.setParameterValue(to: 0.0, at: 1)
rnbo.setParameterValueNormalized(to: 0.5, at: 3)
```

... and its `parameters` property to keep your application's UI in sync with it.

## Creating a new project

There are several steps to ensure that SwiftRNBO will work in your newly created project.

1. **Download this repository**
1. **Import the `RNBO` folder to your project**
   - In Xcode select the root folder of your project, i.e. the one where the `Main.storyboard` or the `ContentView.swift` files are located, not the project itself;
   - Go to 'File' -> 'Add files to [*xcode_project_name*]...';
   - Select the `RNBO` folder in the downloaded repository. Don't click '_Add_' yet;
   - Make sure that '_Copy files if needed_' is checked;
   - Choose '_Create groups_' in '_Added folders_';
   - Deselect all checkboxes in the _'Add to targets'_ section;
   - Click '_Add_'.
1. **Define all the necessary compile sources**

   - In the Xcode's Navigator area go to `RNBO/Interface` and select all the files in that group;
   - In the Inspector area enable the '_Target Membership_' in all of the desired targets.
   - Do the same with the following files and folders inside the `RNBO` group:
     - `Bindings/RNBOAudioUnit.mm`
     - `Export/rnbo/RNBO.cpp`
     - `Export/rnbo_source.cpp`
     - `Export/dependencies.json`
     - `Export/presets.json`
     - `Export/description.json`
     - `Export/media` as a [folder reference](#using-sample-dependencies).

1. **Define the path to an Objective-C Bridging Header**
   - Select your project in the Xcode Navigator area (the one with the blue icon);
   - In the Editing area select your target's Build Settings;
   - Search for the '_Objective-C Bridging Header_' field (use the '_filter_' textfield);
   - Enter `${PRODUCT_NAME}/RNBO/Bindings/RNBO-Bridging-Header.h` into it.
1. **Define the Header Search Paths**
   - Without leaving the '_Build Settings_' tab search for the '_Header Search Paths_' field;
   - Add `${PRODUCT_NAME}/RNBO/export` to it and select '_recursive_' in the dropdown to the right.
1. **Enter the Microphone usage description (only for iOS and multiplatform)**
   - Without leaving the '_Build Settings_' tab search for the '_Privacy - Microphone usage description_' field;
   - Enter _"This app uses microphone to ... (your reason)"_ into it.
1. **Disable App Sandbox (only for macOS and multiplatform)**
   - Select the '_Signing & Capabilities_' tab.
   - Locate the '_App Sandbox_' section and press the trash icon to the right of the section title.

## Using sample dependencies

> **Important!** In order for your audio sample dependencies to be recognized, you need to add your `media` folder from the RNBO export folder to your Bundle as a **_folder reference, not a group_**. This way its path will be preserved in App resources: `.../media/*.wav`.

If you already have a `media` folder as a group as a result of adding of the whole `Export` folder to your project, you can right click on it and choose '_Show in Finder_', then drag and drop it into the same group this time with the '_Create folder references'_ option enabled. At this point you can delete the `media` group (gray icon) and leave only the `media` folder reference (blue icon). Just make sure to choose '_Remove References_' instead of '_Move to trash_' while deleting the group.

## Current limitations

- Only **16 bit** `wav` and `aiff` files **under 4Gb** in size are allowed as sample dependencies;
- Only parameter changes are currently supported. MIDI functionality, messages, outports, inports, multichannel audio and other such things will be added during the ongoing development;
- Only SwiftUI multiplatform sample project currently exists. UIKit and Objective-C examples will be added in the future;
- Only a fraction of methods is currently implemented;
- SwiftRNBO is currently available only as an example Xcode project, not a package. There are many inconveniences because of that. We are looking forward to fix that as soon as possible.

## Credits

We say a big thank you to composer, media artist and audio developer [Alex Nadzharov](https://github.com/njazz), who actually made RNBO interact with Swift and Apple's audio API. His knowledge of audio development and C++ allowed this project to exist. All the changes that are in any way connected to bridging C++ and Swift continue to happen only because of his invaluable contribution.
