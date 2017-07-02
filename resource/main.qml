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

        onPatternFound: {
            patternText.text = "Pattern Found " + keypoints + " matched"
        }

        showMatches: showMatchesSwitch.checked

        minNumberMatchesAllowed: minAllowerKeypointsSlider.value
    }

    VideoOutput {
        id: videoOutput
        source: camera

        anchors.fill: parent

        focus : visible // to receive focus and capture key events when visible
        filters: [patternDetectorFilter]
    }

    Switch {
        id: showMatchesSwitch
        text: qsTr("Show matches")

        anchors.bottom: parent.bottom
        anchors.right: parent.right
    }

    Label {
        id: patternText

        anchors.bottom: parent.bottom
        anchors.left: parent.left

        text: ""
    }

    Slider {
        id: minAllowerKeypointsSlider;

        from: 5
        to: 50
        stepSize: 1
    }
}
