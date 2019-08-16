import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle {
    id: downloadBarRoot
    width: parent.width
    property int gridItemWidth: 400
    Grid {
        id: firstDownloadBarLine
        width: parent.width
        columns: 4
        spacing: 10
        y: 2

        Rectangle {
            id: pixivDownloadRectangle

            Connections {
                target: apiHandler
                onPixivDownloadingFinished: {
                    pixivStatusRectangle.color = "#00ff08"
                    //buttonOninputUserId.enabled = true
                    //viewButton.enabled = true
                }
            }
            Connections {
                target: apiHandler
                onPixivDownloadingStarted: pixivStatusRectangle.color = "#ff0000"
            }
            Connections {
                target: apiHandler
                onPixivViewDataDownloaded: {
                    pixivStatusRectangle.color = "#00ff08"
                    //buttonOninputUserId.enabled = true
                    //viewButton.enabled = true
                    //statusLabel.text = userData["body"]["name"].toString()
                    //testImage.source = "image://myImageProvider/" + imagesFromApi[0]
                }
            }

            width: gridItemWidth
            height: 40
            color: "#292225"
            radius: 6
            Label {
                id: pixivDownloadTitleLabel
                anchors.verticalCenter: parent.verticalCenter
                x: 5
                text: "Pixiv"
                color: "White"
                font.pixelSize: 14
            }

            TextField {
                id: pixivTextField
                anchors.left: pixivDownloadTitleLabel.right
                anchors.leftMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                height: parent.height - 5
                placeholderText: "Enter user ID..."
            }

            KawaiButton {
                id: pixivStartDownloadButton
                height: parent.height - 5
                anchors.left: pixivTextField.right
                anchors.leftMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                labelText: "Start download"
                MouseArea {
                    anchors.fill: parent
                    onClicked: apiHandler.pixivStartDownloading(pixivTextField.text)
                }
            }

            Rectangle {
                id: pixivStatusRectangle
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: pixivStartDownloadButton.right
                anchors.leftMargin: 10
                color: "#00ff08"
                height: 20
                width: 20
            }
        }

        Rectangle {
            id: mangaeockDownloadRectangle

            Connections {
                target: apiHandler
                onMangarockDownloadingFinished: {
                    statusLabel.text = "Downloading finished."
                    buttonOninputUserId.enabled = true
                    viewButton.enabled = true
                }
            }
            Connections {
                target: apiHandler
                onMangarockDownloadingStarted: statusLabel.text = "In proggres..."
            }

            width: gridItemWidth
            height: 40
            color: "#292225"
            radius: 6
            Label {
                id: mangaeockDownloadTitleLabel
                anchors.verticalCenter: parent.verticalCenter
                x: 5
                text: "MangaRock"
                color: "White"
                font.pixelSize: 14
            }

            TextField {
                id: mangaeockTextField
                anchors.left: mangaeockDownloadTitleLabel.right
                anchors.leftMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                height: parent.height - 5
                placeholderText: "Enter user ID..."
            }

            KawaiButton {
                id: mangaeockStartDownloadButton
                height: parent.height - 5
                anchors.left: mangaeockTextField.right
                anchors.leftMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                labelText: "Start download"
            }
        }
    }

}
