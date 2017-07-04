import QtQuick 2.7
import QtQuick.Controls 2.2

ScrollView {
    id: root
    signal clicked()

    TextArea {

        text: qsTr(
"<h1>James Joyce</h1>
<p>James Augustine[1] Aloysius Joyce (2 February 1882 – 13 January 1941) was an Irish novelist, short story writer, and poet. He contributed to the modernist avant-garde and is regarded as one of the most influential and important authors of the 20th century.</p>
<p>Joyce is best known for Ulysses (1922), a landmark work in which the episodes of Homer's Odyssey are paralleled in a variety of literary styles, perhaps most prominently stream of consciousness. Other well-known works are the short-story collection Dubliners (1914), and the novels A Portrait of the Artist as a Young Man (1916) and Finnegans Wake (1939). His other writings include three books of poetry, a play, occasional journalism and his published letters.</p>
<p>Joyce was born in 41 Brighton Square, Rathgar, Dublin—about half a mile from his mother's birthplace in Terenure—into a middle-class family on the way down. A brilliant student, he briefly attended the Christian Brothers-run O'Connell School before excelling at the Jesuit schools Clongowes and Belvedere, despite the chaotic family life imposed by his father's alcoholism and unpredictable finances. He went on to attend University College Dublin.</<p>
<p>In 1904, in his early twenties, Joyce emigrated permanently to continental Europe with his partner (and later wife) Nora Barnacle. They lived in Trieste, Paris and Zurich. Though most of his adult life was spent abroad, Joyce's fictional universe centres on Dublin, and is populated largely by characters who closely resemble family members, enemies and friends from his time there. Ulysses in particular is set with precision in the streets and alleyways of the city. Shortly after the publication of Ulysses, he elucidated this preoccupation somewhat, saying, \"For myself, I always write about Dublin, because if I can get to the heart of Dublin I can get to the heart of all the cities of the world. In the particular is contained the universal.\"[2]</p>
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
