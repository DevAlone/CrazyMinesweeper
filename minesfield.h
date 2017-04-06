#ifndef MINESFIELD_H
#define MINESFIELD_H

#include "size.h"

#include <vector>

class MinesField
{
public:
    MinesField(unsigned rows, unsigned cols);

private:
    class Cell
    {
    public:
        enum class CellState : unsigned char { Closed, Opened, MarkedAsBomb, MarkedAsQuestion };
        inline bool isMine() const
        {
            return data & 1;
        }
        inline unsigned char minesAround() const
        {
            return data >> 1 & 0b1111;
        }
        inline CellState cellState() const
        {
            return CellState(data >> 5 & 0b11);
        }
        inline void setMine(bool value = true)
        {
            if(value)
                data |= 1;
            else
                data = data >> 1 << 1;
        }
        inline void setMinesAround(unsigned char value)
        {
            data &= ~0b11110;
            value <<= 1;
            data |= value;
        }
        inline void setCellState(unsigned char value)
        {
            data &= ~0b1100000;
            value <<= 5;
            data |= value;
        }

    private:
        // CellState state; // 2 bits
        // char minesAround; // 4 bits
        // bool mine; // 1 bit
        // reserved cellState minesAround isMine
        // 0        00         0000         0
        unsigned char data = 0;
    };
    std::vector<Cell> cells;
    unsigned minesCount;
    unsigned rows;
    unsigned cols;
    double minesPercents;

    Size cellSize;
    Size borderSize;

    Size fieldSize;
};

#endif // MINESFIELD_H
