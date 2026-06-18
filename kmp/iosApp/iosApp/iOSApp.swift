import SwiftUI

@main
struct iOSApp: App {
    @State private var fhir = FhirStore()

    var body: some Scene {
        WindowGroup {
            ContentView()
                .environment(\.fhir, fhir)
        }
    }
}