import QtQuick 2.0
import QtQuick.Controls 2.5
import "../../../QmlIncludes"
import KEnums 1.0
import "ParserFunctions.js" as ParsFuncs


Rectangle {
    property var onClickFunctionList: {
        "standart": function(dataArr, parserType, parserMode){
            ParsFuncs.standartOnClickFunction(dataArr, parserType, parserMode)
        },
        "mangadex": function(dataArr, parserType, parserMode){
            ParsFuncs.mangadexOnClickFunction(dataArr, parserType, parserMode)
        }
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
        ListElement {name: "Pixiv";  placeholder:"Enter user ID..."; functionType:"standart"; parserMode: ParserModes.Pixiv.Download; parserType: KEnums.Parsers.Pixiv}
        ListElement {name: "MangaDex"; placeholder:"Enter manga ID..."; functionType:"mangadex"; parserMode: ParserModes.MangaDex.Download; parserType: KEnums.Parsers.MangaDex}
        ListElement {name: "ExHentai"; placeholder:"Enter gallery ID..."; functionType:"standart"; parserMode: ParserModes.ExHentai.Download; parserType: KEnums.Parsers.ExHentai}
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
                var path;
                if (parserType === KEnums.Parsers.MangaDex)
                    path = "qrc:/qml/windows/Misc/Parsers/MangadexInputRectangle.qml"
                else
                    path = "qrc:/qml/windows/Misc/Parsers/StandartInputRectangle.qml"
                var obj = Qt.createComponent(path, innerDelegateItem)
                if (obj.status === Component.Error)
                    console.log(obj.errorString())
                obj.createObject(innerDelegateItem)
            }
        }
    }
}
