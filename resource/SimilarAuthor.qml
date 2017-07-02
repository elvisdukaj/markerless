import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3


Item {
    id: root
    signal clicked()

    ColumnLayout {
        id: grid
        anchors.fill: parent

        Button {
            Layout.fillWidth: true
            Layout.fillHeight: true

            text: "<h1>Pirandello</h1>"

            onClicked: {
                pirandello.visible = true;
                grid.visible = false;
            }
        }
        Button {
            Layout.fillWidth: true
            Layout.fillHeight: true

            text: "<h1>T. Eliot</h1>"

            onClicked: {
                eliot.visible = true;
                grid.visible = false;
            }
        }
        Button {
            Layout.columnSpan: 2
            Layout.fillWidth: true
            Layout.fillHeight: true

            text: "<h1>Indietro</h1>"

            onClicked: {
                root.clicked()
            }
        }

    }

    Pirandello {
        id: pirandello

        anchors.fill: parent
        visible: false

        onClicked:
        {
            grid.visible = true
            pirandello.visible = false
        }
    }

    Eliot {
        id: eliot
        anchors.fill: parent
        visible: false

        onClicked:
        {
            grid.visible = true
            eliot.visible = false
        }
    }
}
