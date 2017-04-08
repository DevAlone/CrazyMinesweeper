#ifndef POINT_H
#define POINT_H

class Point {
public:
    Point(int x = 0, int y = 0);

    int x() const;
    void setX(int x);

    int y() const;
    void setY(int y);

private:
    int _x, _y;
};

#endif // POINT_H
