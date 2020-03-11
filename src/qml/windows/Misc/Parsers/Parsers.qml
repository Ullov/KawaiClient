import QtQuick 2.0
import QtQuick.Controls 2.5
import "../../../QmlIncludes"

Rectangle {
    property var onClickFunctionList: {
        "standart": function(text, systemName){standartOnClickFunction(text, systemName)},
        "mangadex": function(text, enChecked, ruChecked, otherChecked){mangadexOnClickFunction(text, enChecked, ruChecked, otherChecked)}
    }

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
        ListElement {name: "Pixiv"; systemName: "pixiv"; placeholder:"Enter user ID..."; functionType:"standart"}
        ListElement {name: "MangaDex"; systemName: "mangadex"; placeholder:"Enter manga ID..."; functionType:"mangadex"}
        ListElement {name: "YouTube"; systemName: "youtube"; placeholder:"Enter video URL..."; functionType:"standart"}
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
    function standartOnClickFunction(text, systemName)
    {
        var param = [text]
        var mode = [systemName]
        apiHandler.universalStartDownloading(param, mode)
    }
    function mangadexOnClickFunction(text, enChecked, ruChecked, otherChecked)
    {
        var param = [text, enChecked, ruChecked, otherChecked]
        var mode = ["mangadex"]
        apiHandler.universalStartDownloading(param, mode)
    }
}
