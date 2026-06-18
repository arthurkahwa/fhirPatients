package com.example.fhirpatients

import io.ktor.client.HttpClient
import io.ktor.client.call.body
import io.ktor.client.plugins.contentnegotiation.ContentNegotiation
import io.ktor.client.plugins.defaultRequest
import io.ktor.client.request.accept
import io.ktor.client.request.get
import io.ktor.client.request.parameter
import io.ktor.http.ContentType
import io.ktor.serialization.kotlinx.json.json
import kotlinx.serialization.json.Json

class FhirClient(baseUrl: String = "https://hapi.fhir.org/baseR4") {

    private val base = baseUrl.trimEnd('/')

    private val http = HttpClient {
        install(ContentNegotiation) {
            json(Json { ignoreUnknownKeys = true })
        }

        defaultRequest {
            accept(ContentType("application", "fhir+json"))
        }
    }

    suspend fun searchPatients(family: String): List<Patient> =
        http.get("$base/Patient") { parameter("family", family) }
            .body<FhirBundle>()
            .entry
            .map { it.resource }
}