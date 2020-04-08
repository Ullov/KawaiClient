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
    sirInputTextField.anchors.right: checkBoxRectangle.left

    /*sirStartDownloadButton.onClicked: {
        var en = checkBoxRectangle.enLang
        var ru = checkBoxRectangle.ruLang
        var other = checkBoxRectangle.otherLangs
        console.log(en, ru, other)
        onClickFunctionList[functionType](
            sirInputTextField.text,
            parserType, parserMode,
            en,
            ru,
            other
        )
    }*/
    dataArr: [
        sirInputTextField.text,
        checkBoxRectangle.enLang,
        checkBoxRectangle.ruLang,
        checkBoxRectangle.otherLangs
    ]
}
