import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle {
    id: downloadBarRoot
    width: parent.width
    property int gridItemWidth: 450
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
                onUniversalDownloadingFinished: {
                    if (mode[0] == "pixiv")
                    {
                        pixivStatusRectangle.color = "#00ff08"
                        //buttonOninputUserId.enabled = true
                        //viewButton.enabled = true
                    }
                }
            }
            Connections {
                target: apiHandler
                onUniversalDownloadingStarted: {
                    if (mode[0] == "pixiv")
                        pixivStatusRectangle.color = "#ff0000"
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
                heightC: parent.height - 5
                labelText: "Download"
                anchors.left: pixivTextField.right
                anchors.leftMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    var param = [pixivTextField.text]
                    var mode = ["pixiv"]
                    apiHandler.universalStartDownloading(param, mode)
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
            id: mangarockDownloadRectangle
            Connections {
                target: apiHandler
                onUniversalDownloadingFinished: {
                    if (mode[0] == "mangarock")
                        mangarockStatusRectangle.color = "#00ff08"
                }
            }
            Connections {
                target: apiHandler
                onUniversalDownloadingStarted: {
                    if (mode[0] == "mangarock")
                        mangarockStatusRectangle.color = "#ff0000"
                }
            }
            width: gridItemWidth
            height: 40
            color: "#292225"
            radius: 6
            Label {
                id: mangarockDownloadTitleLabel
                anchors.verticalCenter: parent.verticalCenter
                x: 5
                text: "MangaRock"
                color: "White"
                font.pixelSize: 14
            }
            TextField {
                id: mangarockTextField
                anchors.left: mangarockDownloadTitleLabel.right
                anchors.leftMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                height: parent.height - 5
                placeholderText: "Enter user ID..."
            }
            KawaiButton {
                id: mangarockStartDownloadButton
                heightC: parent.height - 5
                labelText: "Download"
                anchors.left: mangarockTextField.right
                anchors.leftMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    var param = [mangarockTextField.text]
                    var mode = ["mangarock"]
                    apiHandler.universalStartDownloading(param, mode)
                }
            }
            Rectangle {
                id: mangarockStatusRectangle
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: mangarockStartDownloadButton.right
                anchors.leftMargin: 10
                color: "#00ff08"
                height: 20
                width: 20
            }
        }

        Rectangle {
            Connections {
                target: apiHandler
                onUniversalDownloadingFinished: {
                    if (mode[0] == "exhentai" && mode[1] == "void")
                        exhentaiStatusRectangle.color = "#00ff08"
                }
            }
            Connections {
                target: apiHandler
                onUniversalDownloadingStarted: {
                    if (mode[0] == "exhentai")
                        exhentaiStatusRectangle.color = "#ff0000"
                }
            }
            height: 40
            radius: 6
            width: gridItemWidth
            color: "#292225"
            Label {
                id: exhentaiLabel
                text: "ExHentai"
                anchors.verticalCenter: parent.verticalCenter
                color: "White"
                font.pixelSize: 14
                x: 5
            }
            TextField {
                id: galleryUrl
                anchors.left: exhentaiLabel.right
                anchors.margins: 5
                placeholderText: "Enter gallery URL..."
                anchors.verticalCenter: parent.verticalCenter
            }
            KawaiButton {
                id: exhentaiButton
                heightC: parent.height - 5
                labelText: "Download"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: galleryUrl.right
                anchors.margins: 5
                onClicked: {
                    var param = [galleryUrl.text]
                    var mode = ["exhentai", "download"]
                    apiHandler.universalStartDownloading(param, mode)
                }
            }

            Rectangle {
                id: exhentaiStatusRectangle
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: exhentaiButton.right
                anchors.margins: 5
                color: "#00ff08"
                height: 20
                width: 20
            }
        }
    }
}
