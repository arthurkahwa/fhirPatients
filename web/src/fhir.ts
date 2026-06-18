// Minimal FHIR R4 types — matches the Kotlin and Swift sides.
export interface HumanName {
    given?: string[]
    family?: string
}

export interface Patient {
    id: string
    name?: HumanName[]
    birthDate?: string
    gender?: string
}

export interface FhirBundle {
    entry?: Array<{ resource: Patient }>
}

export function displayName(name: HumanName | undefined): string {
    if (!name) return '—'
    const parts = [...(name.given ?? []), name.family].filter(Boolean)
    return parts.length > 0 ? parts.join(' ') : '—'
}

export async function searchPatients(family: string): Promise<Patient[]> {
    const url = `https://hapi.fhir.org/baseR4/Patient?family=${encodeURIComponent(family)}`
    const response = await fetch(url, {
        headers: { Accept: 'application/fhir+json' },
    })
    if (!response.ok) {
        throw new Error(`FHIR request failed: ${response.status}`)
    }
    const bundle = (await response.json()) as FhirBundle
    return (bundle.entry ?? []).map((e) => e.resource)
}