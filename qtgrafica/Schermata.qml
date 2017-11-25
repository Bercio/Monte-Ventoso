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
        evoluzione.set_runable()
    }
    parete.onClicked: {
        evoluzione.change_parete()
        animaz.paths = evoluzione.get_paths_parete();
        evoluzione.set_runable()
    }
    passi.onValueChanged:{
        evoluzione.passi = passi.value
        evoluzione.set_runable()
    }
    individui.onValueChanged:{
        evoluzione.individui = individui.value
        evoluzione.set_runable()
    }
    pcross.onValueChanged: evoluzione.pcross = pcross.value
    pmuta.onValueChanged: evoluzione.pmuta=pmuta.value
    text1.text: "fit: " + evoluzione.fit
    busyIndicator.running: evoluzione.running
    animaz.onMemChanged: aniMem.start()
    animaz.onMem_indexChanged: animaz.update()
    animaz.onPathsChanged: animaz.update()
    PropertyAnimation {id: aniMem; target: animaz; property: "mem_index";from: 0; to: animaz.end; duration: durata.value }
}

