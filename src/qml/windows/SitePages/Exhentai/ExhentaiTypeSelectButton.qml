import QtQuick 2.0
import "../../../QmlIncludes"

KawaiButton {
    property alias etsbType: root.labelText

    id: root
    heightC: 20
    labelTextColor: "White"
    labelTextWeight: Font.Bold
    standartColor: objectEtsbColor[labelText]
    borderWidthC: 0
    onHoveredColor: "#571c1c"
}
