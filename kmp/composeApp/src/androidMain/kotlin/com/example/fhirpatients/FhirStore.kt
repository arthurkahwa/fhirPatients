package com.example.fhirpatients

import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.setValue

class FhirStore(baseUrl: String = "https://hapi.fhir.org/baseR4") {

    private val client = FhirClient(baseUrl)

    var patients by mutableStateOf<List<Patient>>(emptyList())
        private set

    var isLoading by mutableStateOf(false)
        private set

    var error by mutableStateOf<String?>(null)
        private set

    suspend fun search(family: String) {
        isLoading = true
        try {
            patients = client.searchPatients(family)
            error = null
        } catch (t: Throwable) {
            error = t.message ?: "Unknown error"
        } finally {
            isLoading = false
        }
    }
}