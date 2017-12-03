import QtQuick 2.7

SchermataForm{

    button2.checkable: evoluzione.runable
    button2.onCheckedChanged: {
        if (button2.checked)
            evoluzione.start_evo()
        else
            evoluzione.stop_evo()
            evoluzione.get_best_dna()
            evoluzione.get_best_mem()
    }
    button3.checkable: animaz.end > 0
    button3.onClicked:{
            evoluzione.animate
            aniMem.restart()
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
    text1.text: "fit: " + evoluzione.fit.toLocaleString()
    busyIndicator.running: evoluzione.running
    animaz.onMem_indexChanged: animaz.update()
    animaz.onPathsChanged: {
        animaz.end_point = evoluzione.get_max_coor()
        aniMem.complete()
        animaz.update()
    }
    animaz.mem: evoluzione.mem
    animaz.onMemChanged: animaz.get_end()
    animaz.paths: evoluzione.paths
    Connections {
        target: evoluzione
        onDnaChanged: dnas.setDna(dna)
    }
    //todo bind dnas change to evoluzione
    //dnas.onDataChanged: evoluzione.change_dna(index)

    Connections {
        target: evoluzione
        onFitChanged: {
            grafo1.axisX.max = evoluzione.evolutions * 1.3;
            grafo1.append(evoluzione.evolutions, evoluzione.fit)
        }
    }
    Connections {
        target: evoluzione
        onRunableChanged: {
            if (evoluzione.running && !evoluzione.runable) {
                evoluzione.stop_evo()
                button2.checked = evoluzione.running
            }
        }
    }
    dnas.onModelReset:{
        dnalista.model = dnas
    }
    dnas.onDataChanged: {evoluzione.change_dna(top,bottom)}
    PropertyAnimation {id: aniMem; target: animaz; property: "mem_index";from: 0; to: animaz.end; duration: animaz.end*500 }
    dnalista.delegate:
        TextInput {
            text: display
            validator: IntValidator{ bottom: 0; top: 3}
            onActiveFocusChanged: {
                if(activeFocus)
                    text = edit
                else
                    text = display
            }
                onEditingFinished: model.edit = text}
}

