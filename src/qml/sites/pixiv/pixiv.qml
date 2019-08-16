import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4


Rectangle {
    Connections {
        target: apiHandler
        onPixivDownloadingFinished: {
            statusLabel.text = "Downloading finished."
            buttonOninputUserId.enabled = true
            viewButton.enabled = true
        }
    }
    Connections {
        target: apiHandler
        onPixivDownloadingStarted: statusLabel.text = "In proggres..."
    }
    Connections {
        target: apiHandler
        onPixivViewDataDownloaded: {
            statusLabel.text = "Downloading finished."
            buttonOninputUserId.enabled = true
            viewButton.enabled = true
            statusLabel.text = userData["body"]["name"].toString()
            testImage.source = "image://myImageProvider/" + imagesFromApi[0]
        }
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
                apiHandler.pixivStartDownloading(userId.text)
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
                apiHandler.pixivViewUser(userId.text)
                buttonOninputUserId.enabled = false
                viewButton.enabled = false
            }
        }

        Label {
            id: statusLabel
            text: qsTr("Waiting")
            anchors.left: viewButton.right
        }
        Image {
            id: testImage
            source: "qrc:/resources/icons/apple-touch-icon(pixiv).png"
            anchors.right: parent.right
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
