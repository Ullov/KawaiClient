import QtQuick 2.0

Rectangle {
    anchors.fill: parent
    Text {
        id: testText
    }
    Component.onCompleted: options.emitRootProgramPath()
    Connections {
        target: options
        onSendRootProgramPath: testText.text = path
    }
}
