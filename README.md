# Ascesa al Monte Ventoso

Simulatore di arrampicanti selezionati attravero algoritmo genetico applicato 
all'esplorazione di alberi simulanti una parete. 

# Piano di marcia

- Generare alberi che simulino una parete traversabile
    - [x] generare alberi casuali
    - [ ] generare alberi che simulino una parete (**Lo**)
        - [x] più nodi possono avere lo stesso figlio solo se adiacenti 
          e se non vi sono altri figli in mezzo
        - [x] rendere direzionali i vertici 
            - [x] eliminare la generazione di nodi orfani rendendo l'algoritmo 
              ricorsivo 
        - [x] rappresentare grafici su stdout
        - [ ] assegnare un vettore bidimensionale ai vertici che rappresenti il 
          vettore distanza tra i nodi (**Lo**)
            - [ ] rappresentare le distanze reali nella rappresentazione 
              grafica
    - [x] verificare che un albero sia traversabile rispettando le costrizioni 
      della simulazione
        - [x] nodo viabile solo se connesso ad almeno due nodi
    - [ ] implementare ragnetto
    - [ ] modellare algorimo genetico (**Rita**)
        - [ ] una classe individuo che contiene il dna e il parametro di 
          fitness, che indica la bravura dell'individuo che considero.

        - [ ] la funzione di fitness che assegna il parametro in base a quanto vicino alla cima è arrivato l'individuo nel grafo.

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
    - [ ] implementare algoritmo genetico
    - [ ] modellare veste grafica
    - [ ] implementare veste grafica
    - [x] progettare meccanismo di collaborazione
    - [ ] implementare collaborazione


