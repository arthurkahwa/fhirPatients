package com.example.fhirpatients

import kotlinx.serialization.Serializable

@Serializable
data class Patient(
    val id: String,
    val name: List<HumanName> = emptyList(),
    val birthDate: String? = null,
    val gender: String? = null
)