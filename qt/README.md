# Qt 6 / QML target — `fhirpatients`

The Qt-native variant of the same FHIR R4 patient search. Built with **Qt 6.5+, C++20, QML, Qt Network, Qt Quick Controls 2**.

## Build & run

```bash
cd qt
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH=$(brew --prefix qt)
cmake --build build
./build/fhirpatients
```

### Toolchain

- **Qt 6.5+** — `brew install qt` (macOS), `sudo apt install qt6-base-dev qt6-declarative-dev qt6-quickcontrols2-dev` (Debian/Ubuntu), or the Qt online installer
- **CMake 3.21+**
- A C++20-capable compiler (Clang 13+, GCC 11+, MSVC 2019+)

## Architecture mirror

The Qt target preserves the same surface as the Android/iOS/Web targets:

| Surface | Equivalent |
|---|---|
| `src/HumanName.h` | `HumanName.kt` / `HumanName` in TS — `Q_GADGET` value type with `display` |
| `src/Patient.h` | `Patient.kt` — `Q_GADGET` value type with `displayName` |
| `src/FhirClient.{h,cpp}` | `FhirClient.kt` — HTTP + JSON, hand-rolled, no SDK |
| `src/FhirStore.{h,cpp}` | `FhirStore.kt` / `FhirStore.swift` — `Q_PROPERTY` + `NOTIFY` is Qt's `mutableStateOf`/`@Observable` |
| `qml/Main.qml` | `PatientSearchScreen.kt` / `ContentView.swift` / `PatientSearch.tsx` — UI |
| `qml/PatientRow.qml` | `ListItem` (Compose) / `VStack` row (SwiftUI) / `<li>` (React) |

`FhirStore` is registered as a `QML_SINGLETON` — the QML equivalent of `CompositionLocalProvider` on Android or `EnvironmentValues` on iOS. The QML tree refers to `FhirStore.patients` directly with no instantiation.
