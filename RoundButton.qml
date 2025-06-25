import QtQuick
import QtQuick.Controls

Button {
    id: control
    width: 40
    height: 40

    property string iconSource: ""

    background: Rectangle {
        id: bg
        radius: width / 2
        color: control.pressed ? "#666666AA" : (control.hovered ? "#777777AA" : "#88888888")  // серый с прозрачностью
        border.color: "white"
        border.width: 1

        Behavior on color {
            ColorAnimation { duration: 150 }
        }

        layer.enabled: true
        layer.smooth: true
    }

    contentItem: Item {
        anchors.fill: parent

        Image {
            id: iconImage
            anchors.centerIn: parent
            source: control.iconSource
            width: 20
            height: 20
            fillMode: Image.PreserveAspectFit
            visible: control.iconSource !== ""
        }

        Text {
            anchors.centerIn: parent
            text: control.text
            color: "white"
            font.pixelSize: 16
            font.bold: true
            visible: control.iconSource === ""
        }
    }
}
