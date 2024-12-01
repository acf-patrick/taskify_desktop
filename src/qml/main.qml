import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

ApplicationWindow {
    id: mainWindow
    minimumWidth: 640
    minimumHeight: 480
    visible: true
    title: "Taskify"

    Material.theme: Material.Dark
    Material.accent: Material.Purple

    property alias loader: pageLoader

    Loader {
        id: pageLoader
        anchors.fill: parent
        source: "page/Home.qml"
    }
}
