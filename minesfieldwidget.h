#ifndef MINESFIELDWIDGET_H
#define MINESFIELDWIDGET_H

#include "minesfield.h"

#include <memory>

#include <QWidget>
#include <QtWidgets>

// TODO: split MinesField with game logic and MinesFieldWidget
class MinesFieldWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MinesFieldWidget(unsigned width, unsigned height, QWidget *parent = 0);

    void updatePixmap();

    QSize sizeHint() const;

signals:

public slots:
    void verticalScrollPosChanged(int pos);
    void horizontalScrollPosChanged(int pos);
    void scrollPosChanged(int horizontal_pos, int vertical_pos);

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void wheelEvent(QWheelEvent *event);
    void showEvent(QShowEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);


private:
    std::unique_ptr<MinesField> field;
    QPixmap pixmap;

    struct Viewport
    {
        int x, y;
        unsigned width, height;
        unsigned start_col, start_row;
        unsigned cols, rows;
    };

    Viewport viewport;
};

#endif // MINESFIELDWIDGET_H
