#ifndef SIZE_H
#define SIZE_H


class Size
{
public:
    Size(int x = 0, int y = 0);

    int width() const;
    void setWidth(int width);

    int height() const;
    void setHeight(int height);

private:
    int _width;
    int _height;
};

#endif // SIZE_H
