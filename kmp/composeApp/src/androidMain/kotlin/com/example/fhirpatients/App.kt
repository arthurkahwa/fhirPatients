package com.example.fhirpatients

import androidx.compose.material3.MaterialTheme
import androidx.compose.runtime.Composable
import androidx.compose.runtime.CompositionLocalProvider
import androidx.compose.runtime.remember

@Composable
fun App() {
    val fhir = remember { FhirStore() }
    MaterialTheme {
        CompositionLocalProvider(LocalFhirStore provides fhir) {
            PatientSearchScreen()
        }
    }
}