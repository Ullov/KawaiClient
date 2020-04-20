import QtQuick 2.0
import "../../QmlIncludes"

Rectangle {
    anchors.fill: parent

    Component.onCompleted:{
        options.emitRootProgramPath()
        options.slotGetParam("/fsExplorer/lastOpenedDirectory")
    }
    Connections {
        target: options
        onSendRootProgramPath: rootProgtramPathField.klifcTextField.text = path
        onSignalParam: testParamField.klifcLabel.text = param
    }

    KawaiLabelInputFieldCombination {
        id: rootProgtramPathField
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: 5
        width: 500
        klifcLabel.text: "Root program path"
    }

    KawaiLabelInputFieldCombination {
        id: testParamField
        anchors.top: rootProgtramPathField.bottom
        anchors.left: parent.left
        anchors.margins: 5
        width: 500
        klifcLabel.text: ""
    }
}
