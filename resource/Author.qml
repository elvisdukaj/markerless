import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Label {
    id: root

    signal clicked()

    text: qsTr("<h1>Italo Svevo is cool</h1>")

    MouseArea {
        anchors.fill: parent
        onClicked: root.clicked()
    }
}

