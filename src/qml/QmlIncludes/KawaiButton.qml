import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle {
    id:root
    property string labelText

    height: 40
    width: 100
    border.color: "Black"
    radius: 6
    color: "#dadada"
    Label {
        id: tetxtLabel
        anchors.centerIn: parent
        text: qsTr(root.labelText)
    }
}
