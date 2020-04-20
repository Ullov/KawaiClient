import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import "../../../../js/Tools.js" as Tools

Button {
    id: root

    property bool selected: false

    anchors.left: parent.left
    anchors.right: parent.right
    height: 23

    background: Rectangle {
        id: buttonRectangle
        color: "White"

        CheckBox {
            id: selectCheckBox
            checked: selected
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            indicator.height: 20
            indicator.width: 20
            onCheckedChanged: sel = selected = checked
        }

        Image {
            id: icon
            source: iconPath
            anchors.left: selectCheckBox.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: 23
        }

        Text {
            id: itemNameLabel
            anchors.left: icon.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.margins: 2
            text: itemName
            width: 500

            color: "Black"
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 12
            font.family: "Segoe UI"
        }

        Text {
            id: itemTypeLabel
            anchors.left: itemNameLabel.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            text: fileType + "\t" + Tools.bytesToHumanReadable(size)

            color: "Black"
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 12
            font.family: "Segoe UI"
        }
    }

    onDoubleClicked: openFileOrFolder()
    onHoveredChanged: hov = hovered

    states: [
        State {
            name: "onHoveredRectangle"
            when: root.hovered == true & selected == false
            PropertyChanges {
                target: buttonRectangle
                color: "#CDE2FC"
            }
        },
        State {
            name: "onSelected"
            when: root.selected == true
            PropertyChanges {
                target: buttonRectangle
                color: "#A0CBFF"
            }
        }
    ]

    function openFileOrFolder() {
        if (isDir)
            fsExplorerHandle.slotCd(itemName)
        else
            fsExplorerHandle.slotOpenInDefaultApp(filePath)
    }
}
