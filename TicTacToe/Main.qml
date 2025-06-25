import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "." as Custom

Window {
    width: 1000
    height: 1000
    visible: true
    title: qsTr("Tic Tac Toe")

    Text {
                text: "Tic Tac Toe"
                font.pixelSize: 40
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }

    Connections {
        target: controller
        function onFirstPlayerChanged() {
            firstPlayerIsX = controller.getTurn()
        }
    }

    //exit button
    Custom.RoundButton {
        iconSource: model.getIconUrl("close.png")
        text : "X"
        width: 30
        height: 30
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.topMargin: 15
        anchors.rightMargin: 15
        onClicked: Qt.quit()
    }
    // Храним текст результата игры
    property string resultDialogText: ""

    // Стилизация и кастомный диалог окончания игры
    Dialog {
        id: resultDialog
        title: "Game Over"
        modal: true
        standardButtons: Dialog.Ok
        visible: false
        x: (parent.width - width) / 2    // по центру по горизонтали
        y: 50                            // отступ от верхнего края (например, 50 пикселей)

        onAccepted: {
            controller.resetBoard()
            resultDialog.visible = false
        }

        contentItem: Column {
            width: 300
            spacing: 20
            padding: 20

            Text {
                id: resultText
                text: resultDialogText
                color: "green"
                font.pixelSize: 26
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WordWrap
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }


    // Сигнал победы от контроллера
    Connections {
        target: controller
        function onGameOver(result) {
            if (result === 1)
                resultDialogText = "🥳Player 1 wins!🥳"
            else if (result === 2)
                resultDialogText = "🥳Player 2 wins!🥳"
            else if (result === 3)
                resultDialogText = "Draw!"
            resultDialog.visible = true
        }
    }

    Row {
        anchors.centerIn: parent
        spacing: 5
        id : row1

        Column {
            spacing: 5

            Button {
                id: b00; width: 85; height: 85
                text: controller.getIndex(0, 0)
                font.bold: true
                font.pixelSize: 25
                onClicked: controller.setIndex(0, 0, controller.getTurn())
                Connections {
                    target: model
                    function onBoardChanged() {
                        b00.text = controller.getIndex(0, 0)
                    }
                }
            }

            Button {
                id: b10; width: 85; height: 85
                text: controller.getIndex(1, 0)
                font.bold: true
                font.pixelSize: 25
                onClicked: controller.setIndex(1, 0, controller.getTurn())
                Connections {
                    target: model
                    function onBoardChanged() {
                        b10.text = controller.getIndex(1, 0)
                    }
                }
            }

            Button {
                id: b20; width: 85; height: 85
                text: controller.getIndex(2, 0)
                font.bold: true
                font.pixelSize: 25
                onClicked: controller.setIndex(2, 0, controller.getTurn())
                Connections {
                    target: model
                    function onBoardChanged() {
                        b20.text = controller.getIndex(2, 0)
                    }
                }
            }
        }

        Column {
            spacing: 5

            Button {
                id: b01; width: 85; height: 85
                text: controller.getIndex(0, 1)
                font.bold: true
                font.pixelSize: 25
                onClicked: controller.setIndex(0, 1, controller.getTurn())
                Connections {
                    target: model
                    function onBoardChanged() {
                        b01.text = controller.getIndex(0, 1)
                    }
                }
            }

            Button {
                id: b11; width: 85; height: 85
                text: controller.getIndex(1, 1)
                font.bold: true
                font.pixelSize: 25
                onClicked: controller.setIndex(1, 1, controller.getTurn())
                Connections {
                    target: model
                    function onBoardChanged() {
                        b11.text = controller.getIndex(1, 1)
                    }
                }
            }

            Button {
                id: b21; width: 85; height: 85
                text: controller.getIndex(2, 1)
                font.bold: true
                font.pixelSize: 25
                onClicked: controller.setIndex(2, 1, controller.getTurn())
                Connections {
                    target: model
                    function onBoardChanged() {
                        b21.text = controller.getIndex(2, 1)
                    }
                }
            }
        }

        Column {
            id : col3
            spacing: 5

            Button {
                id: b02; width: 85; height: 85
                text: controller.getIndex(0, 2)
                font.bold: true
                font.pixelSize: 25
                onClicked: controller.setIndex(0, 2, controller.getTurn())
                Connections {
                    target: model
                    function onBoardChanged() {
                        b02.text = controller.getIndex(0, 2)
                    }
                }
            }

            Button {
                id: b12; width: 85; height: 85
                text: controller.getIndex(1, 2)
                font.bold: true
                font.pixelSize: 25
                onClicked: controller.setIndex(1, 2, controller.getTurn())
                Connections {
                    target: model
                    function onBoardChanged() {
                        b12.text = controller.getIndex(1, 2)
                    }
                }
            }

            Button {
                id: b22; width: 85; height: 85
                text: controller.getIndex(2, 2)
                font.bold: true
                font.pixelSize: 25
                onClicked: controller.setIndex(2, 2, controller.getTurn())
                Connections {
                    target: model
                    function onBoardChanged() {
                        b22.text = controller.getIndex(2, 2)
                    }
                }
            }
        }
    }
    property bool currentAiEnabled: controller.aiEnabled
    property bool firstPlayerIsX: controller.getTurn()
    Row {
        id : row2
        spacing: 10
        anchors.top: row1.bottom
        anchors.horizontalCenter: row1.horizontalCenter
        anchors.topMargin: 30

        Button {
            id: switchModeButton
            width: 160
            height: 50
            text: currentAiEnabled ? "Play with AI" : "Play with Human"
            font.pixelSize: 16
            onClicked: {
                currentAiEnabled = !currentAiEnabled
                controller.aiEnabled = currentAiEnabled
            }
            background: Rectangle {
                color: currentAiEnabled ? "#3498db" : "#9b59b6"
                radius: 25
            }
        }

        Button {
            id: switchFirstPlayerButton
            width: 160
            height: 50
            text: firstPlayerIsX ? "First: X" : "First: O"
            font.pixelSize: 16
            onClicked: {
                firstPlayerIsX = !firstPlayerIsX
                controller.setFirstPlayer(firstPlayerIsX)
            }
            background: Rectangle {
                color: "#2ecc71"
                radius: 25
            }
        }

    }

    Button {
        id: resetButton
        width: 330
        height: 50
        text: "Reset"
        font.pixelSize: 16
        anchors.top: row2.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter

        onClicked: {
            controller.resetBoard()
        }

        background: Rectangle {
            color: "#e67e22"
            radius: 25
        }
    }
}
