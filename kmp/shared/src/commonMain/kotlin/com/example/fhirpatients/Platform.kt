package com.example.fhirpatients

interface Platform {
    val name: String
}

expect fun getPlatform(): Platform