import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3


Item {
    id: root
    signal back()

    ColumnLayout {
        id: grid
        anchors.fill: parent

        Button {
            Layout.fillWidth: true
            Layout.fillHeight: true

            text: "<h1>Il Fu Mattia Pascal</h1>"

            onClicked: {
                ilFuMattiaPascal.visible = true;
                grid.visible = false;
            }
        }
        Button {
            Layout.fillWidth: true
            Layout.fillHeight: true

            text: "<h1>Dubliners</h1>"

            onClicked: {
                dubliners.visible = true;
                grid.visible = false;
            }
        }
        Button {
            Layout.columnSpan: 2
            Layout.fillWidth: true
            Layout.fillHeight: true

            text: "<h1>Indietro</h1>"

            onClicked: {
                root.back()
            }
        }
    }

    IlFuMattiaPascal {
        id: ilFuMattiaPascal

        anchors.fill: parent
        visible: false

        onClicked:
        {
            grid.visible = true
            visible = false
        }
    }

    Dubliners {
        id: dubliners

        anchors.fill: parent
        visible: false

        onClicked:
        {
            grid.visible = true
            visible = false
        }
    }
}
