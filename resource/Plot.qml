import QtQuick 2.7
import QtQuick.Controls 2.2


ScrollView {
    id: root
    signal clicked()

    TextArea {

        text: qsTr(
                  "
<h2>Trama</h2>
<p>Zeno Cosini, il protagonista dell'opera, proviene da una famiglia ricca, vive nell'ozio e in un rapporto conflittuale con il padre, che si rifletterà su tutta la sua vita. Nell'amore, nei rapporti coi familiari e gli amici, nel lavoro, egli prova un costante senso di inadeguatezza e di \"inettitudine\", che interpreta come sintomi di una malattia. In realtà solo più tardi scoprirà che non è lui a essere malato, ma la società in cui vive.</p>
<h2>Prefazione</h2>
<p>È questo uno dei capitoli più importanti, dato che rappresenta una finzione letteraria ben congegnata. Si tratta di poche righe firmate dal dottor S., lo psicanalista che ha in cura Zeno, il quale espone l'origine del libro. A causa dell'ingiustificata interruzione della terapia da parte di Zeno, proprio nel momento in cui essa stava dando i suoi frutti, il dottore, profondamente ferito nel suo orgoglio professionale, decide di vendicarsi del paziente, pubblicando quelle memorie che lui stesso aveva consigliato a Zeno di scrivere come parte integrante della cura. Tali memorie, in cui Zeno ha accumulate menzogne e verità, non sono altro che i capitoli successivi del libro.</p>
<p>È chiaro che questa finzione letteraria è anche una polemica contro la psicoanalisi, una forma di terapia che proprio in quegli anni iniziava velocemente ad affermarsi, soprattutto nell'Impero austro-ungarico, di cui Trieste faceva parte. L'iniziale S sarebbe interpretabile come la prima lettera del nome del padre della psicoanalisi, Sigmund Freud, anch'egli austriaco (di Vienna), ma potrebbe anche riferirsi all'autore stesso. Si è altresì a lungo ritenuto che il Dottor S. fosse l'analista triestino, nonché seguace di Freud, Edoardo Weiss. Lo studioso Giovanni Palmieri ha ipotizzato che si tratti dello psicologo ginevrino Charles Baudouin.[1]</p>
<h2>Il fumo</h2>
<p>Il protagonista parla della sua malattia del fumo, narrando fatti che coprono tutta la sua vita.</p>
<p>Oltre all'inettitudine, il suo grande problema è il vizio del fumo, del quale non riesce a liberarsi. Il protagonista, infatti, ricorda di aver iniziato a fumare già nell'adolescenza a causa del rapporto conflittuale con il padre. A quest'ultimo rubava inizialmente soldi per comprare le sigarette e in seguito, dopo essere stato scoperto, raccoglieva i sigari fumati a metà sparsi per casa. Nonostante più volte si sia riproposto di smettere, non vi riesce e per questo si sente frustrato. I tentativi si moltiplicano, e anche gli sforzi, ma il problema non viene risolto.</p>
<p>Ogni volta che prova a smettere di fumare, Zeno decide di fumare un'\"ultima sigaretta\" (U.S.) e di annotare la data di questa. Dopo numerosi fallimenti Zeno si rende conto che fumare \"ultime sigarette\" è per lui un'esperienza piacevolissima, in quanto quelle assumono ogni volta un sapore diverso, causato dalla coscienza che dopo quelle non potrà fumarne più. Zeno si rivolge a facoltosi medici, riempie libri e addirittura pareti con la sigla U.S., ma non riesce a smettere: il tentativo dura moltissimi anni e non si realizza mai, neanche dopo essersi recato in una clinica specialistica dove, una volta pentitosi di avere iniziato la cura, corrompe l'infermiera con l'alcol per scappare pensando erroneamente che la moglie lo stia tradendo con il Dottor Muli, il dottore della clinica. Il continuo rimandare un evento è tipico del nevrotico, che, in questo caso, può gustare sempre di più l'ultima sigaretta. Zeno inoltre indica il vizio del fumo come causa dei cambiamenti repentini di facoltà universitaria (passa numerose volte dalla facoltà di chimica a quella di giurisprudenza).</p>
<h2>La morte di mio padre</h2>
<p>Zeno rievoca il rapporto conflittuale con suo padre, dando particolare attenzione ai suoi ultimi giorni di vita.<\p>
<p>Si tratta di una relazione ostacolata dall'incomprensione e dai silenzi. Il padre non ha alcuna stima del figlio, tanto che, per sfiducia, affida l'azienda commerciale di famiglia a un amministratore esterno, l'Olivi. A sua volta il figlio, che si ritiene superiore per intelletto e cultura, non stima il padre e sfugge ai suoi tentativi di parlare di argomenti profondi.</p>
<p>Il più grande dei malintesi è l'ultimo, che avviene in punto di morte: quando il figlio è al suo capezzale, il padre (ormai incosciente) lo colpisce con la mano. Zeno non riuscirà mai a capire il significato di quel gesto: uno schiaffo assestato allo scopo di punirlo o soltanto una reazione inconscia del padre ammalato? L'interrogativo produce un dubbio che accompagnerà il protagonista fino all'ultimo dei suoi giorni. Alla fine Zeno preferisce ricordare il padre come era sempre stato: \"io divenuto il più debole e lui il più forte\".</p>
<h2>La storia del mio matrimonio</h2>
<p>Zeno parla delle vicende che lo portano al matrimonio.</p>
<p>Il protagonista, alla disperata ricerca di una moglie, conosce quattro sorelle, le figlie di Giovanni Malfenti, con il quale Zeno ha stretto rapporto di lavoro e per il quale nutre profonda stima, al punto che lo vedrà come una figura paterna dopo la morte del padre. Egli viene accolto in casa Malfenti da una delle quattro fanciulle, Augusta, la quale non essendo bella e mostrando riguardo verso il protagonista, viene da lui subito \"esclusa\" per un'eventuale proposta di matrimonio. Viene esclusa poco dopo anche Anna, in quanto si tratta di una bambina di soli 8 anni. La più attraente delle figlie è in realtà la primogenita Ada, a cui il protagonista fa dunque la corte. Il suo sentimento però non è ricambiato, perché ella lo considera troppo diverso da lei e incapace di cambiare; del resto è già promessa sposa a Guido, un uomo profondo che lei ama.</p>
<p>Dopo il rifiuto, Zeno si rende conto di non voler rimanere da solo e di avere bisogno di una donna al suo fianco. Per questo motivo, la stessa sera, farà la proposta di matrimonio prima ad Alberta, la quale lo respingerà, e successivamente si accontenta di Augusta, la meno attraente delle sorelle ma quella disposta a dedicare la sua vita a lui e che si rivelerà una moglie ideale.</p>
<p>Anche se a questa moglie Zeno rimane legato da un sincero e tiepido affetto, perché in fondo gli garantisce una comoda e sicura vita familiare, ciò non gli impedisce di farsi un'amante, Carla. Augusta costituisce nel romanzo una figura femminile dolce e tenera, che si prodiga per il proprio marito. In lei Zeno trova la figura materna che cercava e un conforto sicuro mancatogli nell'infanzia; per lui rappresenta \"la salute personificata\".</p>
<h2>La moglie e l'amante</h2>
<p>Il rapporto conflittuale di Zeno Cosini con la sfera femminile (la sua patologia è stata bollata dallo psicologo come sindrome Edipica) è evidenziato anche dalla ricerca dell'amante. Zeno accenna a tale esperienza come un rimedio per sfuggire al «tedio della vita coniugale».</p>
<p>Quella con Carla Gerco è un' «avventura insignificante». Lei è solo una «povera fanciulla», «bellissima», che inizialmente suscita in lui un istinto di protezione. All'inizio Zeno e Carla sono legati da una relazione basata sul semplice desiderio fisico, ma successivamente essa viene sostituita da una vera e propria passione. Anche Carla subisce dei cambiamenti: prima insicura, diventa poi una donna energica e dignitosa e finisce con l'abbandonare il suo amante a favore di un maestro di canto, che Zeno stesso le aveva presentato.</p>
<p>Zeno non smetterà mai di amare la moglie Augusta (che dimostra verso di lui un atteggiamento materno e gli comunica sicurezza). Verso la conclusione del suo rapporto con Carla, invece, maturerà per quest'ultima un sentimento ambivalente che si avvicinerà all'odio.</p>
<h2>Storia di un'associazione commerciale</h2>
<p>Incapace di gestire il proprio patrimonio, Guido prega Zeno di aiutarlo a mettere in piedi un'azienda. Egli dice a se stesso di accettare per \"bontà\", ma in realtà lo fa per un oscuro desiderio di rivalsa e di superiorità nei confronti del fortunato rivale in amore che, nel frattempo, ha sposato Ada.</p>
<p>Anche Guido, peraltro, nei ricordi di Zeno appare come un inetto e comincia, per inesperienza, a sperperare il suo patrimonio e a tradire la moglie con la giovane segretaria Carmen, mentre Zeno ha la soddisfazione di essere incaricato da Ada di aiutare e proteggere il marito. Questi, dopo un'ennesima perdita (ha infatti iniziato a giocare in borsa) simula un tentativo di suicidio, per indurre la moglie ad aiutarlo economicamente. Più tardi ritenterà il colpo astuto, ma (per un banale gioco della sorte) si ucciderà davvero.</p>
<p>Zeno, impegnato a salvarne (per quanto è possibile) il patrimonio, non riesce a giungere in tempo al suo funerale, accodandosi al corteo funebre sbagliato. Per questo è accusato da Ada, divenuta nel frattempo brutta e non più desiderabile per una malattia (il morbo di Basedow), di avere in tal modo espresso la sua gelosia e il suo malanimo verso il marito. Il famoso triangolo matrimoniale termina con tre sconfitte irreparabili, ma anche con l'autoinganno dei tre protagonisti, incapaci di distinguere fra sogno e realtà.</p>
<h2>Psicoanalisi</h2>
<p>Nel capitolo precedente si era concluso il racconto imposto dal medico a Zeno. Questi però lo riprende per ribellarsi al medico, che crede non l'abbia guarito.</p>
<p>Zeno tiene un diario, che in seguito invierà al Dottore per comunicargli il suo punto di vista. Il diario di Zeno si compone di tre parti, contrassegnate dalle date di tre giorni distinti negli anni di guerra 1915-1917. Nella riflessione conclusiva, Zeno si considera completamente guarito, perché ha scoperto che la \"vita attuale è inquinata alle radici\" e che rendersene conto è segno di salute, non di malattia.</p>
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
