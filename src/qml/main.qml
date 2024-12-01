import QtQuick 2.15
import QtQuick.Controls 2.15
import "component"

ApplicationWindow {
    width: 640
    height: 480
    minimumWidth: 640
    minimumHeight: 480
    visible: true
    flags: Qt.FramelessWindowHint

    TitleBar {
        anchors.left: parent.left
        anchors.right: parent.right
        height: 40
    }
}
