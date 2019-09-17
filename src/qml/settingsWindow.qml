import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle {
    id: rootRect
    anchors.fill: parent

    property int textFieldsHeight: 35

    Rectangle {
        width: parent.width - 50
        height: 400
        color: "#d2d2d2"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 10
        radius: 10
        Label {
            id: labelPath
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Path settings.")
            font.pixelSize: 16
        }
        Rectangle {
            id: inputRectangleRoot
            width: parent.width
            height: 50
            color: "#949494"
            anchors.top: labelPath.bottom
            anchors.topMargin: 5
            radius: 5
            Label {
                id: labelRoot
                text: "Root path"
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.topMargin: 5
                font.pixelSize: 14
            }
            TextField {
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: labelRoot.bottom
                anchors.rightMargin: parent.width / 20
                anchors.leftMargin: 10
                anchors.bottomMargin: 3
            }
        }

        Rectangle {
            id: inputRectanglePixiv
            width: parent.width
            height: 50
            color: "#949494"
            anchors.top: inputRectangleRoot.bottom
            anchors.topMargin: 5
            radius: 5
            Label {
                id: labelPixiv
                text: "Pixiv path"
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.topMargin: 5
                font.pixelSize: 14
            }
            TextField {
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: labelPixiv.bottom
                anchors.rightMargin: parent.width / 20
                anchors.leftMargin: 10
                anchors.bottomMargin: 3
            }
        }

        Rectangle {
            id: inputRectangleMangarock
            width: parent.width
            height: 50
            color: "#949494"
            anchors.top: inputRectanglePixiv.bottom
            anchors.topMargin: 5
            radius: 5
            Label {
                id: labelMangarock
                text: "MangaRock path"
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.topMargin: 5
                font.pixelSize: 14
            }
            TextField {
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: labelMangarock.bottom
                anchors.rightMargin: parent.width / 20
                anchors.leftMargin: 10
                anchors.bottomMargin: 3
            }
        }

        Rectangle {
            id: inputRectangleNhentai
            width: parent.width
            height: 50
            color: "#949494"
            anchors.top: inputRectangleMangarock.bottom
            anchors.topMargin: 5
            radius: 5
            Label {
                id: labelNhentai
                text: "NHentai path"
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.topMargin: 5
                font.pixelSize: 14
            }
            TextField {
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: labelNhentai.bottom
                anchors.rightMargin: parent.width / 20
                anchors.leftMargin: 10
                anchors.bottomMargin: 3
            }
        }
    }
}
