#include "minesfield.h"

#include <QDebug>
#include <algorithm>
#include <queue>
#include <set>

MinesField::MinesField(unsigned rows, unsigned cols)
    : rows(rows)
    , cols(cols)
{
    minesPercents = 0.2;

    cells = std::vector<Cell>(rows * cols);
    minesCount = rows * cols * minesPercents;

    // генерим мины в первых minesCount элементах массива
    for (unsigned i = 0; i < minesCount; i++) {
        cells.at(i).setMine();
    }
    // пермешиваем
    std::random_shuffle(cells.begin(), cells.end());

    for (unsigned i = 0; i < rows * cols; i++) {
        if (!cells.at(i).isMine())
            continue;

        unsigned y = i / cols;
        unsigned x = i - y * cols;
        // левая и правая
        if (x > 0)
            cells.at(i - 1).setMinesAround(cells.at(i - 1).minesAround() + 1);
        if (x < cols - 1)
            cells.at(i + 1).setMinesAround(cells.at(i + 1).minesAround() + 1);
        // верхняя и нижняя ячейки
        if (y > 0)
            cells.at(i - cols).setMinesAround(cells.at(i - cols).minesAround() + 1);
        if (y < rows - 1)
            cells.at(i + cols).setMinesAround(cells.at(i + cols).minesAround() + 1);
        // диагональные
        if (x > 0 && y > 0)
            cells.at(i - cols - 1).setMinesAround(cells.at(i - cols - 1).minesAround() + 1);
        if (x < cols - 1 && y > 0)
            cells.at(i - cols + 1).setMinesAround(cells.at(i - cols + 1).minesAround() + 1);

        if (x > 0 && y < rows - 1)
            cells.at(i + cols - 1).setMinesAround(cells.at(i + cols - 1).minesAround() + 1);
        if (x < cols - 1 && y < rows - 1)
            cells.at(i + cols + 1).setMinesAround(cells.at(i + cols + 1).minesAround() + 1);
    }

    //    for(unsigned i = 0; i < rows * cols; i++) {
    //        if(!cells.at(i).isMine())
    //            cells.at(i).setCellState(static_cast<unsigned char>(Cell::CellState::Opened));

    ////        int minesAround = cells.at(i).minesAround();
    ////        if(minesAround > 3)
    ////            qDebug() << minesAround;
    //    }
}

void MinesField::tryToOpenCell(const Point& point)
{
    unsigned cellIndex = getCellIndex(point);

    if (!isCellIndexValid(cellIndex))
        return;
    Cell* cell = &cells.at(cellIndex);

    cell->setCellState(Cell::CellState::Opened);
    if (cell->isMine()) {
        // TODO: lose game
    } else {
        //        cell.setCellState(Cell::CellState::Opened);
        std::queue<unsigned> cellsQueue;
        std::set<unsigned> usedCells;
        cellsQueue.push(cellIndex);
        usedCells.insert(cellIndex);

        qDebug() << "start opening...";
        while (!cellsQueue.empty()) {
            cellIndex = cellsQueue.front();
            cellsQueue.pop();
            cell = &cells.at(cellIndex);
            qDebug() << "cell " << cellIndex << "(" << getCellPoint(cellIndex).x() << "," << getCellPoint(cellIndex).y() << ")";
            if (!cell->isMine()) {
                cell->setCellState(Cell::CellState::Opened);
                if (cell->minesAround() == 0) {
                    qDebug() << "minesAround == 0";
                    auto aroundCells = getAroundCells(getCellPoint(cellIndex));

                    for (auto cell : aroundCells) {
                        unsigned index = getCellIndex(cell);
                        qDebug() << "cell around" << index << "(" << cell.x() << "," << cell.y() << ")";
                        if (usedCells.find(index) == usedCells.end()) {
                            qDebug() << "push this";
                            cellsQueue.push(index);
                            usedCells.insert(index);
                        }
                    }
                }
            }
            qDebug() << "\n\n";
        }
    }
    //    qDebug() << "!";
    //    for (auto val : result)
    //        qDebug() << val.x() << val.y();
    //    qDebug() << "?";
}

unsigned MinesField::getMinesCount() const
{
    return minesCount;
}

unsigned MinesField::getRows() const
{
    return rows;
}

unsigned MinesField::getCols() const
{
    return cols;
}

double MinesField::getMinesPercents() const
{
    return minesPercents;
}

std::vector<Cell>& MinesField::getCells()
{
    return cells;
}

unsigned MinesField::getCellIndex(const Point& cell) const
{
    return cell.y() * cols + cell.x();
}

Point MinesField::getCellPoint(unsigned index) const
{
    int y = index / cols;
    int x = index - y * cols;
    return Point(x, y);
}

bool MinesField::isCellIndexValid(unsigned index) const
{
    return index >= 0 && index < cells.size();
}

std::vector<Point> MinesField::getAroundCells(const Point& cell) const
{
    int x = cell.x();
    int y = cell.y();

    std::vector<Point> result;
    result.reserve(8);
    if (x > 0 && y > 0)
        result.push_back(Point(x - 1, y - 1));
    if (y > 0)
        result.push_back(Point(x, y - 1));
    if (x < cols - 1 && y > 0)
        result.push_back(Point(x + 1, y - 1));
    if (x < cols - 1)
        result.push_back(Point(x + 1, y));
    if (x < cols - 1 && y < rows - 1)
        result.push_back(Point(x + 1, y + 1));
    if (y < rows - 1)
        result.push_back(Point(x, y + 1));
    if (x > 0 && y < rows - 1)
        result.push_back(Point(x - 1, y + 1));
    if (x > 0)
        result.push_back(Point(x - 1, y));

    return result;
}
