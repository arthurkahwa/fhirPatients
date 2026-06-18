import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ItemDelegate {
    id: row

    required property var patient

    implicitHeight: content.implicitHeight + 24

    ColumnLayout {
        id: content
        anchors.fill: parent
        anchors.leftMargin: 16
        anchors.rightMargin: 16
        anchors.topMargin: 12
        anchors.bottomMargin: 12
        spacing: 2

        Label {
            text: row.patient.displayName
            font.pixelSize: 16
            font.weight: Font.Medium
            elide: Text.ElideRight
            Layout.fillWidth: true
        }

        Label {
            text: row.patient.birthDate
            visible: row.patient.birthDate.length > 0
            font.pixelSize: 13
            color: "#64748B"
        }
    }

    Rectangle {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: 1
        color: "#E2E8F0"
    }
}
