#include "minesfieldwidget.h"

MinesFieldWidget::MinesFieldWidget(QWidget* parent)
    : QWidget(parent)
{
    int cols = 1000, rows = 1000; // TODO: delete this
    settings.backgroundColor = Qt::gray;
    settings.cellColor = Qt::white;

    field = std::make_unique<MinesField>(rows, cols);
    connect(field.get(), SIGNAL(userLost()), this, SLOT(userLose()));
    // TODO: fix it
    cellSize = QSize(1, 1);
    borderSize = QSize(0, 0);
    fieldSize = QSize(cols * (cellSize.width() + borderSize.width()),
        rows * (cellSize.height() + borderSize.height()));

    viewport.x = 0;
    viewport.y = 0;
    viewport.width = 100; //visibleRegion().boundingRect().width();
    viewport.height = 100; //visibleRegion().boundingRect().height();

    viewport.start_col = viewport.start_row = 0;
    viewport.rows = 100;
    viewport.cols = 100;

    //    zoomWindow = QPixmap(width() / 4 > 0 ? width() / 4 : 1,
    //        height() / 4 > 0 ? height() / 4 : 1);
    pixmap = QPixmap(width(), height());
    updatePixmap();

    setMouseTracking(true);
}

void MinesFieldWidget::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);

    painter.drawPixmap(0, 0, pixmap);

    if (settings.isZoomEnabled && mousePos.x() >= 0 && mousePos.x() < pixmap.width()
        && mousePos.y() >= 0 && mousePos.y() < pixmap.height()) {
        // TODO: optimize this, maybe add checks for out of range
        // TODO: fix zoom near borders
        auto zoomedPixmap = pixmap.copy(mousePos.x() - zoomArea.width() / 2,
                                      mousePos.y() - zoomArea.height() / 2,
                                      zoomArea.width(),
                                      zoomArea.height())
                                .scaled(width() * 0.4, width() * 0.4);
        int centerRectWidth = zoomedPixmap.width() / zoomArea.width();
        int centerRectHeight = zoomedPixmap.height() / zoomArea.height();

        QPainter p1(&zoomedPixmap);
        p1.drawRect(centerRectWidth * (zoomArea.width() / 2),
            centerRectHeight * (zoomArea.height() / 2),
            centerRectWidth,
            centerRectHeight);
        p1.drawRect(0, 0, zoomedPixmap.width() - 1, zoomedPixmap.height() - 1);
        painter.drawPixmap(width() * 0.6, 0, zoomedPixmap);
    }

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
    auto pos = event->pos();
    Point cellPoint;
    cellPoint.setX(double(pos.x()) / (cellSize.width() + borderSize.width()));
    cellPoint.setY(double(pos.y()) / (cellSize.height() + borderSize.height()));

    selectedCell = convertCellPointToAbsolute(cellPoint);
    if (event->buttons() == Qt::LeftButton) {
        highlightCell(selectedCell);
    } else if (event->buttons() == Qt::RightButton) {
        Cell* cell;
        try {
            cell = field->getCell(selectedCell);
        } catch (std::out_of_range& ex) {
            return;
        }

        if (cell->cellState() == Cell::CellState::Closed)
            field->markCell(selectedCell, Cell::CellState::MarkedAsBomb);
        else if (cell->cellState() == Cell::CellState::MarkedAsBomb)
            field->markCell(selectedCell, Cell::CellState::MarkedAsQuestion);
        else if (cell->cellState() == Cell::CellState::MarkedAsQuestion)
            field->unmarkCell(selectedCell);

        updatePixmap();
    } else if (event->buttons() == Qt::MiddleButton) {
        field->lazyOpenCells(selectedCell);
        updatePixmap();
    }
    update();
}

void MinesFieldWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        auto pos = event->pos();
        Point cell(double(pos.x()) / (cellSize.width() + borderSize.width()),
            double(pos.y()) / (cellSize.height() + borderSize.height()));
        cell = convertCellPointToAbsolute(cell);

        unhighlightCell(selectedCell);
        if (cell != selectedCell)
            return;
        field->tryToOpenCell(selectedCell);
        updatePixmap();
    }
    update();
}

