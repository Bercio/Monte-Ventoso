Obiettivo
=========

L’obiettivo del progetto è quello di simulare l’arrampicata di un
individuo(scimmia) su una parete liscia dotata di appigli, che
costituiscono passaggi obbligati che la scimmia deve attraversare per
poter arrivare in cima alla parete. Per la creazione di una scimmia
capace è stato scelto di usare un algoritmo genetico, in modo tale da
far evolvere le strategie di salita della scimmia, ottimizzandole.

Piano di lavoro
===============

Primo tentativo: scimmie primitive
----------------------------------

Il progetto prevede lo sviluppo di tre parti fondamentali:

-   La creazione della parete su cui la scimmia si deve muovere: abbiamo
    ritenuto comodo schematizzare la parete come un grafo in cui gli
    appigli sono rappresentati dai nodi, i quali sono collegati tra loro
    solo se abbastanza vicini da permettere alla scimmia di passare da
    uno all’altro.

-   La creazione della scimmia. Consiste nel decidere quali sono le
    possibili azioni della scimmia quando si trova davanti ad una certa
    configurazione degli appigli. Bisogna quindi determinare quanta
    parte di parete la scimmia ha facoltà di vedere e il set di
    possibili azioni che può intraprendere in base a ciò che vede
    attorno a sé.

    È stato scelto, almeno nella fase iniziale del progetto, di
    attribuire alla scimmia una visuale e un set di possibili azioni
    ristretti: essa conosce infatti solo se tra i nodi che può
    raggiungere sono presenti:

    -   nodi che si trovano più in alto rispetto al punto in cui si
        trova e su cui è giá passata;

    -   nodi che si trovano più in alto rispetto al punto in cui si
        trova e su cui non è mai passata;

    -   nodi che si trovano più in basso rispetto al punto in cui si
        trova e su cui è giá passata;

    -   nodi che si trovano più in basso rispetto al punto in cui si
        trova e su cui non è mai passata.

    Quindi ci sono quattro categorie di nodi, ognuna delle quali è
    contrassegnata dall’attributo presente se il nodo su cui si trova la
    scimmia è collegato a un nodo della categoria considerata, o non
    presente in caso contrario. Risulta quindi che ci sono $4^2$
    configurazioni possibili nella visuale della scimmia. Per ogni nodo
    in cui si trova, la scimmia deve scegliere a quale delle precedenti
    categorie deve appartenere il nodo su cui si spesterà. Se sono
    presenti diversi nodi appartenenti alla categoria scelta lo
    spostamento avviene in modo casuale tra questi.

    La strategia che ci aspettiamo segua una scimmia evoluta è di
    evitare di spostarsi su una categoria di nodi non presente tra
    quelli raggiungibili, di tendere a spostarsi sempre su nodi
    superiori mai visitati e nel caso il percorso intrapreso sia un
    vicolo cieco (non siano presenti nodi più in alto), si sposti in
    basso e intraprenda una strada alternativa (di nodi mai visitati).

-   La creazione dell’algoritmo genetico: questo implica dotare le
    scimmia di un dna (che codifica la sua strategia), ovvero una
    funzione che specifica quale azione associare ad ogni possibile
    configurazione degli appigli, e di una funzione di fitness, che
    calcola la “bravura” della scimmia nello scalare la parete.
    L’algoritmo genetico vero e proprio usa questi due parametri per far
    evolvere le scimmie ed è così strutturato: bisogna creare una prima
    generazione di scimmie dotate di strategie (dna) completamente
    casuali e usare la funzione di fitness per quantificare la bravura
    di tutte le scimmie della generazione. La generazione successiva
    sarà costituita da scimmie il cui dna è un incrocio tra i dna delle
    scimmie genitrici, con probabilità di far ereditare i propri geni
    proporzionale alla propria bravura. Ci sarà inoltre una bassa
    probabilità che alcune scimmie siano soggette a una mutazione
    casuale di un gene del loro dna.Si itera questo processo per un
    numero arbitrario di generazioni finchè la bravura delle scimmie non
    si stabilizza ad un punto di massimo: a questo punto è stat
    ottimizzata la strategia e presumibilmente le scimmie dell’ultima
    generazione sono capaci di arrivare in cima alla parete.

