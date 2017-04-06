#include "minesfield.h"

#include <algorithm>

MinesField::MinesField(unsigned rows, unsigned cols)
    : rows(rows), cols(cols)
{
    minesPercents = 0.2;
    cellSize = Size(10, 10);
    borderSize = Size(2, 2);
    fieldSize = Size(cols * (cellSize.width() + borderSize.width()),
                      rows * (cellSize.height() + borderSize.height()));


    cells = std::vector<Cell>(rows * cols);
    minesCount = rows * cols * minesPercents;

    // генерим мины в первых minesCount элементах массива
    for(unsigned i = 0; i < minesCount; i++) {
        cells.at(i).setMine();
    }
    // пермешиваем
    std::random_shuffle(cells.begin(), cells.end());

    for(unsigned i = 0; i < rows * cols; i++) {
        if (!cells.at(i).isMine())
            continue;

        unsigned y = i / cols;
        unsigned x = i - y * cols;
        // левая и правая
        if(x > 0)
            cells.at(i - 1).setMinesAround(cells.at(i - 1).minesAround() + 1);
        if(x < cols - 1)
            cells.at(i + 1).setMinesAround(cells.at(i + 1).minesAround() + 1);
        // верхняя и нижняя ячейки
        if(y > 0)
            cells.at(i - cols).setMinesAround(cells.at(i - cols).minesAround() + 1);
        if(y < rows - 1)
            cells.at(i + cols).setMinesAround(cells.at(i + cols).minesAround() + 1);
        // диагональные
        if(x > 0 && y > 0)
            cells.at(i - cols - 1).setMinesAround(cells.at(i - cols - 1).minesAround() + 1);
        if(x < cols - 1 && y > 0)
            cells.at(i - cols + 1).setMinesAround(cells.at(i - cols + 1).minesAround() + 1);

        if(x > 0 && y < rows - 1)
            cells.at(i + cols - 1).setMinesAround(cells.at(i + cols - 1).minesAround() + 1);
        if(x < cols - 1 && y < rows - 1)
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

