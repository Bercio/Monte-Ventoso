import QtQuick 2.4

SchermataForm{
    //verifica se evoluzione.runable e' true quando evo e' runnable.
    button2.checkable: evoluzione.runable
    button2.onCheckedChanged: {
        if (button2.checked)
            evoluzione.start_evo()
        else
            evoluzione.stop_evo()
            evoluzione.get_best_dna()
    }
    button3.onClicked: {
            evoluzione.animate()
            aniMem.restart()
    }
    log.checkable: evoluzione.runable
    log.onCheckedChanged: {
        if (log.checked)
           evoluzione.log_evo(filename.text)
    }

    salva.onClicked: {
        evoluzione.write(filename.text)
    }
    leggip.onClicked: {
        evoluzione.read_parete(filename.text)
    }
    leggis.onClicked: {
        evoluzione.read_scimmia(filename.text)
    }
    comboBox.model: ["Rita", "Lorenzo"]
    comboBox.onCurrentIndexChanged: evoluzione.f_index = currentIndex;
    button1.onClicked: {
        evoluzione.change_gen()
        evoluzione._set_runable()
    }
    parete.onClicked: {
        evoluzione.change_parete()

        evoluzione._set_runable()
    }
    label.text: "individui: " + evoluzione.individui.toString()
    label1.text: "passi: " + evoluzione.passi.toString()
    label2.text: "pcross: " + evoluzione.pcross.toString()
    label3.text: "pmuta: " + evoluzione.pmuta.toString()
    passi.onValueChanged:{
        evoluzione.passi = passi.value
        evoluzione._set_runable()
    }
    individui.onValueChanged:{
        evoluzione.individui = individui.value
        evoluzione._set_runable()
    }
    pcross.onValueChanged: evoluzione.pcross = pcross.value
    pmuta.onValueChanged: evoluzione.pmuta=pmuta.value
    text1.text: "fit"
    busyIndicator.running: evoluzione.running
    animaz.onMem_indexChanged: animaz.update()
    animaz.onPathsChanged: {
        animaz.end_point = evoluzione.get_max_coor()
        animaz.clear_mem()
        animaz.update()
    }
    animaz.paths: evoluzione.paths
    animaz.onMemChanged: animaz.get_end()
    animaz.onEndChanged: {
    animaz.update()
    aniMem.target = animaz;
    aniMem.property = "mem_index";
    aniMem.to = animaz.end;
    aniMem.duration = (aniMem.to+1)*500;
    }

    Connections {
        target: evoluzione
        onFitChanged: {
            grafo1.axisX.max = evoluzione.evolutions * 1.3;
            grafo1.append(evoluzione.evolutions, evoluzione.fit)
            text1.text = "fit: " + evoluzione.fit.toLocaleString(Qt.locale("it_IT"),'f',5)
        }
        onRunableChanged: {
            if (evoluzione.running && !evoluzione.runable) {
                evoluzione.stop_evo()
                button2.checked = evoluzione.running
            }
        }
        onMemChanged: animaz.mem = mem
        onDnaChanged: {
            animaz.clear_mem()
            aniMem.complete()
            dnas.setDna(dna)
        }
        onPathsChanged: animaz.paths = paths
        onRunningChanged: {
            if(log.checked) log.checked = false;
        }
    }
    dnas.onModelReset:{
        dnalista.model = dnas
    }
    PropertyAnimation {
        from: 0;
        id: aniMem; }
    dnalista.delegate:
        Text{
            text: display
    }
}

