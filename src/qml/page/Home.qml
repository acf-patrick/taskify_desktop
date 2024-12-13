import QtQuick
import QtQuick.Controls

Item {
    Button {
        text: "Click me"

        onClicked: {
            mainWindow.source = "page/second.qml"
        }
    }
}
