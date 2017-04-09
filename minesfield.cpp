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
    minesLeft = minesCount = rows * cols * minesPercents;

    // генерим мины в первых minesCount элементах массива
    for (unsigned i = 0; i < minesCount; i++) {
        cells.at(i).setMine();
    }

    // пермешиваем
    std::random_shuffle(cells.begin(), cells.end());

    // расставляем количество мин
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

    bool first_cell_opened = false;
    for (int i = cells.size() / 2; i < cells.size() && !first_cell_opened; i++) {
        if (!cells.at(i).isMine() && cells.at(i).minesAround() == 0) {
            first_cell_opened = true;
            tryToOpenCell(getCellPoint(i));
            break;
        }
    }
    for (int i = cells.size() / 2; i >= 0 && !first_cell_opened; i--) {
        if (!cells.at(i).isMine()) {
            tryToOpenCell(getCellPoint(i));
            break;
        }
    }
}

void MinesField::tryToOpenCell(const Point& point)
{
    unsigned cellIndex = getCellIndex(point);

    if (!isCellIndexValid(cellIndex))
        return;
    Cell* cell = &cells.at(cellIndex);

    if (cell->cellState() != Cell::CellState::Closed)
        return;

    if (cell->isMine()) {
        lost = true;
        won = false;
        emit userLost();
    } else {
        std::queue<unsigned> cellsQueue;
        std::set<unsigned> usedCells;
        cellsQueue.push(cellIndex);
        usedCells.insert(cellIndex);

        while (!cellsQueue.empty()) {
            cellIndex = cellsQueue.front();
            cellsQueue.pop();
            cell = &cells.at(cellIndex);
            if (!cell->isMine() && cell->cellState() == Cell::CellState::Closed) {
                cell->setCellState(Cell::CellState::Opened);
                if (cell->minesAround() == 0) {
                    auto aroundCells = getAroundCells(getCellPoint(cellIndex));

                    for (auto cell : aroundCells) {
                        unsigned index = getCellIndex(cell);
                        if (usedCells.find(index) == usedCells.end()) {
                            cellsQueue.push(index);
                            usedCells.insert(index);
                        }
                    }
                }
            }
        }
    }
    //    qDebug() << "!";
    //    for (auto val : result)
    //        qDebug() << val.x() << val.y();
    //    qDebug() << "?";
}

void MinesField::markCell(const Point& point, Cell::CellState markAs)
{
    unsigned index = getCellIndex(point);
    if (!isCellIndexValid(index))
        return;

    Cell& cell = cells.at(index);
    if (cell.cellState() != Cell::CellState::Closed
        && cell.cellState() != Cell::CellState::MarkedAsBomb
        && cell.cellState() != Cell::CellState::MarkedAsQuestion)
        return;
    switch (markAs) {
    case Cell::CellState::MarkedAsBomb:
        cell.setCellState(Cell::CellState::MarkedAsBomb);
        minesLeft--;
        break;
    case Cell::CellState::MarkedAsQuestion:
        cell.setCellState(Cell::CellState::MarkedAsQuestion);
        minesLeft++;
        break;
    }
}

void MinesField::unmarkCell(const Point& point)
{
    unsigned index = getCellIndex(point);
    if (!isCellIndexValid(index))
        return;

    Cell& cell = cells.at(index);
    if (!(cell.cellState() == Cell::CellState::MarkedAsBomb || cell.cellState() == Cell::CellState::MarkedAsQuestion))
        return;

    cell.setCellState(Cell::CellState::Closed);
    minesLeft++;
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

Cell* MinesField::getCell(const Point& cell)
{
    return getCell(getCellIndex(cell));
}

Cell* MinesField::getCell(unsigned index)
{
    if (!isCellIndexValid(index))
        throw std::out_of_range("index out of range");

    return &cells.at(index);
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
