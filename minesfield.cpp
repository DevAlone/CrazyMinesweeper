#include "minesfield.h"

#include <QDebug>
#include <QTime>
#include <algorithm>
#include <ctime>
#include <queue>
#include <set>

MinesField::MinesField(unsigned rows, unsigned cols, unsigned char mp)
    : rows(rows)
    , cols(cols)
{
    created = false;
    if (minesPercents > 100)
        minesPercents = 100;

    minesPercents = double(mp) / 100.0;
    minesLeft = minesCount = rows * cols * minesPercents;
    srand(time(0));

    cells = std::vector<Cell>(this->rows * this->cols);
    // генерим мины в первых minesCount элементах массива
    for (unsigned i = 0; i < minesCount; i++) {
        cells.at(i).setMine();
    }
    // пермешиваем
    std::random_shuffle(cells.begin(), cells.end());

    // расставляем количество мин
    for (unsigned i = 0; i < this->rows * this->cols; i++) {
        if (!cells.at(i).isMine())
            continue;

        unsigned y = i / this->cols;
        unsigned x = i - y * this->cols;
        // левая и правая
        if (x > 0)
            cells.at(i - 1).setMinesAround(cells.at(i - 1).minesAround() + 1);
        if (x < this->cols - 1)
            cells.at(i + 1).setMinesAround(cells.at(i + 1).minesAround() + 1);
        // верхняя и нижняя ячейки
        if (y > 0)
            cells.at(i - this->cols).setMinesAround(cells.at(i - this->cols).minesAround() + 1);
        if (y < this->rows - 1)
            cells.at(i + this->cols).setMinesAround(cells.at(i + this->cols).minesAround() + 1);
        // диагональные
        if (x > 0 && y > 0)
            cells.at(i - this->cols - 1).setMinesAround(cells.at(i - this->cols - 1).minesAround() + 1);
        if (x < this->cols - 1 && y > 0)
            cells.at(i - this->cols + 1).setMinesAround(cells.at(i - this->cols + 1).minesAround() + 1);

        if (x > 0 && y < this->rows - 1)
            cells.at(i + this->cols - 1).setMinesAround(cells.at(i + this->cols - 1).minesAround() + 1);
        if (x < this->cols - 1 && y < this->rows - 1)
            cells.at(i + this->cols + 1).setMinesAround(cells.at(i + this->cols + 1).minesAround() + 1);
    }

    bool first_cell_opened = false;
    for (unsigned i = cells.size() / 2; i < cells.size() && !first_cell_opened; i++) {
        if (!cells.at(i).isMine() && cells.at(i).minesAround() == 0) {
            first_cell_opened = true;
            tryToOpenCell(getCellPoint(i));
            break;
        }
    }
    for (long i = cells.size() / 2; i >= 0 && !first_cell_opened; i--) {
        if (!cells.at(i).isMine()) {
            tryToOpenCell(getCellPoint(i));
            break;
        }
    }

    created = true;
}

MinesField::~MinesField()
{
}

void MinesField::lazyOpenCells(const Point& point)
{
    if (!created)
        return;

    checkForWin();

    if (lost || won)
        return;
    if (!isCellPointValid(point))
        return;

    Cell* cell;
    try {
        cell = getCell(point);
    } catch (const std::out_of_range& ex) {
        return;
    }
    if (cell->cellState() != Cell::CellState::Opened)
        return;

    auto minesAround = getAroundCells(point);
    unsigned markedAsBombCount = 0;
    for (auto mine : minesAround) {
        Cell* currentCell;
        try {
            currentCell = getCell(mine);
        } catch (const std::out_of_range& ex) {
            return;
        }
        if (currentCell->cellState() == Cell::CellState::MarkedAsBomb) {
            markedAsBombCount++;
            if (!currentCell->isMine()) {
                loseGame();
                return;
            }
        }
    }
    if (markedAsBombCount != cell->minesAround())
        return;

    for (auto mine : minesAround) {
        tryToOpenCell(mine);
    }

    checkForWin();
}

void MinesField::loseGame()
{
    if (!created)
        return;

    lost = true;
    won = false;
    emit userLost();
}

bool MinesField::isUserWon()
{
    if (!created)
        return false;

    if (minesLeft != 0)
        return false;
    // TODO: optimize this
    for (const auto& cell : cells) {
        if (cell.isMine()) {
            if (cell.cellState() != Cell::CellState::MarkedAsBomb)
                return false;
        } else if (cell.cellState() != Cell::CellState::Opened)
            return false;
    }
    return true;
}

void MinesField::checkForWin()
{
    if (!created)
        return;

    if (minesLeft == 0) {
        if (!won && (won = isUserWon()))
            emit userWon();
    }
}

bool MinesField::getCreated() const
{
    return created;
}

unsigned MinesField::getMarkedCells() const
{
    return markedCells;
}

void MinesField::tryToOpenCell(const Point& point)
{
    // да, костыль, но перемещать игровую логику в отдельный поток дольше
    QTime exec_time;
    exec_time.start();
    if (!created)
        return;

    checkForWin();

    if (lost || won)
        return;
    if (!isCellPointValid(point))
        return;

    unsigned cellIndex = getCellIndex(point);

    if (!isCellIndexValid(cellIndex))
        return;
    Cell* cell = &cells.at(cellIndex);

    if (cell->cellState() != Cell::CellState::Closed)
        return;

    if (cell->isMine()) {
        loseGame();
        return;
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
            if (exec_time.elapsed() > 3000)
                break;
        }
    }
    checkForWin();
}

void MinesField::markCell(const Point& point, Cell::CellState markAs)
{
    if (!created)
        return;

    checkForWin();

    if (lost || won)
        return;
    if (!isCellPointValid(point))
        return;

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

        if (cell.isMine())
            minesLeft--;
        markedCells++;
        emit markedCellsCountChanged();
        break;
    case Cell::CellState::MarkedAsQuestion:
        cell.setCellState(Cell::CellState::MarkedAsQuestion);
        if (cell.isMine())
            minesLeft++;
        markedCells--;
        emit markedCellsCountChanged();
        break;
    default:
        break;
    }

    checkForWin();
}

void MinesField::unmarkCell(const Point& point)
{
    if (!created)
        return;

    checkForWin();
    if (lost || won)
        return;
    if (!isCellPointValid(point))
        return;

    unsigned index = getCellIndex(point);
    if (!isCellIndexValid(index))
        return;

    Cell& cell = cells.at(index);
    if (!(cell.cellState() == Cell::CellState::MarkedAsBomb || cell.cellState() == Cell::CellState::MarkedAsQuestion))
        return;

    if (cell.cellState() == Cell::CellState::MarkedAsBomb) {
        minesLeft++;
        markedCells--;
        emit markedCellsCountChanged();
    }

    cell.setCellState(Cell::CellState::Closed);
    checkForWin();
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
    unsigned x = cell.x();
    unsigned y = cell.y();

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
