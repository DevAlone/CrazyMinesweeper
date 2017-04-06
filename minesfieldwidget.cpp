#include "minesfield.h"

MinesField::MinesField(unsigned rows, unsigned cols, QWidget *parent)
    : QWidget(parent), rows(rows), cols(cols)
{
    qDebug() << sizeof(Cell) << endl;

    field = std::make_unique<MinesField>(rows, cols);

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

void MinesField::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);

    painter.drawPixmap(0, 0, pixmap);

    event->accept();
}

void MinesField::resizeEvent(QResizeEvent *event)
{
    updatePixmap();
}

void MinesField::wheelEvent(QWheelEvent *event)
{
    return QWidget::wheelEvent(event);
}

void MinesField::showEvent(QShowEvent *event)
{
    updatePixmap();
    QWidget::showEvent(event);
}

void MinesField::mousePressEvent(QMouseEvent *event)
{

}

void MinesField::mouseReleaseEvent(QMouseEvent *event)
{

}

void MinesField::updatePixmap()
{
    int width = visibleRegion().boundingRect().width();
    int height = visibleRegion().boundingRect().height();
    if(width < 1 || height < 1)
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
    for(int y = borderSize.height() / 2; y <= viewport.height; y += stepY)
        painter.drawLine(0, y, viewport.width, y);

    // vertical lines
    painter.setPen(QPen(Qt::black, borderSize.width()));
    for(int x = borderSize.width() / 2; x <= viewport.width; x+= stepX)
        painter.drawLine(x, 0, x, viewport.height);

    for(unsigned y = viewport.start_row; y < viewport.start_row + viewport.rows; y++) {
        for(unsigned x = viewport.start_col; x < viewport.start_col + viewport.cols; x++) {
            unsigned i = y * cols + x;
            if(i >= cells.size())
                continue;
            const Cell &cell = cells.at(i);

            int minesAroundCell = cell.minesAround();
            QColor color;
            switch(cell.cellState()) {
            case Cell::CellState::Closed:
                color = Qt::white;
                break;
            case Cell::CellState::Opened:
                if(minesAroundCell == 0)
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

    //        if(cell.isMine())
    //            color = Qt::red;


            painter.fillRect((x - viewport.start_col) * stepX + borderSize.width(),
                             (y - viewport.start_row) * stepY + borderSize.height(),
                             cellSize.width(),
                             cellSize.height(),
                             color);
        }
    }
    update();
}

QSize MinesField::sizeHint() const
{
//    return QSize(cols * cellSize.width(), rows * cellSize.height());
    return fieldSize;
}

void MinesField::verticalScrollPosChanged(int pos)
{
    if(pos < 0)
        return;
    viewport.start_row = pos;
    viewport.y = pos * (cellSize.height() + borderSize.height());
    updatePixmap();
}

void MinesField::horizontalScrollPosChanged(int pos)
{
    if(pos < 0)
        return;
    viewport.start_col = pos;
    viewport.x = pos * (cellSize.width() + borderSize.width());
    updatePixmap();
}

void MinesField::scrollPosChanged(int horizontal_pos, int vertical_pos)
{
    if(horizontal_pos < 0 || vertical_pos < 0)
        return;
    viewport.start_col = horizontal_pos;
    viewport.start_row = vertical_pos;
    viewport.x = horizontal_pos * (cellSize.width() + borderSize.width());
    viewport.y = vertical_pos * (cellSize.height() + borderSize.height());
    updatePixmap();
}
