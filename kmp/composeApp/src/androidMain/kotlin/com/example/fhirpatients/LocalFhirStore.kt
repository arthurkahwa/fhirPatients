package com.example.fhirpatients

import androidx.compose.runtime.staticCompositionLocalOf

val LocalFhirStore = staticCompositionLocalOf<FhirStore> {
    error("LocalFhirStore not provided")
}
