import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle {
    Connections {
        target: logging
        onLogMessage: logTextArea.append(message)
    }

    id: log
    anchors.fill: parent
    color: "#000000"
    Rectangle {
        width: parent.width
        height: parent.height - 20
        color: "#000000"
        ScrollView {
            anchors.fill: parent
            TextArea {
                id: logTextArea
                anchors.fill: parent
                placeholderText: qsTr("Here will shows some logs...")
                color: "#0fe71f"
                readOnly: true
                font.pixelSize: 12
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.RightButton
        onClicked: {
            logContextMenu.x = mouse.x
            logContextMenu.y = mouse.y
            logContextMenu.open()
        }
    }

    Menu {
        id: logContextMenu
        MenuItem {
            text: "Clear log"
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    logTextArea.text = ""
                    logContextMenu.close()
                }
            }
        }
    }
}
