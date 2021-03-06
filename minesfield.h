#ifndef MINESFIELD_H
#define MINESFIELD_H

#include "cell.h"
#include "point.h"

#include <QObject>
#include <atomic>
#include <thread>
#include <vector>

class MinesField : public QObject {
    Q_OBJECT
public:
    MinesField(unsigned rows, unsigned cols, unsigned char minesPercents);
    virtual ~MinesField();

    void lazyOpenCells(const Point& point);
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
    bool isCellIndexValid(long index) const
    {
        return index >= 0 && index < long(cells.size());
    }
    bool isCellPointValid(const Point& point) const
    {
        return point.x() >= 0 && point.x() < long(cols)
            && point.y() >= 0 && point.y() < long(rows);
    }
    inline std::vector<Point> getAroundCells(const Point& cell) const;

    bool getCreated() const;

    unsigned getMarkedCells() const;

signals:
    void userLost();
    void userWon();
    void markedCellsCountChanged();
public slots:

private:
    std::vector<Cell> cells;
    unsigned minesCount = 0;
    int minesLeft = 0;
    unsigned markedCells = 0;
    unsigned rows;
    unsigned cols;
    double minesPercents = 0;

    bool lost = false;
    bool won = false;
    void loseGame();

    bool isUserWon();
    void checkForWin();

    std::atomic<bool> created;
};

#endif // MINESFIELD_H
