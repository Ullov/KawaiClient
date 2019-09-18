import QtQuick 2.0
import QtQuick.Controls 2.2
import "qrc:/QmlIncludes/qml/QmlIncludes/" as QmlIncludes

Rectangle {
    anchors.fill: parent
    color: "#34353b"

    property bool doujinshi: true
    property bool nonH: true
    property bool manga: true
    property bool imageSet: true
    property bool artistCg: true
    property bool cosplay: true
    property bool gameCg: true
    property bool asianPorn: true
    property bool western: true
    property bool misc: true

    Rectangle {
        id: topBar
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.margins: 5
        height: frontPageButton.height
        Label {
            id: frontPageButton
            text: ">Front Page"
            font.pixelSize: 16
            color: "White"
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    parent.color = "Green"
                }
            }
        }
    }

    Rectangle {
        id: mainArea
        anchors.top: topBar.bottom
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.margins: 5
        width: (parent.width / 100) * 80
        color: "#4f535b"
        Rectangle {
            id: filterRectangle
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 5
            color: "#4f535b"
            border.color: "Black"
            border.width: 2
            height: 150
            width: (parent.width / 100) * 50
            clip: true
            Grid {
                id: genreSelectorGrid
                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 5
                columns: 5
                QmlIncludes.KawaiButton {
                    id: doujinshiSelectRectangle
                    standartColor: "#9E2720"
                    heightC: 20
                    labelText: "Doujinshi"
                    labelTextColor: "White"
                    labelTextWeight: Font.Bold
                    borderWidthC: 0
                    onHoveredColor: "#571c1c"
                }
                QmlIncludes.KawaiButton {
                    id: mangaSelectRectangle
                    standartColor: "#DB6C24"
                    heightC: 20
                    labelText: "Manga"
                    labelTextColor: "White"
                    labelTextWeight: Font.Bold
                    borderWidthC: 0
                    onHoveredColor: "#571c1c"
                }
                QmlIncludes.KawaiButton {
                    id: artistCgSelectRectangle
                    standartColor: "#D38F1D"
                    heightC: 20
                    labelText: "Artist CG"
                    labelTextColor: "White"
                    labelTextWeight: Font.Bold
                    borderWidthC: 0
                    onHoveredColor: "#571c1c"
                }
                QmlIncludes.KawaiButton {
                    id: gameCgSelectRectangle
                    standartColor: "#6A936D"
                    heightC: 20
                    labelText: "Game CG"
                    labelTextColor: "White"
                    labelTextWeight: Font.Bold
                    borderWidthC: 0
                    onHoveredColor: "#571c1c"
                }
                QmlIncludes.KawaiButton {
                    id: westernSelectRectangle
                    standartColor: "#AB9F60"
                    heightC: 20
                    labelText: "Western"
                    labelTextColor: "White"
                    labelTextWeight: Font.Bold
                    borderWidthC: 0
                    onHoveredColor: "#571c1c"
                }
                QmlIncludes.KawaiButton {
                    id: nonHSelectRectangle
                    standartColor: "#5FA9CF"
                    heightC: 20
                    labelText: "Non-H"
                    labelTextColor: "White"
                    labelTextWeight: Font.Bold
                    borderWidthC: 0
                    onHoveredColor: "#571c1c"
                }
                QmlIncludes.KawaiButton {
                    id: imageSetSelectRectangle
                    standartColor: "#325CA2"
                    heightC: 20
                    labelText: "Image Set"
                    labelTextColor: "White"
                    labelTextWeight: Font.Bold
                    borderWidthC: 0
                    onHoveredColor: "#571c1c"
                }
                QmlIncludes.KawaiButton {
                    id: cosplaySelectRectangle
                    standartColor: "#6A32A2"
                    heightC: 20
                    labelText: "Cosplay"
                    labelTextColor: "White"
                    labelTextWeight: Font.Bold
                    borderWidthC: 0
                    onHoveredColor: "#571c1c"
                }
                QmlIncludes.KawaiButton {
                    id: asianPornSelectRectangle
                    standartColor: "#A23282"
                    heightC: 20
                    labelText: "Asian Porn"
                    labelTextColor: "White"
                    labelTextWeight: Font.Bold
                    borderWidthC: 0
                    onHoveredColor: "#571c1c"
                }
                QmlIncludes.KawaiButton {
                    id: miscSelectRectangle
                    standartColor: "#777777"
                    heightC: 20
                    labelText: "Misc"
                    labelTextColor: "White"
                    labelTextWeight: Font.Bold
                    borderWidthC: 0
                    onHoveredColor: "#571c1c"
                }
            }

            TextField {
                id: filterInputTextField
                anchors.top: genreSelectorGrid.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.topMargin: 15
                anchors.leftMargin: 20
                anchors.rightMargin: 20
                placeholderText: "Search Keywords"
                height: 35
                color: "White"
                font.pointSize: 12
                background: Rectangle {
                    color: "#34353b"
                }
            }
            Rectangle {
                anchors.top: filterInputTextField.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: 5
                width: applyFilterButton.width + clearFilterButton.width + refreshButton.width
                QmlIncludes.KawaiButton {
                    id: applyFilterButton
                    anchors.left: parent.left
                    anchors.margins: 5
                    labelText: "Apply filter"
                    standartColor: "#34353b"
                    borderColorC: "#8d8d8d"
                    labelTextColor: "White"
                    borderWidthC: 2
                    borderRadiusC: 3
                    heightC: 30
                    onClicked: {
                        var param = [filterInputTextField.text]
                        var mode = ["exhentai", "viewFrontPage"]
                        apiHandler.universalStartDownloading(param, mode)
                    }
                }
                QmlIncludes.KawaiButton {
                    id: clearFilterButton
                    anchors.left: applyFilterButton.right
                    anchors.margins: 5
                    labelText: "Clear filter"
                    standartColor: "#34353b"
                    borderColorC: "#8d8d8d"
                    labelTextColor: "White"
                    borderWidthC: 2
                    borderRadiusC: 3
                    heightC: 30
                    onClicked: filterInputTextField.text = ""
                }
                QmlIncludes.KawaiButton {
                    id: refreshButton
                    anchors.left: clearFilterButton.right
                    anchors.margins: 5
                    labelText: "Refresh"
                    standartColor: "#34353b"
                    borderColorC: "#8d8d8d"
                    labelTextColor: "White"
                    borderWidthC: 2
                    borderRadiusC: 3
                    heightC: 30
                }
            }
        }
        Rectangle {
            id: titleList
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.top: filterRectangle.bottom
            anchors.margins: 5

        }
    }
}
