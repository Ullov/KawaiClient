import QtQuick 2.0
import QtQuick.Controls 2.5
import "../../../QmlIncludes"

Rectangle {
    /*property var sirChildItems: {
        "titleLabel": titleLabel,
        "inputTextField": inputTextField,
        "statusTextBox": statusTextBox,
        "startDownloadButton": startDownloadButton,
        "statusRectangle": statusRectangle,
    }*/
    property alias sirTitleLabel: titleLabel
    property alias sirInputTextField: inputTextField
    property alias sirStatusTextBox: statusTextBox
    property alias sirStartDownloadButton: startDownloadButton
    property alias sirStatusRectangle: statusRectangle

    id: root
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.margins: 5
    height: 40
    color: "#292225"
    radius: 6
    Label {
        id: titleLabel
        anchors.verticalCenter: parent.verticalCenter
        width: 120
        text: name
        color: "White"
        font.pixelSize: 14
        x: 5
    }
    TextField {
        id: inputTextField
        anchors.left: titleLabel.right
        anchors.right: statusTextBox.left
        anchors.margins: 5
        anchors.verticalCenter: parent.verticalCenter
        height: 30
        placeholderText: placeholder
    }
    Text {
        id: statusTextBox
        anchors.right: startDownloadButton.left
        anchors.margins: 5
        anchors.verticalCenter: parent.verticalCenter
        width: 145
        font.pixelSize: 14
        color: "White"
        horizontalAlignment: Text.AlignRight
    }
    KawaiButton {
        id: startDownloadButton
        heightC: 30
        labelText: "Download"
        anchors.right: statusRectangle.left
        anchors.margins: 5
        anchors.verticalCenter: parent.verticalCenter
        onClicked: onClickFunctionList[functionType](inputTextField.text, parserType, parserMode)
    }
    Rectangle {
        id: statusRectangle
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.margins: 5
        color: "#00ff08"
        height: 20
        width: 20
    }
    Connections {
        target: apiHandler
        onSignalDownloadingStarted: {
            if (parserType === mode[0] && parserMode === mode[1])
                statusRectangle.color = "#ff0000"
        }
        onSignalDownloadingFinished: {
            if (parserType === mode[0] && parserMode === mode[1])
                statusRectangle.color = "#00ff08"
        }
    }
}
