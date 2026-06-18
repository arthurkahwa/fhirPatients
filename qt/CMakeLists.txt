cmake_minimum_required(VERSION 3.21)

project(fhirpatients
    VERSION 1.0.0
    DESCRIPTION "FHIR R4 patient search — Qt 6 / QML"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Quick QuickControls2 Network Qml)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(fhirpatients_app
    src/main.cpp
    src/FhirClient.h
    src/FhirClient.cpp
)

qt_add_qml_module(fhirpatients_app
    URI fhirpatients
    VERSION 1.0
    QML_FILES
        qml/Main.qml
        qml/PatientRow.qml
    SOURCES
        src/HumanName.h
        src/Patient.h
        src/FhirStore.h
        src/FhirStore.cpp
)

target_link_libraries(fhirpatients_app
    PRIVATE
        Qt6::Quick
        Qt6::QuickControls2
        Qt6::Network
        Qt6::Qml
)

target_include_directories(fhirpatients_app
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set_target_properties(fhirpatients_app PROPERTIES
    OUTPUT_NAME fhirpatients
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
