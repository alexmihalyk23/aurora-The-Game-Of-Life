#include "gamelogic.h"
#include <QDebug>

GameLogic::GameLogic(QObject *parent) : QObject(parent)
{
    // Инициализируем поля значениями по умолчанию
    m_rows = 0;
    m_columns = 0;
    m_grid = QVector<int>();
    m_timer = new QTimer(this);
    // Соединяем сигнал таймера со слотом обновления сетки
    connect(m_timer, &QTimer::timeout, this, &GameLogic::updateGrid);
}
// Геттер для свойства rows
int GameLogic::rows() const
{
    return m_rows;
}

// Сеттер для свойства rows
void GameLogic::setRows(int rows)
{
    if (m_rows == rows)
        return;

    m_rows = rows;
    emit rowsChanged(m_rows);
}

// Геттер для свойства columns
int GameLogic::columns() const
{
    return m_columns;
}

// Сеттер для свойства columns
void GameLogic::setColumns(int columns)
{
    if (m_columns == columns)
        return;

    m_columns = columns;
    emit columnsChanged(m_columns);
}

// Геттер для свойства grid

QVector<int> GameLogic::grid() const
{
    return m_grid;
}

// Сеттер для свойства grid
void GameLogic::setGrid(const QVector<int> &grid)
{
    if (m_grid == grid)
        return;

    m_grid = grid;
    emit gridChanged(m_grid);
}
QVariantList GameLogic::gridList() const
{
    QVariantList list;
    for (int i = 0; i < m_grid.size(); i++) {
        list.append(m_grid[i]);
    }
    return list;
}

// Слот для запуска игры
void GameLogic::start()
{
    // Запускаем таймер с интервалом в 500 мс
    m_timer->start(500);
}

// Слот для остановки игры
void GameLogic::stop()
{
    // Останавливаем таймер
    m_timer->stop();
}

// Слот для сброса игры
void GameLogic::reset()
{
    // Останавливаем таймер
    m_timer->stop();

    // Заполняем сетку случайными значениями (0 или 1)
    m_grid.clear();
    for (int i = 0; i < m_rows * m_columns; i++) {
        m_grid.append(qrand() % 2);
    }

    // Уведомляем QML об изменении сетки
    emit gridChanged(m_grid);
}

// Слот для переключения состояния ячейки по индексу
void GameLogic::toggleCell(int index)
{
    // Проверяем, что индекс в допустимом диапазоне
    if (index >= 0 && index < m_rows * m_columns) {
            // Переключаем состояние ячейки (0 -> 1, 1 -> 0)
            m_grid[index] = 1 - m_grid[index];

            // Уведомляем QML об изменении сетки
            emit gridChanged(m_grid);
        }
}

// Слот для обновления сетки ячеек по правилам игры
// Пример использования отладчика для поиска ошибок
void GameLogic::updateGrid()
{
    QVector<int> newGrid(m_rows * m_columns); // Временная переменная для хранения новых состояний ячеек

    // Проходим по всем ячейкам сетки
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_columns; j++) {
            // Получаем текущее состояние ячейки
            int state = getCellState(i, j);

            // Подсчитываем количество живых соседей
            int neighbors = countNeighbors(i, j);

            // Применяем правила игры
            if (state == 1 && (neighbors < 2 || neighbors > 3)) {
                // Живая ячейка умирает, если у нее меньше двух или больше трех живых соседей
                newGrid[i * m_columns + j] = 0;
            } else if (state == 0 && neighbors == 3) {
                // Мертвая ячейка оживает, если у нее ровно три живых соседа
                newGrid[i * m_columns + j] = 1;
            } else {
                // Сохраняем текущее состояние ячейки
                newGrid[i * m_columns + j] = state;
            }
        }
    }

    // Присваиваем новые состояния ячеек основной сетке
    m_grid = newGrid;
    emit gridChanged(m_grid);

    // Используем отладчик для проверки состояния сетки после обновления
    qDebug() << "Updated grid:" << m_grid;
}



// Подсчитывает количество живых соседей у ячейки по координатам
int GameLogic::countNeighbors(int row, int column)
{
    // Инициализируем счетчик нулем
    int count = 0;

    // Проходим по соседним ячейкам
    for (int i = row - 1; i <= row + 1; i++) {
        for (int j = column - 1; j <= column + 1; j++) {
            // Проверяем, что координаты в допустимом диапазоне и не равны координатам текущей ячейки
            if (i >= 0 && i < m_rows && j >= 0 && j < m_columns && !(i == row && j == column)) {
                // Прибавляем к счетчику состояние соседней ячейки
                count += getCellState(i, j);
            }
        }
    }

    // Возвращаем счетчик
    return count;
}

// Возвращает состояние ячейки по координатам
// Возвращает состояние ячейки по координатам
int GameLogic::getCellState(int row, int column)
{
    // Проверяем, что координаты в допустимом диапазоне
    if (row >= 0 && row < m_rows && column >= 0 && column < m_columns) {
        // Возвращаем значение из сетки по индексу
        return m_grid[row * m_columns + column];
    } else {
        // Возвращаем ноль в случае неверных координат
        return 0;
    }
}

// Устанавливает состояние ячейки по координатам
void GameLogic::setCellState(int row, int column, int state)
{
    // Проверяем, что координаты в допустимом диапазоне
    if (row >= 0 && row < m_rows && column >= 0 && column < m_columns) {
        // Устанавливаем значение в сетке по индексу
        m_grid[row * m_columns + column] = state;
    }
}

