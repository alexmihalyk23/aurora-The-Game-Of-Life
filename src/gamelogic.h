// GameLogic.h
#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QObject>
#include <QTimer>
#include <QVector>
#include <QVariantList>

class GameLogic : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int rows READ rows WRITE setRows NOTIFY rowsChanged)
    Q_PROPERTY(int columns READ columns WRITE setColumns NOTIFY columnsChanged)
    Q_PROPERTY(QVector<int> grid READ grid WRITE setGrid NOTIFY gridChanged)
    Q_PROPERTY(QVariantList gridList READ gridList NOTIFY gridChanged)

public:
    explicit GameLogic(QObject *parent = nullptr);

    int rows() const;
    void setRows(int rows);

    int columns() const;
    void setColumns(int columns);

    QVector<int> grid() const;
    void setGrid(const QVector<int> &grid);

    QVariantList gridList() const;

signals:
    void rowsChanged(int rows);
    void columnsChanged(int columns);
    void gridChanged(const QVector<int> &grid);

public slots:
    void start();
    void stop();
    void reset();
    void toggleCell(int index);
    void updateGrid();

private:
    int m_rows;
    int m_columns;
    QVector<int> m_grid;
    QTimer *m_timer;

    int countNeighbors(int row, int column);
    int getCellState(int row, int column);
    void setCellState(int row, int column, int state);
};

#endif // GAMELOGIC_H
