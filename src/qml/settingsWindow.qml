import QtQuick 2.0
import QtQuick.Controls 2.2
import "qrc:/QmlIncludes/qml/QmlIncludes" as QmlIncludes

Rectangle {
    id: rootRect
    anchors.fill: parent

    QmlIncludes.KawaiButton {
        id: refreshButton
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: 5
        labelText: "Refresh"
        onClicked: options.emitRootProgramPath()
    }
    QmlIncludes.KawaiButton {
        id: setButton
        anchors.top: parent.top
        anchors.left: refreshButton.right
        anchors.margins: 5
        labelText: "Set"
        onClicked: options.setRootProgramPath(rootProgramPathTextFied.text)
    }

    TextField {
        id: rootProgramPathTextFied
        anchors.top: refreshButton.bottom
        anchors.left: parent.left
        anchors.margins: 5
        width: parent.width / 1.2
        placeholderText: "Input rootProgramPath"
    }

    Connections {
        target: options
        onSendRootProgramPath: {
            rootProgramPathTextFied.text = path
        }
    }
}
