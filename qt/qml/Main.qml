import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import fhirpatients

ApplicationWindow {
    id: window
    width: 480
    height: 720
    visible: true
    title: qsTr("Patients")

    header: ToolBar {
        Label {
            anchors.centerIn: parent
            text: qsTr("Patients")
            font.pixelSize: 18
            font.bold: true
        }
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        RowLayout {
            Layout.fillWidth: true
            Layout.margins: 16
            spacing: 8

            TextField {
                id: familyField
                Layout.fillWidth: true
                placeholderText: qsTr("Family name")
                onAccepted: FhirStore.search(text)
            }

            Button {
                text: qsTr("Search")
                enabled: !FhirStore.isLoading && familyField.text.trim().length > 0
                onClicked: FhirStore.search(familyField.text)
            }
        }

        ProgressBar {
            Layout.fillWidth: true
            indeterminate: true
            visible: FhirStore.isLoading
        }

        Rectangle {
            id: errorBanner
            Layout.fillWidth: true
            Layout.leftMargin: 16
            Layout.rightMargin: 16
            Layout.topMargin: 8
            visible: FhirStore.error.length > 0
            color: "#FEE2E2"
            border.color: "#FCA5A5"
            radius: 6
            implicitHeight: errorText.implicitHeight + 16

            Label {
                id: errorText
                anchors.fill: parent
                anchors.margins: 8
                text: qsTr("Error: %1").arg(FhirStore.error)
                color: "#991B1B"
                wrapMode: Text.Wrap
            }
        }

        ListView {
            id: results
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            model: FhirStore.patients

            delegate: PatientRow {
                required property var modelData
                width: results.width
                patient: modelData
            }

            ScrollBar.vertical: ScrollBar {}

            Label {
                anchors.centerIn: parent
                visible: results.count === 0 && !FhirStore.isLoading
                text: qsTr("No results yet.")
                color: "#94A3B8"
            }
        }
    }
}
