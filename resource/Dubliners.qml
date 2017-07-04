import QtQuick 2.7
import QtQuick.Controls 2.2

ScrollView {
    id: root
    signal clicked()

    TextArea {

        text: qsTr(
"<h2>Dubliners</h2>
<p>Dubliners is a collection of fifteen short stories by James Joyce, first published in 1914.[1] They form a naturalistic depiction of Irish middle class life in and around Dublin in the early years of the 20th century.</p>
<h2>Style</h2>
<p>When discussing Joyce's Dubliners, there are two types of critics that are often at the forefront of the conversation: the \"Realists\" and the \"Symbolists\". The Realists view Dubliners as the most simple of Joyce's works, which often causes them to disregard the revolutionary nature of the work. The symbolists instead neglect the rebellious meanings behind Joyce's symbols. While some choose only one side to argue, others believe that Dubliners completely defies any form of characterization. Without any clear evidence of thematic unity, logic of plot, or closure, Joyce prevents any conclusive critical analysis.[4] As Sonja Bašić argues, the book \"should be seen not just as a realist/naturalist masterpiece, but as a significant stepping- stone integrated into the modernist structure of Joyce's mature work.\"[4]</p>
<p>It has been argued that the narrators in Dubliners rarely mediate, which means that there are limited descriptions of their thoughts and emotions, a practice said to accompany narratorial invisibility where the narrator sees instead of tells. While some point to Joyce's use of free indirect discourse as a way to understand his characters, he often obscures the reliability of his characters in a way that would make any kind of analysis very difficult.[4] As Richard Ellmann has argued, \"Joyce claims importance by claiming nothing\"[5] His characters' personalities can only be observed because they are not explicitly told.</p>
<p>The collection as a whole displays an overall plan, beginning with stories of youth and progressing in age to culminate in The Dead. Great emphasis is laid upon the specific geographic details of Dublin, details to which a reader with a knowledge of the area would be able to directly relate. The multiple perspectives presented throughout the collection serve to compare the characters and people in Dublin at this time.</p>
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
