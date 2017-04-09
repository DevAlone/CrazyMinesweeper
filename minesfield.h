#ifndef MINESFIELD_H
#define MINESFIELD_H

#include "cell.h"
#include "point.h"
#include "size.h"

#include <QObject>
#include <vector>

class MinesField : public QObject {
    Q_OBJECT
public:
    MinesField(unsigned rows, unsigned cols);

    void tryToOpenCell(const Point& point);
    void markCell(const Point& point, Cell::CellState markAs = Cell::CellState::MarkedAsBomb);
    void unmarkCell(const Point& point);

    unsigned getMinesCount() const;

    unsigned getRows() const;

    unsigned getCols() const;

    double getMinesPercents() const;

    std::vector<Cell>& getCells();

    unsigned getCellIndex(const Point& cell) const;
    Point getCellPoint(unsigned index) const;
    Cell* getCell(const Point& cell);
    Cell* getCell(unsigned index);
    bool isCellIndexValid(unsigned index) const
    {
        return index >= 0 && index < cells.size();
    }
    inline std::vector<Point> getAroundCells(const Point& cell) const;

signals:
    void userLost();
    void userWon();
public slots:

private:
    std::vector<Cell> cells;
    unsigned minesCount = 0;
    int minesLeft = 0;
    unsigned rows;
    unsigned cols;
    double minesPercents = 0;

    bool lost = false;
    bool won = false;
};

#endif // MINESFIELD_H
