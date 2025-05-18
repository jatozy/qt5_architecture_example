import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    visible: true
    width: 400
    height: 600
    title: "Audio Mixer"

    ToolBar {
        ColumnLayout {
            anchors.fill: parent
            spacing: 4
            anchors.margins: 10

            RowLayout {
                spacing: 10
                Layout.fillWidth: true

                ToolButton {
                    text: "Mute All"
                    onClicked: eventHandler.muteAllAmps()
                }
                ToolButton {
                    text: "Unmute All"
                    onClicked: eventHandler.unmuteAllAmps()
                }
                ToolButton {
                    text: "Add Amp"
                    onClicked: eventHandler.addAmp()
                }
                ToolButton {
                    text: "Save"
                    onClicked: eventHandler.save()
                }
                ToolButton {
                    text: "Undo"
                    onClicked: {
                        eventHandler.undo()
                    }
                }
                ToolButton {
                    text: "Redo"
                    onClicked: {
                        eventHandler.undo()
                    }
                }
            }
            ComboBox {
                model: applicationState.commandNames
                textRole: "name"
            }
        }
    }

    ListView {
        anchors.fill: parent
        anchors.topMargin: 100  // Leave space for the toolbar
        model: applicationState.ampsD10
        spacing: 12
        delegate: AmpD10 {
            device: model.device
        }
    }
}
