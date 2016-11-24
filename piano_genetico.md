# ALGORITMO GENETICO

## Obiettivo

creo 50 individui ragnetti dotati di un dna[1] che rappresenta le loro azioni
davanti ad una certa situazione. Il dna inizialmente è casuale, poi dovrò far
evolvere la popolazione di generazione in generazione selezionando di volta in
volta i ragnetti che si comportano meglio.

Devo quindi creare:

- [x] una classe individuo che contiene il dna e il parametro di fitness, che indica la bravura dell'individuo che considero.

- [x] la funzione di fitness che assegna il parametro in base a quanto vicino alla cima è arrivato l'individuo nel grafo.

- [ ] un'array di individui che rappresenta la popolazione.

- [ ] la funzione cross over che crea il dna di un nuovo individuo unendo due parti del dna di due genitori bravi.

- [ ] la funzione mutazione che introduce una mutazione casuale di un gene del dna.

- [ ] la funzione che effettua il cambio di generazione.

- [ ] una funzione che dà la vista al ragnetto e che converte quello che vede in un
array (o scalare) che individua una configurazione. Di conseguenza occorre
anche aggiornare una lista dei nodi in cui è stato e di volta in volta
confrontare se i nodi che vede sono o meno nella lista.

- [ ] una funzione che faccia avanzare la posizione del ragnetto in un nodo che
  soddisfa la sua scelta (determinata dal dna), con eventualmente una
  componente casuale-> può trovarsi davanti diversi nodi che appartengono alla
  stessa classe e su cui può eventualmente spostarsi ma il dna non gli dice su
  quale di questi andare.

Il dna è un array di interi che vanno da 0 a 3. Ogni intero individua
un'azione che compie il ragno (quindi può compiere 4 azioni). Il ragno decide
quale azione compiere(==associa univocamente un'azione) in base a cosa vede
attorno a sè (chiamo la sua visuale "configurazione"): distinguere solo se ci
sono figli e/o genitori del nodo in cui si trova e se questi sono stati
visitati o meno. Quindi deve controllare la presenza o meno di: nodi figli già
visitati, nodi figli non visitati, nodi genitori visitati, nodi genitori non
visitati. Quindi il ragnetto può trovarsi davanti nodi appartenenti a 4 classi
diverse, ciascuna classe può trovarsi in due diversi stati: 1=presente; 0=non
presente. Una configurazione può essere quindi rappresentata da un array di 4
interi che possono variare tra 0 e 1. Ci sono di conseguenza 16 configurazioni
possibili.

Ciò implica che io debba costruire una matrice (abbiamo poi detto che le righe
saranno degli scalari invece che degli array da 4 elementi per il fatto che può
essere interpretato come codice binario) e associare ad ogni riga un'azione del
ragno. Quindi il dna del ragno sarà costituito da una sequenza di 16 elementi,
ciascuno dei quali rappresenta l'azione di risposta alla configurazione che il
ragnetto vede. Le azioni di risposta possibili sono 4: 0: vai su un figlio
ignoto, 1:vai su un figlio noto, 2: vai su un genitore ignoto, 3: vai su un
genitore noto.

NB!!! praticamente tutte le configurazioni hanno azioni di risposta non
permesse, per esempio se non esiste il figlio ignoto non può compiere l'azione
0-> bisogna porre delle limitazioni all'assegnazione dell'azione ad una
configurazione. (Oppure lasciargli fallire le azioni e sperare che non lo
faccia piu' man mano che si evolve


Non mi sono ancora addentrata nello specifico nelle funzioni di cross over ecc
perchè non so ancora impostare il resto. 
PS secondo me alla fine ho posto il problema in modo talmente semplice che
converge dopo tipo 10 generazioni, però partirei da qui per poi complicarla,
magari fornendogli una visuale diversa.

