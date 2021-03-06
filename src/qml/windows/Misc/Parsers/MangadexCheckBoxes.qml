import QtQuick 2.0
import QtQuick.Controls 2.5

Rectangle {
    property alias enLang: enLangCheckbox.checked
    property alias ruLang: ruLangCheckbox.checked
    property alias otherLangs: otherLangCheckbox.checked
    id: checkBoxesRectangle
    anchors.verticalCenter: parent.verticalCenter
    height: 30
    width: 200
    CheckBox {
        id: enLangCheckbox
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        text: "EN"
    }
    CheckBox {
        id: ruLangCheckbox
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: enLangCheckbox.right
        text: "RU"
    }
    CheckBox {
        id: otherLangCheckbox
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: ruLangCheckbox.right
        text: "Other"
    }
}
