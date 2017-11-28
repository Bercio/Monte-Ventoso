import QtQuick 2.4

SchermataForm{
    //verifica se evoluzione.runable e' true quando evo e' runnable.
    button2.checkable: true
    button2.onCheckedChanged: {
        if (button2.checked)
            evoluzione.start_evo()
        else
            evoluzione.stop_evo()
            animaz.mem = evoluzione.get_best_mem()
    }
    comboBox.model: ["Rita", "Lorenzo"]
    comboBox.onCurrentIndexChanged: evoluzione.f_index = comboBox.currentIndex;
    button1.onClicked: {
        evoluzione.change_gen()
        evoluzione._set_runable()
    }
    parete.onClicked: {
        evoluzione.change_parete()
        animaz.paths = evoluzione.get_paths_parete();
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
    animaz.onMemChanged: aniMem.start()
    animaz.onMem_indexChanged: animaz.update()
    animaz.onPathsChanged: {
        animaz.end_point = evoluzione.get_max_coor()
        animaz.update()
    }
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

    PropertyAnimation {id: aniMem; target: animaz; property: "mem_index";from: 0; to: animaz.end; duration: animaz.end*500 }
}

