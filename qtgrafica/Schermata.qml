import QtQuick 2.4

SchermataForm{
    //verifica se evoluzione.runable e' true quando evo e' runnable.
    button2.checkable: true
    button2.onCheckedChanged: {
        if (button2.checked)
            evoluzione.start_evo()
        else
            evoluzione.stop_evo()
    }
    comboBox.model: ["Rita", "Lorenzo"]
    comboBox.onCurrentIndexChanged: evoluzione.f_index = comboBox.currentIndex;
    button1.onClicked: {
        evoluzione.change_gen()
        evoluzione.set_runable()
    }
    parete.onClicked: {
        evoluzione.change_parete()
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
    text1.text: evoluzione.fit
    busyIndicator.running: evoluzione.running
}

