import QtQuick 2.7
import QtQuick.Controls 2.2

ScrollView {
    id: root
    signal clicked()

    TextArea {

        text: qsTr(
"<h1>Pirandello</h1>
<p>Luigi Pirandello (Girgenti, 28 giugno 1867 – Roma, 10 dicembre 1936) è stato un drammaturgo, scrittore e poeta italiano, insignito del Premio Nobel per la letteratura nel 1934. Per la sua produzione, le tematiche affrontate e l'innovazione del racconto teatrale è considerato tra i maggiori drammaturghi del XX secolo. Tra i suoi lavori spiccano diverse novelle e racconti brevi (in lingua italiana e siciliana) e circa quaranta drammi, l'ultimo dei quali incompleto.</p>
")
        textFormat: Text.RichText
        wrapMode: Text.WordWrap
        horizontalAlignment: Text.AlignLeft

        MouseArea {
            anchors.fill: parent
            onClicked: root.clicked()
        }
    }
}
