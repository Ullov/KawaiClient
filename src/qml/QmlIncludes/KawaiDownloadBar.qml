import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle {
    id: downloadBarRoot
    width: parent.width
    Grid {
        id: firstDownloadBarLine
        width: parent.width
        columns: 4
        spacing: 10
        y: 2

    }
    Rectangle {
        id: pixivDownloadRectangle
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 5
        height: 40
        color: "#292225"
        radius: 6
        Label {
            id: pixivDownloadTitleLabel
            anchors.verticalCenter: parent.verticalCenter
            width: 120
            text: "Pixiv"
            color: "White"
            font.pixelSize: 14
            x: 5
        }
        TextField {
            id: pixivTextField
            anchors.left: pixivDownloadTitleLabel.right
            anchors.right: pixivStartDownloadButton.left
            anchors.margins: 5
            anchors.verticalCenter: parent.verticalCenter
            height: 30
            placeholderText: "Enter user ID..."
        }
        KawaiButton {
            id: pixivStartDownloadButton
            heightC: 30
            labelText: "Download"
            anchors.right: pixivStatusRectangle.left
            anchors.margins: 5
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
            anchors.right: parent.right
            anchors.margins: 5
            color: "#00ff08"
            height: 20
            width: 20
        }
    }

    Rectangle {
        id: mangarockDownloadRectangle
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: pixivDownloadRectangle.bottom
        anchors.margins: 5
        height: 40
        color: "#292225"
        radius: 6
        Label {
            id: mangarockDownloadTitleLabel
            anchors.verticalCenter: parent.verticalCenter
            width: 120
            text: "MangaRock"
            color: "White"
            font.pixelSize: 14
            x: 5
        }
        TextField {
            id: mangarockTextField
            anchors.left: mangarockDownloadTitleLabel.right
            anchors.right: mangarockStartDownloadButton.left
            anchors.margins: 5
            anchors.verticalCenter: parent.verticalCenter
            height: 30
            placeholderText: "Enter manga OID..."
        }
        KawaiButton {
            id: mangarockStartDownloadButton
            heightC: 30
            labelText: "Download"
            anchors.right: mangarockStatusRectangle.left
            anchors.margins: 5
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
            anchors.right: parent.right
            anchors.margins: 5
            color: "#00ff08"
            height: 20
            width: 20
        }
    }

    Rectangle {
        id: exhentaiDownloadRectangle
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: mangarockDownloadRectangle.bottom
        anchors.margins: 5
        height: 40
        radius: 6
        color: "#292225"
        Label {
            id: exhentaiLabel
            text: "ExHentai"
            width: 120
            anchors.verticalCenter: parent.verticalCenter
            color: "White"
            font.pixelSize: 14
            x: 5
        }
        TextField {
            id: galleryUrl
            anchors.left: exhentaiLabel.right
            anchors.right: exhentaiButton.left
            anchors.margins: 5
            height: 30
            placeholderText: "Enter gallery URL..."
            anchors.verticalCenter: parent.verticalCenter
        }
        KawaiButton {
            id: exhentaiButton
            heightC: 30
            labelText: "Download"
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: exhentaiStatusRectangle.left
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
            anchors.right: parent.right
            anchors.margins: 5
            color: "#00ff08"
            height: 20
            width: 20
        }
    }

    Rectangle {
        id: mangadexDownloadRectangle
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: exhentaiDownloadRectangle.bottom
        anchors.margins: 5
        height: 40
        radius: 6
        color: "#292225"
        Label {
            id: mangadexLabel
            text: "MangaDex"
            width: 120
            anchors.verticalCenter: parent.verticalCenter
            color: "White"
            font.pixelSize: 14
            x: 5
        }
        TextField {
            id: mangadexMangaId
            anchors.left: mangadexLabel.right
            anchors.right: checkBoxesRectangle.left
            anchors.margins: 5
            height: 30
            placeholderText: "Enter manga ID..."
            anchors.verticalCenter: parent.verticalCenter
        }
        Rectangle {
            id: checkBoxesRectangle
            anchors.right: mangadexButton.left
            anchors.verticalCenter: parent.verticalCenter
            anchors.margins: 5
            height: 30
            width: 200
            CheckBox {
                id: enLangChekbox
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                text: "EN"
            }
            CheckBox {
                id: ruLangChekbox
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: enLangChekbox.right
                text: "RU"
            }
            CheckBox {
                id: otherLangChekbox
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: ruLangChekbox.right
                text: "Other"
            }
        }

        KawaiButton {
            id: mangadexButton
            heightC: 30
            labelText: "Download"
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: mangadexStatusRectangle.left
            anchors.margins: 5
            onClicked: {
                var param = [mangadexMangaId.text, enLangChekbox.checked, ruLangChekbox.checked, otherLangChekbox.checked]
                var mode = ["mangadex", "download"]
                apiHandler.universalStartDownloading(param, mode)
            }
        }

        Rectangle {
            id: mangadexStatusRectangle
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.margins: 5
            color: "#00ff08"
            height: 20
            width: 20
        }
    }

    Connections {
        target: apiHandler
        onUniversalDownloadingStarted: {
            if (mode[0] == "exhentai")
                exhentaiStatusRectangle.color = "#ff0000"
            else if (mode[0] == "mangarock")
                mangarockStatusRectangle.color = "#ff0000"
            else if (mode[0] == "pixiv")
                pixivStatusRectangle.color = "#ff0000"
            else if (mode[0] == "mangadex")
                mangadexStatusRectangle.color = "#ff0000"
        }
        onUniversalDownloadingFinished: {
            if (mode[0] == "exhentai" && mode[1] == "void")
                exhentaiStatusRectangle.color = "#00ff08"
            else if (mode[0] == "mangarock")
                mangarockStatusRectangle.color = "#00ff08"
            else if (mode[0] == "pixiv")
                pixivStatusRectangle.color = "#00ff08"
            else if (mode[0] == "mangadex")
                mangadexStatusRectangle.color = "#00ff08"
        }
    }
}
