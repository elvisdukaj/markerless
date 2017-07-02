import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Rectangle {
    id: root

    color: "black"
    opacity: 0.5

    width: 600
    height: 300

    signal exit()

    GridLayout {
        id: grid
        anchors.fill: parent
        columns: 2

        Button {
            Layout.fillWidth: true
            Layout.fillHeight: true

            text: "<h1>Autore</h1>"

            onClicked: {
                author.visible = true;
                grid.visible = false;
            }
        }
        Button {
            Layout.fillWidth: true
            Layout.fillHeight: true

            text: "<h1>Romanzo</h1>"
        }
        Button {
            Layout.fillWidth: true
            Layout.fillHeight: true

            text: "<h1>Generi Simili</h1>"
        }
        Button {
            Layout.fillWidth: true
            Layout.fillHeight: true

            text: "<h1>Autori Simili</h1>"

            onClicked: {
                similAuthors.visible = true;
                grid.visible = false;
            }
        }
        Button {
            Layout.columnSpan: 2
            Layout.fillWidth: true
            Layout.fillHeight: true

            text: "<h1>Esci</h1>"

            onClicked: {
                root.exit()
            }
        }
    }

    Author {
        id: author

        anchors.fill: parent
        visible: false

        onClicked: {
            grid.visible = true
            author.visible = false;
        }
    }

    SimilarAuthor {
        anchors.fill: parent

        id: similAuthors
        visible: false

        onClicked: {
            grid.visible = true
            similAuthors.visible = false
        }
    }
}
