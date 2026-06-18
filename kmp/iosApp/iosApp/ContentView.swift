import SwiftUI
import Shared

struct ContentView: View {
    @Environment(\.fhir) private var fhir
    @State private var query = ""

    var body: some View {
        NavigationStack {
            VStack(spacing: 0) {
                if fhir.isLoading {
                    ProgressView()
                        .frame(maxWidth: .infinity)
                        .padding()
                }

                if let error = fhir.error {
                    Text("Error: \(error)")
                        .foregroundStyle(.red)
                        .padding()
                }

                List(fhir.patients, id: \.id) { patient in
                    VStack(alignment: .leading, spacing: 4) {
                        Text(patient.name.first?.display ?? "—")
                            .font(.headline)
                        if let dob = patient.birthDate {
                            Text(dob)
                                .font(.caption)
                                .foregroundStyle(.secondary)
                        }
                    }
                }
            }
            .navigationTitle("Patients")
            .searchable(text: $query, prompt: "Family name")
            .onSubmit(of: .search) {
                Task { await fhir.search(family: query) }
            }
        }
    }
}

#Preview {
    ContentView()
}