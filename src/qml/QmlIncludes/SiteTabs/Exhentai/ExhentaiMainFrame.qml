import QtQuick 2.0
import QtQuick.Controls 2.2

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
                Rectangle {
                    id: doujinshiSelectRectangle
                    color: "#9E2720"
                    height: 20
                    width: 100
                    radius: 5
                    Label {
                        anchors.centerIn: parent
                        color: "White"
                        font.weight: "Bold"
                        text: "Doujinshi"
                    }
                }
                Rectangle {
                    id: mangaSelectRectangle
                    color: "#DB6C24"
                    height: 20
                    width: 100
                    radius: 5
                    Label {
                        anchors.centerIn: parent
                        color: "White"
                        font.weight: "Bold"
                        text: "Manga"
                    }
                }
                Rectangle {
                    id: artistCgSelectRectangle
                    color: "#D38F1D"
                    height: 20
                    width: 100
                    radius: 5
                    Label {
                        anchors.centerIn: parent
                        color: "White"
                        font.weight: "Bold"
                        text: "Artist CG"
                    }
                }
                Rectangle {
                    id: gameCgSelectRectangle
                    color: "#6A936D"
                    height: 20
                    width: 100
                    radius: 5
                    Label {
                        anchors.centerIn: parent
                        color: "White"
                        font.weight: "Bold"
                        text: "Game CG"
                    }
                }
                Rectangle {
                    id: westernSelectRectangle
                    color: "#AB9F60"
                    height: 20
                    width: 100
                    radius: 5
                    Label {
                        anchors.centerIn: parent
                        color: "White"
                        font.weight: "Bold"
                        text: "Western"
                    }
                }
                Rectangle {
                    id: nonHSelectRectangle
                    color: "#5FA9CF"
                    height: 20
                    width: 100
                    radius: 5
                    Label {
                        anchors.centerIn: parent
                        color: "White"
                        font.weight: "Bold"
                        text: "Non-H"
                    }
                }
                Rectangle {
                    id: imageSetSelectRectangle
                    color: "#325CA2"
                    height: 20
                    width: 100
                    radius: 5
                    Label {
                        anchors.centerIn: parent
                        color: "White"
                        font.weight: "Bold"
                        text: "Image Set"
                    }
                }
                Rectangle {
                    id: cosplaySelectRectangle
                    color: "#6A32A2"
                    height: 20
                    width: 100
                    radius: 5
                    Label {
                        anchors.centerIn: parent
                        color: "White"
                        font.weight: "Bold"
                        text: "Cosplay"
                    }
                }
                Rectangle {
                    id: asianPornSelectRectangle
                    color: "#A23282"
                    height: 20
                    width: 100
                    radius: 5
                    Label {
                        anchors.centerIn: parent
                        color: "White"
                        font.weight: "Bold"
                        text: "Asian Porn"
                    }
                }
                Rectangle {
                    id: miscSelectRectangle
                    color: "#777777"
                    height: 20
                    width: 100
                    radius: 5
                    Label {
                        anchors.centerIn: parent
                        color: "White"
                        font.weight: "Bold"
                        text: "Misc"
                    }
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
                Button {
                    id: applyFilterButton
                    anchors.left: parent.left
                    width: 100
                    height: 30
                    background: Rectangle {
                        color: "#34353b"
                        border.color: "#8d8d8d"
                        border.width: 2
                        radius: 3
                        Text {
                            anchors.centerIn: parent
                            text: "Apply filter"
                            color: "White"
                        }
                    }
                    onClicked: {
                        var param = [filterInputTextField.text]
                        var mode = ["exhentai", "viewFrontPage"]
                        apiHandler.universalStartDownloading(param, mode)
                    }
                }
                Button {
                    id: clearFilterButton
                    anchors.left: applyFilterButton.right
                    anchors.margins: 5
                    width: 100
                    height: 30
                    background: Rectangle {
                        color: "#34353b"
                        border.color: "#8d8d8d"
                        border.width: 2
                        radius: 3
                        Text {
                            anchors.centerIn: parent
                            text: "Clear filter"
                            color: "White"
                        }
                    }
                    onClicked: filterInputTextField.text = ""
                }
                Button {
                    id: refreshButton
                    anchors.left: clearFilterButton.right
                    anchors.margins: 5
                    width: 100
                    height: 30
                    background: Rectangle {
                        color: "#34353b"
                        border.color: "#8d8d8d"
                        border.width: 2
                        radius: 3
                        Text {
                            anchors.centerIn: parent
                            text: "Refresh"
                            color: "White"
                        }
                    }
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
