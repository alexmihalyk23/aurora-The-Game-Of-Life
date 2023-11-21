import QtQuick 2.0

// Компонент Cell, который представляет собой прямоугольник с цветом в зависимости от состояния
Item {
    id: cell
    property int state: 0 // Свойство для хранения состояния ячейки (0 или 1)
    Rectangle {
        anchors.fill: parent
        color: state == 0 ? "white" : "black" // Цвет ячейки в зависимости от состояния
        border.color: "gray" // Цвет границы ячейки
    }
}
