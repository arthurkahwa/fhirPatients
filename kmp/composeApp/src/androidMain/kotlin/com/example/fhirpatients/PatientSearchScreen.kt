package com.example.fhirpatients

import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.foundation.text.KeyboardActions
import androidx.compose.foundation.text.KeyboardOptions
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.HorizontalDivider
import androidx.compose.material3.LinearProgressIndicator
import androidx.compose.material3.ListItem
import androidx.compose.material3.OutlinedTextField
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.material3.TopAppBar
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.rememberCoroutineScope
import androidx.compose.runtime.setValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.text.input.ImeAction
import androidx.compose.ui.unit.dp
import kotlinx.coroutines.launch

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun PatientSearchScreen() {
    val fhir = LocalFhirStore.current
    var query by remember { mutableStateOf("") }
    val scope = rememberCoroutineScope()

    Scaffold(
        topBar = { TopAppBar(title = { Text("Patients") }) }
    ) { padding ->
        Column(
            modifier = Modifier.padding(padding).fillMaxSize()
        ) {
            OutlinedTextField(
                value = query,
                onValueChange = { query = it },
                label = { Text("Family name") },
                singleLine = true,
                modifier = Modifier.fillMaxWidth().padding(16.dp),
                keyboardOptions = KeyboardOptions(imeAction = ImeAction.Search),
                keyboardActions = KeyboardActions(
                    onSearch = { scope.launch { fhir.search(query) } }
                )
            )

            if (fhir.isLoading) {
                LinearProgressIndicator(modifier = Modifier.fillMaxWidth())
            }

            fhir.error?.let {
                Text(
                    text = "Error: $it",
                    modifier = Modifier.padding(16.dp)
                )
            }

            LazyColumn {
                items(fhir.patients, key = { it.id }) { patient ->
                    ListItem(
                        headlineContent = {
                            Text(patient.name.firstOrNull()?.display ?: "—")
                        },
                        supportingContent = {
                            patient.birthDate?.let { Text(it) }
                        }
                    )
                    HorizontalDivider()
                }
            }
        }
    }
}