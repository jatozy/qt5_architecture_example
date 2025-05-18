import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: root
    property var device: null

    color: "#c2bebe"             // Lighter grey background
    border.color: "#b0acad"      // Matching light grey border
    border.width: 2
    radius: 6

    width: ListView.view ? ListView.view.width : 300
    implicitHeight: contentContainer.implicitHeight + header.implicitHeight + 30

    Column {
        id: contentContainer
        anchors {
            left: parent.left
            right: parent.right
            margins: 10
            top: header.bottom
            bottom: parent.bottom
            bottomMargin: 10
        }
        spacing: 10

        Row {
            spacing: 10
            width: parent.width
            height: 30

            Text {
                id: gainText
                text: "Gain: " + device.gain.toFixed(2)
                font.pointSize: 10
                color: "black"
                verticalAlignment: Text.AlignVCenter
                anchors.verticalCenter: parent.verticalCenter
            }

            RoundButton {
                id: muteButton
                height: gainText.height * 2
                width: 80
                radius: 12
                onClicked: {
                    eventHandler.toggleMuteAmp(device.id)
                } 
                anchors.verticalCenter: parent.verticalCenter

                contentItem: RowLayout {
                    anchors.fill: parent
                    anchors.margins: 4
                    spacing: 6

                    Rectangle {
                        width: 10
                        height: 10
                        radius: 5
                        color: device.mute ? "red" : "black"
                        Layout.alignment: Qt.AlignVCenter
                    }

                    Text {
                        text: device.mute ? "Unmute" : "Mute"
                        color: "black"
                        font.pointSize: 8
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        Layout.alignment: Qt.AlignVCenter
                    }
                }
            }
        }

        Slider {
            from: 0.0
            to: 2.0
            wheelEnabled: true
            value: device.gain
            onValueChanged: {
                eventHandler.setGainAmp(device.id, value)
            }
            width: parent.width * 0.9
        }

        Rectangle {
            width: parent.width * 0.9
            height: 20
            color: "black"
            border.color: "white"

            Rectangle {
                width: parent.width * device.inputLevel / 2
                height: parent.height
                color: "green"
            }
        }

        Rectangle {
            width: parent.width * 0.9
            height: 20
            color: "black"
            border.color: "white"

            Rectangle {
                width: parent.width * device.outputLevel / 2
                height: parent.height
                color: "blue"
            }
        }
    }

    Text {
        id: header
        text: "D10 " + device.id
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 10
        font.pointSize: 14
        font.bold: true
        color: "black"
    }
}
