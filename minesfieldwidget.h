#ifndef MINESFIELDWIDGET_H
#define MINESFIELDWIDGET_H

#include "minesfield.h"
#include "minesfieldwidgetsettings.h"
#include "point.h"

#include <memory>

#include <QWidget>
#include <QtWidgets>

class MinesFieldWidget : public QWidget {
    Q_OBJECT
public:
    explicit MinesFieldWidget(QWidget* parent = 0);

    void updatePixmap();

    QSize sizeHint() const;

signals:

public slots:
    void verticalScrollPosChanged(int pos);
    void horizontalScrollPosChanged(int pos);
    void scrollPosChanged(int horizontal_pos, int vertical_pos);
    void userLose();

protected:
    void paintEvent(QPaintEvent* event);
    void resizeEvent(QResizeEvent* event);
    void wheelEvent(QWheelEvent* event);
    void showEvent(QShowEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent* event);

private:
    MinesFieldWidgetSettings settings;
    void highlightCell(Point cellPoint, QColor color = Qt::gray);
    void unhighlightCell(Point cellPoint);

    std::unique_ptr<MinesField> field;
    QPixmap pixmap;

    struct Viewport {
        int x, y;
        unsigned width, height;
        unsigned start_col, start_row;
        unsigned cols, rows;
    };

    Viewport viewport;

    Size cellSize;
    Size borderSize;

    Size fieldSize;
    Point selectedCell;
    QPoint mousePos;
    QSize zoomArea = QSize(7, 7);

    Point getCellByMousePoint(const QPoint& mousePoint);
    Point convertCellPointToAbsolute(const Point& point);
};

#endif // MINESFIELDWIDGET_H
