import QtQuick 2.11
import QtQuick.Window 2.11
import "qrc:/js/pageloader.js" as Pageloader
import QtQuick.Controls 1.4
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import "qrc:/QmlIncludes/qml/QmlIncludes/" as QmlIncludes
import "qrc:/QmlIncludes/qml/QmlIncludes/SiteTabs/Pixiv" as PixivTabs
import "qrc:/QmlIncludes/qml/QmlIncludes/SiteTabs/Exhentai" as ExhentaiTabs

Window {
    id: baseItem
    visible: true
    width: 640
    height: 480
    color: "Black"
    title: qsTr("Kawai Client")
    visibility: "Maximized"


    TabView {
        id: tabs
        anchors.fill: parent
        Component.onCompleted: {
            addTab("Home Tab",homeTab)
            addTab("Log Tab", Qt.createComponent("qrc:/qml/logWindow.qml"))
            addTab("Settings Tab", Qt.createComponent("qrc:/qml/settingsWindow.qml"))
        }


        Rectangle {
            id: loadTabButtonStyle
            implicitWidth: 100
            implicitHeight: 40
//            border.width: control.activeFocus ? 2 : 1
            border.color: "Black"
            color: "#dadada"
            radius: 5
        }

        Component {
            id: exhentaiTab
            ExhentaiTabs.ExhentaiMainFrame {}
        }

        Component {
            id: homeTab
            Rectangle {
                color: "#2849de"
                anchors.fill: parent
                QmlIncludes.KawaiDownloadBar {}

                Grid {
                    anchors.centerIn: parent
                    columns: 8
                    spacing: 5

                    QmlIncludes.KawaiLoadTabButton {
                        id: pixivSatrtButton
                        labelText: "Pixiv"
                        siteFile: "qrc:/qml/sites/pixiv/pixiv.qml"
                        tabTitle: "Pixiv"
                    }
                    QmlIncludes.KawaiLoadTabButton {
                        id: mangarockStartButton
                        labelText: "MangaRock"
                        siteFile: "qrc:/qml/sites/mangarock/mangarock.qml"
                        tabTitle: "MangaRock"
                    }
                    Button {
                        text: "ExHentai"
                        onClicked: tabs.addTab("ExHentai", exhentaiTab)
                        background: loadTabButtonStyle
                    }
                }
            }
        }

        function loadTab(siteFile, title){
            var cTab = currentIndex
            var t = addTab(title, Qt.createComponent(siteFile))
            currentIndex = cTab
        }

        style: TabViewStyle {
            frameOverlap: 1
            tabsMovable: true
            tab: Rectangle {
                color: styleData.selected ? "#484848" : "#dddddd"
                border.color: "steelblue"
                implicitWidth: Math.max(text.width + 4, 80)
                implicitHeight: 30

                Text {
                    id: text
                    anchors.centerIn: parent
                    text: styleData.title
                    color: styleData.selected ? "white" : "black"
                }
            }
            frame: Rectangle { color: "steelblue" }
        }
    }
}
