import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Rectangle {
    id: root

    color: "black"
    opacity: 0.5

    width: 600
    height: 300

    signal back()

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

            onClicked: {
                plot.visible = true
                grid.visible = false
            }
        }
        Button {
            Layout.fillWidth: true
            Layout.fillHeight: true

            text: "<h1>Opere Consigliate</h1>"

            onClicked: {
                suggestedNovel.visible = true;
                grid.visible = false;
            }
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

            text: "<h1>Indietro</h1>"

            onClicked: {
                root.back()
            }
        }
    }

    Plot {
        id: plot
        anchors.fill: parent

        visible: false

        onClicked: {
            grid.visible = true
            plot.visible = false
        }
    }

    Author {
        id: author

        anchors.fill: parent
        visible: false

        onClicked: {
            grid.visible = true
            visible = false;
        }
    }

    SimilarAuthor {
        id: similAuthors
        anchors.fill: parent

        visible: false

        onBack: {
            grid.visible = true
            visible = false
        }
    }

    SuggestedNovel {
        id: suggestedNovel
        anchors.fill: parent

        visible: false

        onBack: {
            grid.visible = true
            visible = false
        }
    }
}
