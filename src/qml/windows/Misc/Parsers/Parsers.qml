import QtQuick 2.0
import QtQuick.Controls 2.5
import "../../../QmlIncludes"

Rectangle {
    property var onClickFunctionList: {
        "standart": function(text, systemName, gMode){standartOnClickFunction(text, systemName, gMode)},
        "mangadex": function(text, enChecked, ruChecked, otherChecked){mangadexOnClickFunction(text, enChecked, ruChecked, otherChecked)}
    }
    property var modeList: [
        "",
        "download"
    ]

    anchors.fill: parent
    color: "#2849de"
    ListView {
        id: parsersListView
        anchors.fill: parent
        anchors.margins: 5
        model: parsersModelItem
        delegate: parsersDelegateItem
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
        id: parsersModelItem
        ListElement {name: "Pixiv"; systemName: "pixiv"; placeholder:"Enter user ID..."; functionType:"standart"; modeNumber: 0}
        ListElement {name: "MangaDex"; systemName: "mangadex"; placeholder:"Enter manga ID..."; functionType:"mangadex"; modeNumber: 0}
        ListElement {name: "ExHentai"; systemName: "exhentai"; placeholder:"Enter gallery ID..."; functionType:"standart"; modeNumber: 1}
    }
    Component {
        id: parsersDelegateItem
        Rectangle {
            id: innerDelegateItem
            anchors.left: parent.left
            anchors.right: parent.right
            height: 40
            radius: 20
            Component.onCompleted: {
                if (systemName === "mangadex")
                    Qt.createComponent("qrc:/qml/windows/Misc/Parsers/MangadexInputRectangle.qml", innerDelegateItem).createObject(innerDelegateItem)
                else
                    Qt.createComponent("qrc:/qml/windows/Misc/Parsers/StandartInputRectangle.qml", innerDelegateItem).createObject(innerDelegateItem)
            }
        }
    }
    function standartOnClickFunction(text, systemName, gMode)
    {
        var param = [text]
        var mode;
        if (gMode === "")
            mode = [systemName]
        else
            mode = [systemName, gMode]
        apiHandler.universalStartDownloading(param, mode)
    }
    function mangadexOnClickFunction(text, enChecked, ruChecked, otherChecked)
    {
        var param = [text, enChecked, ruChecked, otherChecked]
        var mode = ["mangadex"]
        apiHandler.universalStartDownloading(param, mode)
    }
}
