#include "size.h"

Size::Size(int x, int y)
    : x(x), y(y)
{

}

int Size::width() const
{
    return _width;
}

void Size::setWidth(int width)
{
    _width = width;
}

int Size::height() const
{
    return _height;
}

void Size::setHeight(int height)
{
    _height = height;
}

