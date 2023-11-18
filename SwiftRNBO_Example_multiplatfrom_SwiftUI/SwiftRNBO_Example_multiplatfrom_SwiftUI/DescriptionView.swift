//
//  DescriptionView.swift
//  SwiftRNBO_Example_multiplatfrom_SwiftUI
//
//  Created by Eldar Sadykov on 18.11.2023.
//

#if !os(tvOS)
    import SwiftUI

    struct DescriptionView: View {
        @EnvironmentObject var rnbo: RNBOAudioUnitHostModel

        var body: some View {
            Group {
                if let rnboDescription = rnbo.description {
                    List {
                        Section(header: Text("Parameters")) {
                            ForEach(rnboDescription.parameters.indices, id: \.self) { index in
                                DisclosureGroup("\(rnboDescription.parameters[index].displayName)") {
                                    ParameterView(parameter: rnboDescription.parameters[index])
                                }
                            }
                        }

                        Section(header: Text("External Data Refs")) {
                            ForEach(rnboDescription.externalDataRefs, id: \.id) { ref in
                                Text(ref.file)
                            }
                        }
                        Section(header: Text("Inports")) {
                            ForEach(rnboDescription.inports, id: \.tag) { port in
                                PortView(port: port)
                            }
                        }

                        Section(header: Text("Outports")) {
                            ForEach(rnboDescription.outports, id: \.tag) { port in
                                PortView(port: port)
                            }
                        }

                        Section(header: Text("Inlets")) {
                            ForEach(rnboDescription.inlets.indices, id: \.self) { index in
                                InletOutletView(inletOutlet: rnboDescription.inlets[index])
                            }
                        }

                        Section(header: Text("Outlets")) {
                            ForEach(rnboDescription.outlets.indices, id: \.self) { index in
                                InletOutletView(inletOutlet: rnboDescription.outlets[index])
                            }
                        }

                        Section(header: Text("Meta")) {
                            MetaView(meta: rnboDescription.meta)
                        }
                    }
                    .frame(minHeight: 100)
                } else {
                    Text("Error loading description")
                        .padding()
                        .background()
                }
            }

            .padding(.bottom)
        }
    }

    struct ParameterView: View {
        let parameter: Parameter

        var body: some View {
            Text("Name: \(parameter.name)")
            Text("ID: \(parameter.paramId)")
            Text("Minimum: \(parameter.minimum)")
            Text("Maximum: \(parameter.maximum)")
            // ... Display other properties of Parameter
        }
    }

    struct ExternalDataRefView: View {
        let ref: ExternalDataRef

        var body: some View {
            Text("ID: \(ref.id)")
            Text("File: \(ref.file)")
            // ... other properties
        }
    }

    struct PortView: View {
        let port: Port

        var body: some View {
            Text("Tag: \(port.tag)")
            // ... other properties
        }
    }

    struct InletOutletView: View {
        let inletOutlet: InletOutlet

        var body: some View {
            DisclosureGroup("\(inletOutlet.type.capitalizedSentence)") {
                if let index = inletOutlet.index {
                    Text("Index: \(index)")
                }
                if let tag = inletOutlet.tag {
                    Text("Tag: \(tag)")
                }
                // ... other properties
            }
        }
    }

    struct MetaView: View {
        let meta: Meta

        var body: some View {
            Text("Architecture: \(meta.architecture)")
            Text("Filename: \(meta.filename)")
            // ... other properties
        }
    }
#endif

extension String {
    var capitalizedSentence: String {
        // 1
        let firstLetter = prefix(1).capitalized
        // 2
        let remainingLetters = dropFirst().lowercased()
        // 3
        return firstLetter + remainingLetters
    }
}
