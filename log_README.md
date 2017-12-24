# log dal terminale

per salvare dati senza usare la grafica puoi far andare logEvol o da CLion (e' uno dei possibili target, ed ha come argomenti di default 100000 evol e 10000 evol per pareti che puoi cambiare clickando su edit configurations dal menu dei target) oppure dal terminale: per compilarlo dalla cartella del progetto digita "make logEvol" e per farlo andare "./logEvol n_evol n_evol_per_pareti" dove n_evol e n_evol per pareti sono numeri interi. 

#log da grafica

dalla grafica di qt (che puoi fare andare con "cd qtgrafica; ./qtgrafica" dal terminale e puoi rebuildare con "cd qtgrafica; make") puoi, una volta modificate le variabili come ti aggrada e inserito nel campo filename il nome del file in cui vuoi salvare i risultati, far andare 1000 evoluzioni e registrare il risultato finale clickando sul bottone "log". se vuoi visualizzare il comportamento della scimmia finale clicca "animate", se vuoi visualizzare il comportamento di qualsiasi altra scimmia salvata in simulazioni precedenti sulla parete attualmente caricata immetti nel campo filename il nome del file in cui hai salvato la suddetta scimmia e clicca "carica scimmia" e "animate" (N.B.: il campo "fit:" ti mostrera' il fit registrato nella precedente simulazione dopo aver cliccato su "carica scimmia", mentre ti mostrera' il fit ottenuto traversando l'attuale parete dopo aver cliccato su "animate"). Per caricare la parete che la suddetta scimmia ha attraversato nella simulazione precedente clicca "carica parete", e per caricare qualsiasi altra parete salvata in una simulazione precedente inserisci in "filename" il nome del file su cui sono stati salvati i risultati e clicca "carica parete". 

#dove trovare i risultati

I Risultati sono sempre salvati nella cartella /data, nella forma:  nome del file scelto.json se salvati dalla grafica, oppure millisecondi trascorsi dal 1/1/1970 al momento della simulazione + "_" + numero di evoluzioni trascorse dall'inizio della simulazione + L se il fit e' sotto la media, W se e' sopra la media + ".json" . per caricare i file in qt scrivi il nome del file senza estensione (es: per caricare il file /data/scimma.json scrivere in "filename" "scimmia")

