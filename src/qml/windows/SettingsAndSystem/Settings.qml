import QtQuick 2.0
import "../../QmlIncludes"

Rectangle {
    anchors.fill: parent

    Component.onCompleted: options.emitRootProgramPath()
    Connections {
        target: options
        onSendRootProgramPath: rootProgtramPathField.klifcTextField.text = path
    }

    KawaiLabelInputFieldCombination {
        id: rootProgtramPathField
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: 5
        width: 500
        klifcLabel.text: "Root program path"
    }
}
