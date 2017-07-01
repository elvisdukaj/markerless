import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtMultimedia 5.5
import QtQuick.Dialogs 1.2

import com.qubicaamf.vision 1.0

ApplicationWindow {
    id: mainWindow

    visible: true
    width: 800
    height: 600
    title: qsTr("Hello World")

    Camera {
        id: camera
    }

    PatternDetectorFilter {
        id: patternDetectorFilter

        onObjectFound: {
            console.log("object found");
        }
    }

    VideoOutput {
        id: videoOutput
        source: camera

        anchors.fill: parent

        focus : visible // to receive focus and capture key events when visible
        filters: [patternDetectorFilter]
    }
}
