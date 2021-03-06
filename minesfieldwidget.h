#ifndef MINESFIELDWIDGET_H
#define MINESFIELDWIDGET_H

#include "minesfield.h"
#include "minesfieldwidgetsettings.h"
#include "minesfieldwidgetupdaterthread.h"
#include "point.h"

#include <memory>

#include <QWidget>
#include <QtWidgets>

struct Viewport {
    long long x, y;
    long width, height;
    long start_col, start_row;
    long cols, rows;
};

class MinesFieldWidgetUpdaterThread;

class MinesFieldWidget : public QWidget {
    Q_OBJECT
public:
    friend class MinesFieldWidgetUpdaterThread;
    explicit MinesFieldWidget(QWidget* parent = 0);
    virtual ~MinesFieldWidget();

    void updatePixmap();

    QSize sizeHint() const;

    std::shared_ptr<MinesField> getField() const;
    void setField(const std::shared_ptr<MinesField>& value);

    QSize getCellSize() const;
    void setCellSize(const QSize& value);

    QSize getBorderSize() const;
    void setBorderSize(const QSize& value);

    MinesFieldWidgetSettings& getSettings();
    void setSettings(const MinesFieldWidgetSettings& value);

    Point getCellByMousePoint(const QPoint& mousePoint);
    Point convertCellPointToAbsolute(const Point& point);
    Viewport getViewport() const;

signals:

public slots:
    void verticalScrollPosChanged(int pos);
    void horizontalScrollPosChanged(int pos);
    void scrollPosChanged(int horizontal_pos, int vertical_pos);

protected:
    void paintEvent(QPaintEvent* event);
    void resizeEvent(QResizeEvent* event);
    void wheelEvent(QWheelEvent* event);
    void showEvent(QShowEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

private slots:
    void updatingThreadFinished();

private:
    std::shared_ptr<MinesField> field;
    MinesFieldWidgetSettings settings;

    void highlightCell(Point cellPoint, QColor color = Qt::gray);
    void unhighlightCell(Point cellPoint);
    QColor getCellColor(Cell::CellState cellState, int minesAroundCell);

    QPixmap pixmap;
    Viewport viewport;

    QSize cellSize;
    QSize borderSize;

    QSize fieldSize;
    Point selectedCell;
    QPoint mousePos;
    QSize zoomArea = QSize(7, 7);

    MinesFieldWidgetUpdaterThread* thread = 0;
    bool isUpdatingQueued;
    QMutex updatingMutex;
};

#endif // MINESFIELDWIDGET_H
