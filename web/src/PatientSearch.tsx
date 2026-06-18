import { useState } from 'react'
import { searchPatients, displayName, type Patient } from './fhir'

export function PatientSearch() {
    const [query, setQuery] = useState('')
    const [patients, setPatients] = useState<Patient[]>([])
    const [isLoading, setIsLoading] = useState(false)
    const [error, setError] = useState<string | null>(null)

    async function handleSearch(e: React.FormEvent) {
        e.preventDefault()
        setIsLoading(true)
        setError(null)
        try {
            const result = await searchPatients(query)
            setPatients(result)
        } catch (err) {
            setError(err instanceof Error ? err.message : 'Unknown error')
        } finally {
            setIsLoading(false)
        }
    }

    return (
        <div className="mx-auto max-w-2xl p-6">
            <h1 className="mb-6 text-2xl font-semibold text-slate-900">Patients</h1>

            <form onSubmit={handleSearch} className="mb-6">
                <label htmlFor="family" className="mb-1 block text-sm font-medium text-slate-700">
                    Family name
                </label>
                <div className="flex gap-2">
                    <input
                        id="family"
                        type="search"
                        value={query}
                        onChange={(e) => setQuery(e.target.value)}
                        placeholder="e.g. Smith"
                        className="flex-1 rounded-md border border-slate-300 px-3 py-2 text-slate-900 focus:border-slate-500 focus:outline-none"
                    />
                    <button
                        type="submit"
                        disabled={isLoading || query.trim().length === 0}
                        className="rounded-md bg-slate-900 px-4 py-2 text-sm font-medium text-white disabled:opacity-50"
                    >
                        Search
                    </button>
                </div>
            </form>

            {isLoading && (
                <div className="mb-4 h-1 w-full overflow-hidden rounded bg-slate-200">
                    <div className="h-full w-1/3 animate-pulse bg-slate-900" />
                </div>
            )}

            {error && (
                <div className="mb-4 rounded-md border border-red-300 bg-red-50 p-3 text-sm text-red-800">
                    {error}
                </div>
            )}

            <ul className="divide-y divide-slate-200 rounded-md border border-slate-200">
                {patients.length === 0 && !isLoading && (
                    <li className="p-4 text-sm text-slate-500">No results yet.</li>
                )}
                {patients.map((patient) => (
                    <li key={patient.id} className="p-4">
                        <div className="font-medium text-slate-900">
                            {displayName(patient.name?.[0])}
                        </div>
                        {patient.birthDate && (
                            <div className="text-sm text-slate-500">{patient.birthDate}</div>
                        )}
                    </li>
                ))}
            </ul>
        </div>
    )
}