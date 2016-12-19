import QtQuick 2.4

SchermataForm{
    button2.checkable: evoluzione.runable
    button2.onCheckedChanged: {
        if (button2.checked)
            evoluzione.start_evo()
        else
            evoluzione.stop_evo()
        condole.log("yoo")
    }
    comboBox.model: ["Rita", "Lorenzo"]
    comboBox.onCurrentIndexChanged: evoluzione.f_index = comboBox.currentIndex;
    button1.onClicked: evoluzione.change_gen()
    parete.onClicked: evoluzione.change_parete()
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

