import QtQuick 2.0
import QtQuick.Controls 2.2
import "../../../QmlIncludes" as QmlIncludes

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
                width: applyFilterButton.width + clearFilterButton.width
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
            }
        }
        Rectangle {
            id: titleList
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.top: filterRectangle.bottom
            anchors.margins: 5

            Component {
                id: delegateItem
                Rectangle {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    height: 300
                    border.color: "Black"
                    radius: 5
                    Image {
                        id: coverImage
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.left: parent.left
                        anchors.margins: 5
                        width: 230
                    }
                    Rectangle {
                        id: infoRectangle
                        anchors.top: parent.top
                        anchors.left: coverImage.right
                        anchors.bottom: parent.bottom
                        anchors.right: parent.right
                        anchors.margins: 5
                        radius: 5
                        border.color: "Black"
                        /*Text {
                            anchors.fill: parent
                            anchors.margins: 5
                            text: "#:" + index + "\t" + name + "\n" + url + "\n" + coverUrl + "\n" + tagBlock;

                        }*/
                        Rectangle {
                            id: indexRectangle
                            anchors.left: parent.left
                            anchors.top: parent.top
                            height: 20
                            width: 40
                            border.color: "Black"
                            radius: 5
                            Text {
                                anchors.centerIn: parent
                                text: "# " + index
                            }
                        }
                        Rectangle {
                            id: nameRectangle
                            anchors.left: indexRectangle.right
                            anchors.top: parent.top
                            height: indexRectangle.height
                            anchors.right: parent.right
                            border.color: "Black"
                            radius: 5
                            Text {
                                anchors.centerIn: parent
                                text: name
                            }
                        }
                        Rectangle {
                            id: typeRectangle
                            anchors.left: parent.left
                            anchors.top: indexRectangle.bottom
                            width: 100
                            height: 20
                            border.color: "Black"
                            radius: 5
                        }
                        Rectangle {
                            id: dataTimeRectangle
                            anchors.top: typeRectangle.bottom
                            anchors.left: parent.left
                            height: 60
                            width: typeRectangle.width
                            border.color: "Black"
                            radius: 5
                        }
                        Rectangle {
                            id: uploaderRectangle
                            anchors.top: dataTimeRectangle.bottom
                            anchors.left: parent.left
                            height: 30
                            width: typeRectangle.width
                            border.color: "Black"
                            radius: 5
                        }
                        Rectangle {
                            id: pagesRectangle
                            anchors.top: uploaderRectangle.bottom
                            anchors.left: parent.left
                            height: 30
                            width: typeRectangle.width
                            border.color: "Black"
                            radius: 5
                        }
                        Rectangle {
                            id: tagsRectangle
                            anchors.left: typeRectangle.right
                            anchors.right: parent.right
                            anchors.top: indexRectangle.bottom
                            anchors.bottom: parent.bottom
                            border.color: "Black"
                            radius: 5
                            Text {
                                anchors.fill: parent
                                anchors.margins: 5
                                text: tagBlock
                            }
                        }
                    }
                }
            }
            ListModel {
                id: modelItem
            }
            ListView {
                id:listViewItem
                model: modelItem
                delegate: delegateItem
                anchors.fill: parent
                anchors.margins: 5
                clip: true
                ScrollBar.vertical: ScrollBar {
                    id: scrollBarItem
                    policy: ScrollBar.AlwaysOn
                }
                Keys.onUpPressed: scrollBarItem.decrease()
                Keys.onDownPressed: scrollBarItem.increase()
            }
        }
    }
    Connections {
        target: apiHandler
        onUniversalDownloadingFinished: {
            if (mode[0] == "exhentai" && mode[1] == "viewFrontPage")
                addingElements(data)
        }
    }

    function addingElements(elements) {
        modelItem.clear()
        var tagBlock = []
        var tmpTagBlock = ""
        for (var j = 0; elements["data"][j]; j++) {
            var keysArr = Object.keys(elements["data"][j]["tags"])
            for (var i = 0; i < keysArr.length; i++)
            {
                var tagName = keysArr[i]
                var tagElements = elements["data"][j]["tags"][keysArr[i]]
                tmpTagBlock += tagName + ": "
                for (var k = 0; tagElements[k]; k++)
                {
                    if (tagElements[k + 1])
                        tmpTagBlock += tagElements[k] + ", "
                    else
                        tmpTagBlock += tagElements[k]
                }
                tmpTagBlock += "\n"
            }
            tagBlock[j] = tmpTagBlock
            tmpTagBlock = ""
        }
        var jArr = elements["data"]
        for (var i = 0; jArr[i]; i++) {
            modelItem.append({
                index: i,
                name: jArr[i]["name"],
                url: jArr[i]["url"],
                coverUrl: jArr[i]["coverUrl"],
                tagBlock: tagBlock[i]
            })

        }
    }
}
