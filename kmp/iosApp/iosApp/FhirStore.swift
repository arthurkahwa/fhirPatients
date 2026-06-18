//
// Created by Arthur Nsereko Kahwa on 2026-05-09.
//

import Foundation
import Shared

@Observable
final class FhirStore {
    var patients: [Patient] = []
    var isLoading = false
    var error: String?

    private let client = FhirClient(baseUrl: "https://hapi.fhir.org/baseR4")

    func search(family: String) async {
        isLoading = true
        defer { isLoading = false }
        do {
            patients = try await client.searchPatients(family: family)
            error = nil
        } catch {
            self.error = error.localizedDescription
        }
    }
}