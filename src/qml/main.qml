import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.5
import "../js/Tools.js" as Tools
import "QmlIncludes"

Window {
    id: baseItem
    visible: true
    width: 640
    height: 480
    color: "Black"
    title: qsTr("Kawai Client")
    visibility: "Maximized"

    KawaiSwitchableWindows {
        id: switchableWindows

    }
    Component.onCompleted: {
        var obj =
        [
           [
                "Site pages",
                [
                    ["ExHentai", "qrc:/qml/windows/SitePages/Exhentai/ExhentaiFrontPage.qml"]
                ]
           ],
           [
                "Misc",
                [
                    ["Parsers", "qrc:/qml/windows/Misc/Parsers/Parsers.qml"]
                ]
           ],
           [
                "Settings and System",
                [
                    ["Settings", "qrc:/qml/windows/SettingsAndSystem/Settings.qml"]
                ]
            ]
        ]
        switchableWindows.addItemsAndSections(obj);
    }
}