### Scimmia primititva sugli alberi

Inizialmente abbiamo scelto di far muovere la scimmia per un determinato
numero di passi attraverso un grafo ad albero, con un arbitrario numero
di livelli e di figli per ciascun nodo, abbastanza semplice da poter
essere attraversato anche con una visuale così ristretta. È stata scelta
una funzione di fitnness proporzionale alla somma delle altezze dei nodi
visitati (quindi quanti più nodi in alto visita la scimmia tanto più è
premiata) ma inversamente proporzionale al numero di nodi nella sua
memoria, in modo tale che quelle arrivate in cima, avendo meno nodi in
memoria, venivano premiate. È stato inoltre necessario prevenire la
possibilità che una scimmia facesse lo stesso movimento in loop (per
esempio cercare di spostarsi su un nodo che non esiste, rimanendo quindi
ferma) punendola nel caso lo facesse.

Il risultato è consistente con l’aspettativa: dopo meno di 100
generazioni la strategia delle scimmie si evolve in modo tale da farle
arrivare, prima o poi, in cima. In particolare la scimmia esplora i nodi
dell’albero con una ricerca depth first, quindi tendendo a spostarsi
subito verso i nodi piú alti e nel caso si trovi davanti a un vicolo
cieco ritorna indietro ed esplora altre strade.

La pecca del modello utilizzato per queste scimmie primitive è che il
percorso della scimmia è in buona parte affidato al caso, essendo
casuale su quale dei nodi appartenenti alla categoria scelta la scimmia
si muove. Quindi una stessa scimmia può impiegare un numero diverso di
passi ad arrivare alla cima.

### Scimmia primitiva sulle pareti

Questa pecca emerge non appena si prova a far muovere la scimmia su un
grafo più complesso e più somigliante a una parete reale. Abbiamo
generato questo tipo di grafo in questo modo: viene generata una
distribuzione casuale di punti su un piano, che ha come parametri
impostabili densità dei punti, altitudine minima della cima (nodo con
coordinata y maggiore), à di appiglio e probabilità di appoggio. Tramite
particolari accorgimenti è garantita la traversabilità della parete così
generata.

La scimmia che era capace di attraversare l’albero è solo in parte
capace di attraversare la parete: se la parete ha uno sviluppo
soprattutto verticale allora la scimmia è capace di attraversarla
praticamente sempre, se invece la parete presenta strettoie e si
sviluppa in orizzontale invece la scimmia più brava solo alcune volte
arriva in cima: dipende dalla scelta casuale che fa dei nodi. Capita
infatti più o meno la metà delle volte che vada in loop ai piedi della
parete non trovando la direzione giusta da imboccare per sorpassare una
strettoia.

Per far evolvere la scimmia sulle pareti sono state usate due diverse
funzioni di fit, verificando quale fosse la migliore : quella usata
anche per gli alberi ed un’altra, inversamente proporzionale al minimo
numero di passi necessari per arrivare alla cima. Rsiulta che le scimmie
che si sono evolute con la funzione di fit precedentemente usata hanno
una strategia identica a quella che ci aspettiamo, quelle evolute con la
seconda funzione arrivano in cima con la stessa probabilità rispetto
alle prime ma presentano una strategia leggermente diversa. Questo può
essere determinato da una maggiore specializzazione della scimmia
evoluta col secondo fit nei confronti della parete che si trova davanti.

Buoni propositi
---------------

-   Ampliare la visuale della scimmia, le possibilità sono:

    -   fare vedere alla scimmia anche a quale categoria appartengono i
        nodi raggiungibili in due passi;

    -   far vedere alla scimmia quante volte ha visitato un nodo per
        evitare il loop;

    -   dare una memoria geografica alla scimmia: sa quali nodi ha
        visitato e dove sono posizionati;

    -   indicare la direzione in cui si deve muovere con un vettore dato
        dalla combinazione lineare dei vettori che puntano ai nodi
        collegati con opportuni coefficienti dati dal dna;

-   implementare un’eventuale collaborazione tra scimmie: le scimmie
    possono raggiungere nodi che distano due collegamenti dal loro se in
    quei nodi sono presenti altre scimmie che le aiutano;

-   analisi dati.


