import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import animazione 1.0

Item {
    id: item1
    width: 1200
    height: 600
    property alias text1: text1
    property alias parete: parete
    property alias individui: individui
    property alias passi: passi
    property alias pcross: pcross
    property alias pmuta: pmuta
    property alias button2: button2
    property alias button1: button1
    property alias comboBox: comboBox
    property alias animaz: animaz
    property alias busyIndicator: busyIndicator

    RowLayout {
        id: rowLayout
        x: 0
        y: 8
        width: 863
        height: 40
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
        x: 869
        y: 0
        width: 314
        height: 207
        anchors.right: parent.right
        anchors.rightMargin: 17
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
    }

    Animazione {
        id: animaz
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 6
        anchors.topMargin: 6
        anchors.right: columnLayout.left
        anchors.left: parent.left
        anchors.leftMargin: 3
        anchors.rightMargin: 3
    }

    BusyIndicator {
        id: busyIndicator
        anchors.horizontalCenter: animaz.horizontalCenter
        anchors.verticalCenter: animaz.verticalCenter
    }
}
