package com.example.fhirpatients

import kotlinx.serialization.Serializable

@Serializable
data class HumanName(
    val given: List<String> = emptyList(),
    val family: String? = null
) {
    val display: String
        get() = (given + listOfNotNull(family)).joinToString(" ").ifBlank { "—" }
}