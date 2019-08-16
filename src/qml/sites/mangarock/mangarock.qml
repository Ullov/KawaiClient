import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4


Rectangle {
    Connections {
        target: apiHandler
        onDownloadingFinished: {
            statusLabel.text = "Downloading finished."
            buttonOninputUserId.enabled = true
            viewButton.enabled = true
        }
    }
    Connections {
        target: apiHandler
        onDownloadingStarted: statusLabel.text = "In proggres..."
    }

    anchors.fill: parent
    color: "Black"
    Rectangle {
        id: userIdInputBar
        width: parent.width
        height: 30
        TextField {
            background: Rectangle {
                radius: 4
                implicitWidth: 150
                implicitHeight: userIdInputBar.height
                border.color: "#333"
                border.width: 1
            }
            id: userId
            placeholderText: qsTr("Enter user id...")
        }
        Button {
            id: buttonOninputUserId
            x: userId.width + 10
            height: parent.height
            width: 100
            text: qsTr("Download")
            onClicked: {
                apiHandler.startPixivDownloading(userId.text)
                buttonOninputUserId.enabled = false
                viewButton.enabled = false
            }
        }
        Button {
            id: viewButton
            anchors.left: buttonOninputUserId.right
            height: parent.height
            width: 100
            text: qsTr("View")
            onClicked: {
                apiHandler.viewPixivUser(userId.text)
                buttonOninputUserId.enabled = false
                viewButton.enabled = false
            }
        }

        Label {
            id: statusLabel
            text: qsTr("Waiting")
            anchors.left: viewButton.right
        }
    }

    Rectangle {
        anchors.top: userIdInputBar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        color: "Gray"
    }
}
