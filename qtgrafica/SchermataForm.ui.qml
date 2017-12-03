import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Window 2.2
import QtCharts 2.2
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
    property alias label: label
    property alias label1: label1
    property alias label2: label2
    property alias label3: label3

    property alias button2: button2
    property alias button1: button1
    property alias comboBox: comboBox
    property alias animaz: animaz
    property alias busyIndicator: busyIndicator
    property alias grafo1: grafo1

    RowLayout {
        id: rowLayout
        anchors.right: columnLayout.left
        anchors.rightMargin: 6
        anchors.leftMargin: 0
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.topMargin: 0

        Button {
            id: button2
            text: qsTr("Running")
            checkable: false
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
            text: qsTr("Text")
            fontSizeMode: Text.Fit
            font.pixelSize: 12
        }
    }

    ColumnLayout {
        id: columnLayout
        width: 300
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.topMargin: 0
        anchors.top: parent.top
        z: 1
        Layout.fillHeight: false

        Slider {
            id: pmuta
            width: parent.width
            value: 0.5

            Label {
                id: label3
                x: -136
                y: 65
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
}
