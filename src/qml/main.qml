import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: "Taskify"

    Component.onCompleted: {
        const req = new XMLHttpRequest();
        req.open("GET", "http://127.0.0.1:8000/board", true);

        req.onreadystatechange = () => {
            if (req.readyState === 4 && req.status === 200) {
                console.log('Response from TASKIFY : ');
                console.log(`${req.responseText}`);
            }
        };

        req.send();
    }
}
