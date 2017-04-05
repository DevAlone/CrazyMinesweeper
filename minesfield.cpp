#include "minesfield.h"

MinesField::MinesField(unsigned rows, unsigned cols, QWidget *parent)
    : QWidget(parent), rows(rows), cols(cols)
{
    qDebug() << sizeof(Cell) << endl;
    minesPercents = 0.2;
    cellSize = QSize(10, 10);
    borderSize = QSize(2, 2);

    pixmap = QPixmap(width(), height());
    viewport = visibleRegion().boundingRect();


    cells = std::vector<Cell>(rows * cols);
    minesCount = rows * cols * minesPercents;

    // генерим мины в первых minesCount элементах массива
    for(unsigned i = 0; i < minesCount; i++) {
        cells.at(i).setMine();
    }
    // пермешиваем
    std::random_shuffle(cells.begin(), cells.end());

    for(unsigned i = 0; i < rows * cols; i++) {
        if (!cells.at(i).isMine())
            continue;

        unsigned y = i / cols;
        unsigned x = i - y * cols;
        // левая и правая
        if(x > 0)
            cells.at(i - 1).setMinesAround(cells.at(i - 1).minesAround() + 1);
        if(x < cols - 1)
            cells.at(i + 1).setMinesAround(cells.at(i + 1).minesAround() + 1);
        // верхняя и нижняя ячейки
        if(y > 0)
            cells.at(i - cols).setMinesAround(cells.at(i - cols).minesAround() + 1);
        if(y < rows - 1)
            cells.at(i + cols).setMinesAround(cells.at(i + cols).minesAround() + 1);
        // диагональные
        if(x > 0 && y > 0)
            cells.at(i - cols - 1).setMinesAround(cells.at(i - cols - 1).minesAround() + 1);
        if(x < cols - 1 && y > 0)
            cells.at(i - cols + 1).setMinesAround(cells.at(i - cols + 1).minesAround() + 1);

        if(x > 0 && y < rows - 1)
            cells.at(i + cols - 1).setMinesAround(cells.at(i + cols - 1).minesAround() + 1);
        if(x < cols - 1 && y < rows - 1)
            cells.at(i + cols + 1).setMinesAround(cells.at(i + cols + 1).minesAround() + 1);
    }

    for(unsigned i = 0; i < rows * cols; i++) {
        if(!cells.at(i).isMine())
            cells.at(i).setCellState(static_cast<unsigned char>(Cell::CellState::Opened));

//        int minesAround = cells.at(i).minesAround();
//        if(minesAround > 3)
//            qDebug() << minesAround;
    }

    updatePixmap();
}

void MinesField::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);

    painter.drawPixmap(0, 0, pixmap);

    event->accept();

    qDebug() << viewport.x() << viewport.y() << " : " << viewport.width() << viewport.height();
}

void MinesField::resizeEvent(QResizeEvent *event)
{
    viewport.setWidth(visibleRegion().boundingRect().width());
    viewport.setHeight(visibleRegion().boundingRect().height());
//    int width = visibleRegion().boundingRect().width();
//    int height = visibleRegion().boundingRect().height();
    if(viewport.width() < 1 || viewport.height() < 1)
        return;
    pixmap = QPixmap(viewport.width(), viewport.height());
    updatePixmap();
    qDebug() << viewport.x() << viewport.y() << " : " << viewport.width() << viewport.height();
}

void MinesField::wheelEvent(QWheelEvent *event)
{
    int numDegrees = event->delta() / 8;
    int numSteps = numDegrees / 15;

    if(event->orientation() == Qt::Vertical) {
        // vertical
        viewport.setY(viewport.y() + 10);
    } else {
        // horizontal
        viewport.setX(viewport.x() + 10);
    }
    qDebug() << viewport.x() << viewport.y() << " : " << viewport.width() << viewport.height();
}

void MinesField::updatePixmap()
{
    QPainter painter(&pixmap);
    // to do: optimize this
    int fieldWidth = cols * (cellSize.width() + borderSize.width());
    int fieldHeight = rows * (cellSize.height() + borderSize.height());
    int stepX = cellSize.width() + borderSize.width();
    int stepY = cellSize.height() + borderSize.height();

    // horizontal lines
    painter.setPen(QPen(Qt::black, borderSize.width()));
    for(int y = borderSize.height() / 2; y <= fieldHeight; y += stepY)
        painter.drawLine(0, y, fieldWidth, y);

    // vertical lines
    painter.setPen(QPen(Qt::black, borderSize.width()));
    for(int x = borderSize.width() / 2; x <= fieldWidth; x+= stepX)
        painter.drawLine(x, 0, x, fieldHeight);

    for(unsigned i = 0; i < cells.size(); i++) {
        unsigned y = i / cols;
        unsigned x = i - y * cols;
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


        painter.fillRect(x * stepX + borderSize.width(),
                         y * stepY + borderSize.height(),
                         cellSize.width(),
                         cellSize.height(),
                         color);
    }
}

QSize MinesField::sizeHint() const
{
    return QSize(cols * cellSize.width(), rows * cellSize.height());
}
