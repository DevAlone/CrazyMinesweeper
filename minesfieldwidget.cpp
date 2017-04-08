#include "minesfieldwidget.h"

MinesFieldWidget::MinesFieldWidget(unsigned rows, unsigned cols, QWidget* parent)
    : QWidget(parent)
{
    settings.backgroundColor = Qt::gray;
    settings.cellColor = Qt::white;

    field = std::make_unique<MinesField>(rows, cols);

    cellSize = Size(10, 10);
    borderSize = Size(2, 2);
    fieldSize = Size(cols * (cellSize.width() + borderSize.width()),
        rows * (cellSize.height() + borderSize.height()));

    viewport.x = 0;
    viewport.y = 0;
    viewport.width = 100; //visibleRegion().boundingRect().width();
    viewport.height = 100; //visibleRegion().boundingRect().height();

    viewport.start_col = viewport.start_row = 0;
    viewport.rows = 100;
    viewport.cols = 100;

    pixmap = QPixmap(width(), height());
    updatePixmap();
}

void MinesFieldWidget::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);

    painter.drawPixmap(0, 0, pixmap);

    event->accept();
}

void MinesFieldWidget::resizeEvent(QResizeEvent*)
{
    updatePixmap();
}

void MinesFieldWidget::wheelEvent(QWheelEvent* event)
{
    return QWidget::wheelEvent(event);
}

void MinesFieldWidget::showEvent(QShowEvent* event)
{
    updatePixmap();
    QWidget::showEvent(event);
}

void MinesFieldWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->buttons() == Qt::LeftButton) {
        auto pos = event->pos();
        selectedCell.setX(double(pos.x()) / (cellSize.width() + borderSize.width()));
        selectedCell.setY(double(pos.y()) / (cellSize.height() + borderSize.height()));
        qDebug() << event->pos();
        qDebug() << selectedCell.x() << selectedCell.y();
        highlightCell(selectedCell);
    }
}

void MinesFieldWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        auto pos = event->pos();
        Point cell(double(pos.x()) / (cellSize.width() + borderSize.width()),
            double(pos.y()) / (cellSize.height() + borderSize.height()));
        unhighlightCell(selectedCell);
        qDebug() << cell.x() << cell.y() << ":" << selectedCell.x() << selectedCell.y();
        if (cell != selectedCell)
            return;
        field->tryToOpenCell(selectedCell);
        updatePixmap();
    }
}

void MinesFieldWidget::highlightCell(Point cell, bool state)
{
    cell.setX(cell.x() - viewport.start_col);
    cell.setY(cell.y() - viewport.start_row);
    if (cell.x() < 0 || cell.y() < 0)
        return;
    QPainter painter(&pixmap);
    int x = cell.x() * (cellSize.width() + borderSize.width()) + borderSize.width();
    int y = cell.y() * (cellSize.height() + borderSize.height()) + borderSize.height();
    painter.fillRect(x,
        y,
        cellSize.width(),
        cellSize.height(),
        state ? settings.cellColor : settings.backgroundColor);
    update();
}

void MinesFieldWidget::unhighlightCell(Point cell)
{
    highlightCell(cell, true);
}

void MinesFieldWidget::updatePixmap()
{
    int width = visibleRegion().boundingRect().width();
    int height = visibleRegion().boundingRect().height();
    if (width < 1 || height < 1)
        return;
    viewport.width = width;
    viewport.height = height;
    viewport.cols = width / (cellSize.width() + borderSize.width()) + 1;
    viewport.rows = height / (cellSize.height() + borderSize.height()) + 1;
    pixmap = QPixmap(viewport.width, viewport.height);

    pixmap.fill(Qt::gray);
    QPainter painter(&pixmap);
    // to do: optimize this
    int stepX = cellSize.width() + borderSize.width();
    int stepY = cellSize.height() + borderSize.height();

    // horizontal lines
    painter.setPen(QPen(Qt::black, borderSize.width()));
    for (unsigned y = borderSize.height() / 2; y <= viewport.height; y += stepY)
        painter.drawLine(0, y, viewport.width, y);

    // vertical lines
    painter.setPen(QPen(Qt::black, borderSize.width()));
    for (unsigned x = borderSize.width() / 2; x <= viewport.width; x += stepX)
        painter.drawLine(x, 0, x, viewport.height);

    for (unsigned y = viewport.start_row;
         y < viewport.start_row + viewport.rows && y < field->getRows();
         y++) {
        for (unsigned x = viewport.start_col;
             x < viewport.start_col + viewport.cols && x < field->getCols();
             x++) {
            unsigned i = field->getCellIndex(Point(x, y));
            if (!field->isCellIndexValid(i))
                continue;

            auto& cells = field->getCells();
            const Cell& cell = cells.at(i);

            int minesAroundCell = cell.minesAround();
            QColor color;
            switch (cell.cellState()) {
            case Cell::CellState::Closed:
                color = Qt::white;
                break;
            case Cell::CellState::Opened:
                if (minesAroundCell == 0)
                    color = Qt::gray;
                else
                    color = QColor(0, 100.0 + 155.0 * (8 - minesAroundCell) / 8.0, 0);

                break;
            case Cell::CellState::MarkedAsBomb:
                color = Qt::yellow;
                break;
            default:
                break;
            }

            if (cell.isMine())
                color = Qt::red;

            painter.fillRect((x - viewport.start_col) * stepX + borderSize.width(),
                (y - viewport.start_row) * stepY + borderSize.height(),
                cellSize.width(),
                cellSize.height(),
                color);
        }
    }
    update();
}

QSize MinesFieldWidget::sizeHint() const
{
    //    return QSize(cols * cellSize.width(), rows * cellSize.height());
    return QSize(fieldSize.width(), fieldSize.height());
}

void MinesFieldWidget::verticalScrollPosChanged(int pos)
{
    if (pos < 0)
        return;
    viewport.start_row = pos;
    viewport.y = pos * (cellSize.height() + borderSize.height());
    updatePixmap();
}

void MinesFieldWidget::horizontalScrollPosChanged(int pos)
{
    if (pos < 0)
        return;
    viewport.start_col = pos;
    viewport.x = pos * (cellSize.width() + borderSize.width());
    updatePixmap();
}

void MinesFieldWidget::scrollPosChanged(int horizontal_pos, int vertical_pos)
{
    if (horizontal_pos < 0 || vertical_pos < 0)
        return;
    viewport.start_col = horizontal_pos;
    viewport.start_row = vertical_pos;
    viewport.x = horizontal_pos * (cellSize.width() + borderSize.width());
    viewport.y = vertical_pos * (cellSize.height() + borderSize.height());
    updatePixmap();
}
