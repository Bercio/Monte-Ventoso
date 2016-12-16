import QtQuick 2.4

SchermataForm{
    button2.onCheckedChanged: {
        evoluzione.setRunning(button2.checked)
        if (button2.checked)
            evoluzione.start_evo()
    }
    comboBox.onCurrentIndexChanged: evoluzione.choose_fitfunc(comboBox.currentIndex)
    button2.checkable: evoluzione.runable
    button1.onClicked: evoluzione.newgen()
    parete.onClicked: evoluzione.chage_parete()
    passi.onValueChanged: evoluzione.set_passi(passi.value)
    individui.onValueChanged: evoluzione.set_individui(individui.value)
    pcross.onValueChanged: evoluzione.set_pcross(pcross.value)
    pmuta.onValueChanged: evoluzione.set_pmuta(pmuta.value)
    textField: evoluzione.best_fit
    busyIndicator.running: evoluzione.running
}

