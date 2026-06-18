package com.example.fhirpatients

import kotlinx.serialization.Serializable

@Serializable
data class FhirBundle(
    val entry: List<Entry> = emptyList()
) {
    @Serializable
    data class Entry(val resource: Patient)
}