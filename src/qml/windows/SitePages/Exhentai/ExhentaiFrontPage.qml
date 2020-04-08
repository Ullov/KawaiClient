import QtQuick 2.0
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.5
import "../../../../js/Tools.js" as Tools

Rectangle {
    property var objectEtsbColor: {
        "Doujinshi": "#9E2720",
        "Manga": "#DB6C24",
        "Artist CG": "#D38F1D",
        "Game CG": "#6A936D",
        "Western": "#AB9F60",
        "Non-H": "#5FA9CF",
        "Image Set": "#325CA2",
        "Cosplay": "#6A32A2",
        "Asian Porn": "#A23282",
        "Misc": "#777777"
    }
    id: background
    anchors.fill: parent
    color: "#34353b"
    Rectangle {
        id: usefulArea
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: 5
        width: Tools.cutNumberByPercents(parent.width, 90)
        color: "#4f535b"
        Item {
            id: filtersAndInputItem
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.margins: 5
            width: Tools.cutNumberByPercents(parent.width, 60)
            height: 145
            RadialGradient {
                anchors.fill: parent
                verticalRadius: Tools.cutNumberByPercents(parent.height, 70)
                horizontalRadius: Tools.cutNumberByPercents(parent.width, 70)
                gradient: Gradient {
                    GradientStop {
                        position: 0.4
                        color: "#4f535b"
                    }
                    GradientStop {
                        position: 1.0
                        color: "#34353b"
                    }
                }
            }
            Grid {
                id: filtersGrid
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.margins: 15
                spacing: 5
                columns: 5
                ExhentaiTypeSelectButton {etsbType: "Doujinshi"}
                ExhentaiTypeSelectButton {etsbType: "Manga"}
                ExhentaiTypeSelectButton {etsbType: "Artist CG"}
                ExhentaiTypeSelectButton {etsbType: "Game CG"}
                ExhentaiTypeSelectButton {etsbType: "Western"}
                ExhentaiTypeSelectButton {etsbType: "Non-H"}
                ExhentaiTypeSelectButton {etsbType: "Image Set"}
                ExhentaiTypeSelectButton {etsbType: "Cosplay"}
                ExhentaiTypeSelectButton {etsbType: "Asian Porn"}
                ExhentaiTypeSelectButton {etsbType: "Misc"}
            }
            TextField {
                id: searchTextField
                anchors.top: filtersGrid.bottom
                anchors.margins: 5
                anchors.horizontalCenter: parent.horizontalCenter
                width: filtersGrid.width
                placeholderText: "Search Keywords"
                height: 30
                color: "White"
                font.pointSize: 12
                background: Rectangle {
                    color: "#34353b"
                    radius: 4
                }
            }
            ExhentaiButton {
                anchors.top: searchTextField.bottom
                anchors.right: parent.horizontalCenter
                anchors.margins: 5
                ebText: "Apply filter"
                onClicked: {
                    var param = [searchTextField.text, 0]
                    var mode = ["exhentai", "frontPage"]
                    apiHandler.universalStartDownloading(param, mode)
                }
            }
            ExhentaiButton {
                anchors.top: searchTextField.bottom
                anchors.left: parent.horizontalCenter
                ebText: "Clear filter"
                anchors.margins: 5
                onClicked: searchTextField.text = ""
            }
            ListView {
                id: galleriesScrollListView
                model: galleriesScrollListModel
                delegate: leftBarListViewDelegateItem
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: leftBarDivisionLine.bottom
                anchors.bottom: parent.bottom
                anchors.margins: 5
                clip: true
                ScrollBar.vertical: ScrollBar {
                    id: scrollBarItem
                    policy: ScrollBar.AlwaysOn
                }
                Keys.onUpPressed: scrollBarItem.decrease()
                Keys.onDownPressed: scrollBarItem.increase()
                spacing: 3
            }
            ListModel {
                id: galleriesScrollListModel
            }
        }
    }
}