void MinesFieldWidget::mouseMoveEvent(QMouseEvent* event)
{
    mousePos = event->pos();
    update();
}

void MinesFieldWidget::keyPressEvent(QKeyEvent* event)
{
}

MinesFieldWidgetSettings MinesFieldWidget::getSettings() const
{
    return settings;
}

void MinesFieldWidget::setSettings(const MinesFieldWidgetSettings& value)
{
    settings = value;
}

std::shared_ptr<MinesField> MinesFieldWidget::getField() const
{
    return field;
}

void MinesFieldWidget::setField(const std::shared_ptr<MinesField>& value)
{
    field = value;
}

void MinesFieldWidget::highlightCell(Point cellPoint, QColor color)
{
    cellPoint.setX(cellPoint.x() - viewport.start_col);
    cellPoint.setY(cellPoint.y() - viewport.start_row);
    if (cellPoint.x() < 0 || cellPoint.y() < 0)
        return;
    QPainter painter(&pixmap);
    int x = cellPoint.x() * (cellSize.width() + borderSize.width()) + borderSize.width();
    int y = cellPoint.y() * (cellSize.height() + borderSize.height()) + borderSize.height();
    painter.fillRect(x,
        y,
        cellSize.width(),
        cellSize.height(),
        color);
    update();
}

void MinesFieldWidget::unhighlightCell(Point cellPoint)
{
    // TODO: fix unhighlighting with other color
    QColor color = Qt::white;
    Cell* cell;
    try {
        cell = field->getCell(cellPoint);
    } catch (std::out_of_range& ex) {
        return;
    }

    if (cell->cellState() == Cell::CellState::Opened)
        updatePixmap();
    else
        highlightCell(cellPoint, color);
}

QSize MinesFieldWidget::getBorderSize() const
{
    return borderSize;
}

void MinesFieldWidget::setBorderSize(const QSize& value)
{
    borderSize = value;
}

QSize MinesFieldWidget::getCellSize() const
{
    return cellSize;
}

void MinesFieldWidget::setCellSize(const QSize& value)
{
    cellSize = value;
}

Point MinesFieldWidget::getCellByMousePoint(const QPoint& mousePoint)
{
    return Point(double(mousePoint.x()) / (cellSize.width() + borderSize.width()),
        double(mousePoint.y()) / (cellSize.height() + borderSize.height()));
}

Point MinesFieldWidget::convertCellPointToAbsolute(const Point& point)
{
    return Point(point.x() + viewport.start_col, point.y() + viewport.start_row);
}

void MinesFieldWidget::updatePixmap()
{
    // TODO: do it
    int width = visibleRegion().boundingRect().width();
    int height = visibleRegion().boundingRect().height();
    //    int width = 100;
    //    int height = 100;
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
    if (borderSize.height() > 0) {
        painter.setPen(QPen(Qt::black, borderSize.height()));
        for (unsigned y = borderSize.height() / 2; y <= viewport.height; y += stepY)
            painter.drawLine(0, y, viewport.width, y);
    }

    // vertical lines
    if (borderSize.width() > 0) {
        painter.setPen(QPen(Qt::black, borderSize.width()));
        for (unsigned x = borderSize.width() / 2; x <= viewport.width; x += stepX)
            painter.drawLine(x, 0, x, viewport.height);
    }

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
            case Cell::CellState::MarkedAsQuestion:
                color = Qt::blue;
                break;
            default:
                break;
            }

            //            if (cell.isMine())
            //                color = Qt::red;

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

void MinesFieldWidget::userLose()
{
    QMessageBox::warning(this, "you lose", "you lose");

    field = std::make_unique<MinesField>(field->getRows(), field->getCols());
    connect(field.get(), SIGNAL(userLost()), this, SLOT(userLose()));
    updatePixmap();
}
