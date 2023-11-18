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
                                let displayName = rnboDescription.parameters[index].displayName
                                let name = rnboDescription.parameters[index].name
                                let groupTitle = displayName == "" ? name : displayName
                                DisclosureGroup("\(groupTitle)") {
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
            Text("Minimum Value: \(parameter.minimum)")
            Text("Maximum Value: \(parameter.maximum)")
            Text("Exponent: \(parameter.exponent)")
            Text("Steps: \(parameter.steps)")
            Text("Initial Value: \(parameter.initialValue)")
            Text("Is Enum: \(parameter.isEnum ? "Yes" : "No")")
            // Enum values (if any)
            if !parameter.enumValues.isEmpty {
                Text("Enum Values: \(parameter.enumValues.map { "\($0)" }.joined(separator: ", "))")
            }
            Text("Display Name: \(parameter.displayName)")
            Text("Unit: \(parameter.unit)")
            Text("Order: \(parameter.order)")
            Text("Debug: \(parameter.debug ? "Yes" : "No")")
            Text("Visible: \(parameter.visible ? "Yes" : "No")")
            if let signalIndex = parameter.signalIndex {
                Text("Signal Index: \(signalIndex)")
            } else {
                Text("Signal Index: Not Available")
            }
            Text("IO Type: \(parameter.ioType)")
        }
    }

    struct ExternalDataRefView: View {
        let ref: ExternalDataRef

        var body: some View {
            Text("ID: \(ref.id)")
            Text("File: \(ref.file)")
            Text("Tag: \(ref.tag)")
            Text("Type: \(ref.type)")
        }
    }

    struct PortView: View {
        let port: Port

        var body: some View {
            Text("Tag: \(port.tag)")
            if port.meta != "" {
                Text("Meta: \(port.meta)")
            }
        }
    }

    struct InletOutletView: View {
        let inletOutlet: InletOutlet

        var body: some View {
            let indexString: String = if let index = inletOutlet.index {
                String(index)
            } else {
                ""
            }
            let tagString = if let tag = inletOutlet.tag {
                ": \(tag)"
            } else {
                ""
            }

            Text("\(inletOutlet.type.capitalizedSentence) \(indexString)\(tagString)")
        }
    }

    struct MetaView: View {
        let meta: Meta

        var body: some View {
            Text("architecture: \(meta.architecture)")
            Text("filename: \(meta.filename)")
            Text("rnboobjname: \(meta.rnboobjname)")
            Text("maxversion: \(meta.maxversion)")
            Text("rnboversion: \(meta.rnboversion)")
            Text("name: \(meta.name)")
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
