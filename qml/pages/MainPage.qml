import QtQuick 2.0
import Sailfish.Silica 1.0
import QtQuick.Layouts 1.0
import gamelogic 1.0

Page {
    objectName: "mainPage"
    allowedOrientations: Orientation.Portrait
    property var grida: []
    GameLogic {
        id: gameLogic
        rows: 18 // Количество строк в сетке
        columns: 11 // Количество столбцов в сетке


    }
    PageHeader{
        title: "Игра в Жизнь"
        

    }




    SilicaGridView {


        ColumnLayout {
            Row {
                Layout.fillWidth: true
                Layout.preferredHeight: Theme.itemSizeLarge

                IconButton {
                     id: startButton
                    icon.source: "image://theme/icon-m-play"
                    onClicked: gameLogic.start() // Запустить игру

                }

                IconButton {
                    id:stopButton
                    icon.source: "image://theme/icon-m-pause"
                    onClicked: gameLogic.stop() // Поставить игру на паузу
                }

                IconButton {
                     id: resetButton
                    icon.source: "image://theme/icon-m-refresh"
                    onClicked: {
                                            gameLogic.reset() // Сбросить игру
                                            startButton.enabled = true // Разрешить нажатие кнопки "Start"
                                            stopButton.enabled = true
                                        }

                }
            }
            Grid{
                id: grid1
                rows: 18
                columns: 11
                spacing: 6


                Repeater {
                    model: gameLogic.gridList
                    delegate: Rectangle {
                        width: 60
                        height: 60
                        color: modelData === 0 ? "black" : "white"
                        border.color: "black"
                        border.width: 1
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                gameLogic.toggleCell(index)
                            }
                        }
                    }
                }
            }
        }
    }
    Component.onCompleted: {
            startButton.enabled = false // Запретить нажатие кнопки "Start" при запуске приложения
            stopButton.enabled = false
        }

}
