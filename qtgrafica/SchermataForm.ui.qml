import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Window 2.2
import QtCharts 2.2
import dnas 1.0
import animazione 1.0

Item {
    id: item1
    visible: true
    width: 1200
    height: 600
    property alias text1: text1
    property alias parete: parete
    property alias individui: individui
    property alias passi: passi
    property alias pcross: pcross
    property alias pmuta: pmuta
    property alias button2: button2
    property alias button3: button3
    property alias button1: button1
    property alias comboBox: comboBox
    property alias animaz: animaz
    property alias busyIndicator: busyIndicator
    property alias grafo1: grafo1
    property alias dnalista: dnalista
    property alias dnas: dnas
    property alias filename: filename
    property alias salva: salva
    property alias leggip: leggip
    property alias leggis: leggis

    RowLayout {
        id: rowLayout
        anchors.right: columnLayout.left
        spacing:0
        Layout.maximumWidth: parent.width - columnLayout.width
        anchors.rightMargin: 6
        anchors.leftMargin: 0
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.topMargin: 0

        Button {
            id: button2
            text: qsTr("Running")
        }
        Button {
        id:button3
        text: qsTr("Animate")
        }

        Button {
            id: button1
            text: qsTr("New Pop")
        }

        
        Button {
            id: parete
            text: qsTr("New Parete")
        }
        ComboBox {
            id: comboBox
            currentIndex: 0
        }

        Text {
            id: text1
        }
        Button {
            id: leggip
            text: "carica parete"
        }
        Button {
            id: leggis
            text: "carica scimmia"
            }
        Button{
            id: salva
            text: "salva p+s"
            Layout.minimumWidth: 2
            }

        TextField {
            id: filename
            placeholderText:  "filename:"
            implicitWidth: 100
            }
    }

    ColumnLayout {
        id: columnLayout
        width: 200
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        z: 1

        Slider {
            id: pmuta
            width: parent.width
            value: 0.5

            Label {
                id: label3
                x: -136
                y: 65
                text: qsTr("pmuta")
                anchors.bottomMargin: -9
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }

        Slider {
            id: pcross
            width: parent.width
            value: 0.5

            Label {
                id: label2
                x: -136
                y: 65
                text: qsTr("pcross")
                anchors.bottomMargin: -9
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }

        Slider {
            id: passi
            width: parent.width
            stepSize: 1
            from: 0
            to: 2000
            value: 500

            Label {
                id: label1
                x: -136
                y: 65
                text: qsTr("passi")
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WordWrap
                anchors.bottomMargin: -9
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }

        Slider {
            id: individui
            width: parent.width
            stepSize: 1
            to: 1000
            value: 100

            Label {
                id: label
                text: qsTr("individui")
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: -9
            }
        }
        ChartView {
            width: parent.width
            height: 300
            title: "andamento del fit"
            legend.visible: false
            axes: [
                ValueAxis {
                    id: xAxis
                    minorGridVisible: false
                    labelsVisible: true
                    titleVisible: false
                    visible:true
                    min: 0
                    max: 1000
                    tickCount: 2
                },
                ValueAxis {
                    id: yAxis
                    minorGridVisible: false
                    labelsVisible: true
                    tickCount: 2
                    titleVisible: false
                    visible: true
                    min: 0
                    max: 1
                }
            ]
            LineSeries {
                id: grafo1
                axisX: xAxis
                axisY: yAxis
            }
        }
        ListView {
            id: dnalista
            Layout.fillHeight: true
        }
    }

    Item {
        id: parAnim
        z: 2
        anchors.top: rowLayout.bottom
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.topMargin: 10
        anchors.right: columnLayout.left
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        Animazione{
            id: animaz
            anchors.fill: parent
        }
    }

    BusyIndicator {
        id: busyIndicator
        anchors.horizontalCenter: parAnim.horizontalCenter
        anchors.verticalCenter: parAnim.verticalCenter
    }
    Dnas {
        id: dnas
    }
}
