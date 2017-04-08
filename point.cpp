#include "point.h"

Point::Point(int x, int y)
    : _x(x)
    , _y(y)
{
}

int Point::x() const
{
    return _x;
}

void Point::setX(int x)
{
    _x = x;
}

int Point::y() const
{
    return _y;
}

void Point::setY(int y)
{
    _y = y;
}
