import QtQuick 2.15
import QtQuick.Layouts 2.15

Rectangle {
    RowLayout {
        anchors.fill: parent

        Text {
            text: "Taskify"
            font.bold: true
            Layout.alignment: Qt.AlignVCenter
        }

        Item {
            Layout.fillWidth: true
        }

        Text {
            text: "buttons here"
            Layout.alignment: Qt.AlignVCenter
        }
    }
}
