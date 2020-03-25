import QtQuick 2.0
import QtQuick.Controls 2.5
import "../../../QmlIncludes"

StandartInputRectangle {
    id: root
    MangadexCheckBoxes {
        id: checkBoxRectangle
        anchors.right: root.sirStatusTextBox.left
        anchors.margins: 5
    }
    Component.onCompleted: sirInputTextField.anchors.right = checkBoxRectangle.left
}
