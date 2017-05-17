#include "minesfieldwidget.h"
#include <QDebug>

MinesFieldWidget::MinesFieldWidget(QWidget* parent)
    : QWidget(parent)
{
    settings.backgroundColor = Qt::gray;
    settings.closedCellColor = Qt::white;

    //    connect(field.get(), SIGNAL(userLost()), this, SLOT(userLose()));
    cellSize = QSize(1, 1);
    borderSize = QSize(0, 0);
    //    fieldSize = QSize(cols * (cellSize.width() + borderSize.width()),
    //        rows * (cellSize.height() + borderSize.height()));

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

MinesFieldWidget::~MinesFieldWidget()
{
}

void MinesFieldWidget::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);

    if (!field->getCreated()) {
        painter.drawText(width() / 2, height() / 2, "creating field...");
        return;
    }
    painter.drawPixmap(0, 0, pixmap);

    int startDrawingPosY = 0;
    double popupWidth = width() * 0.25;
    if (settings.isZoomEnabled && mousePos.x() >= 0 && mousePos.x() < pixmap.width()
        && mousePos.y() >= 0 && mousePos.y() < pixmap.height()) {
        auto zoomedPixmap = pixmap.copy(mousePos.x() >= zoomArea.width() / 2 ? mousePos.x() - zoomArea.width() / 2 : 0,
                                      mousePos.y() >= zoomArea.height() / 2 ? mousePos.y() - zoomArea.height() / 2 : 0,
                                      zoomArea.width(),
                                      zoomArea.height())
                                .scaled(popupWidth, popupWidth);
        int centerRectWidth = zoomedPixmap.width() / zoomArea.width();
        int centerRectHeight = zoomedPixmap.height() / zoomArea.height();

        QPainter p1(&zoomedPixmap);
        // draw center rectangle
        QPoint centerRectPos;
        if (mousePos.x() >= zoomArea.width() / 2)
            centerRectPos.setX(zoomArea.width() / 2);
        else
            centerRectPos.setX(mousePos.x());

        if (mousePos.y() >= zoomArea.height() / 2)
            centerRectPos.setY(zoomArea.height() / 2);
        else
            centerRectPos.setY(mousePos.y());

        p1.drawRect(centerRectWidth * centerRectPos.x(),
            centerRectHeight * centerRectPos.y(),
            centerRectWidth,
            centerRectHeight);

        //        p1.drawRect(0, 0, zoomedPixmap.width() - 1, zoomedPixmap.height() - 1);
        painter.drawPixmap(width() - zoomedPixmap.width(), 0, zoomedPixmap);
        startDrawingPosY += zoomedPixmap.height();
    }
    if (settings.isHintsEnabled) {
        int cellWidth = popupWidth / 8.0;
        QPixmap hintsPixmap(popupWidth, cellWidth * 2);
        hintsPixmap.fill(settings.backgroundColor);
        QPainter p1(&hintsPixmap);

        for (int i = 0; i < 8; i++) {
            int minesAroundCell = i + 1;
            auto color = QColor((9 - minesAroundCell) / 8.0 * settings.minesAroundColor.red(),
                (9 - minesAroundCell) / 8.0 * settings.minesAroundColor.green(),
                (9 - minesAroundCell) / 8.0 * settings.minesAroundColor.blue());
            p1.setBrush(color);
            p1.setPen(Qt::transparent);
            p1.drawRect(i * (cellWidth), 0, cellWidth, cellWidth);

            p1.setPen(QColor::fromRgb(255 - settings.backgroundColor.red(),
                255 - settings.backgroundColor.green(),
                255 - settings.backgroundColor.blue()));
            p1.drawText(i * cellWidth, 1.75 * cellWidth, QString::number(minesAroundCell));
        }
        p1.setBrush(Qt::transparent);
        //        p1.drawRect(0, 0, popupWidth - 1, 2 * cellWidth - 1);
        painter.drawPixmap(width() - popupWidth, startDrawingPosY, hintsPixmap);
    }

    event->accept();
}

void MinesFieldWidget::resizeEvent(QResizeEvent*)
{
    updatePixmap();
}

void MinesFieldWidget::wheelEvent(QWheelEvent* event)
{
    if (event->modifiers())
        horizontalScrollPosChanged(-event->delta() / 120);
    else
        verticalScrollPosChanged(-event->delta() / 120);
    return QWidget::wheelEvent(event);
}

void MinesFieldWidget::showEvent(QShowEvent* event)
{
    updatePixmap();
    QWidget::showEvent(event);
}

void MinesFieldWidget::mousePressEvent(QMouseEvent* event)
{
    if (!field)
        return;
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
    if (!field)
        return;
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

MinesFieldWidgetSettings& MinesFieldWidget::getSettings()
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
    // TODO: fix unhighlighting with other color outside field
    QColor color = settings.backgroundColor;
    Cell* cell;
    try {
        cell = field->getCell(cellPoint);
    } catch (std::out_of_range& ex) {
        highlightCell(cellPoint, color);
        return;
    }
    color = getCellColor(cell->cellState(), cell->minesAround());

    highlightCell(cellPoint, color);
    //    if (cell->cellState() == Cell::CellState::Opened)
    //        updatePixmap();
    //    else
    //        highlightCell(cellPoint, color);
}

QColor MinesFieldWidget::getCellColor(Cell::CellState cellState, int minesAroundCell)
{
    QColor color = settings.backgroundColor;
    switch (cellState) {
    case Cell::CellState::Closed:
        color = settings.closedCellColor;
        break;
    case Cell::CellState::Opened:
        if (minesAroundCell == 0)
            color = settings.openedCellColor;
        else {
            // color = settings.minesAroundColor; // QColor(0, 100.0 + 155.0 * (8 - minesAroundCell) / 8.0, 0);
            color = QColor((9 - minesAroundCell) / 8.0 * settings.minesAroundColor.red(),
                (9 - minesAroundCell) / 8.0 * settings.minesAroundColor.green(),
                (9 - minesAroundCell) / 8.0 * settings.minesAroundColor.blue());
        }
        break;
    case Cell::CellState::MarkedAsBomb:
        color = settings.markedAsBombColor;
        break;
    case Cell::CellState::MarkedAsQuestion:
        color = settings.markedAsQuestionColor;
        break;
    default:
        break;
    }
    return color;
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
    // to do: optimize this shit

    if (!field || !field->getCreated())
        return;

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

    pixmap.fill(settings.backgroundColor);
    QPainter painter(&pixmap);
    int stepX = cellSize.width() + borderSize.width();
    int stepY = cellSize.height() + borderSize.height();

    // horizontal lines
    if (borderSize.height() > 0) {
        painter.setPen(QPen(settings.borderColor, borderSize.height()));
        for (unsigned y = borderSize.height() / 2; y <= viewport.height; y += stepY)
            painter.drawLine(0, y, viewport.width, y);
    }

    // vertical lines
    if (borderSize.width() > 0) {
        painter.setPen(QPen(settings.borderColor, borderSize.width()));
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

            int minesAroundCell = cell.minesAround(); // TODO: ?
            QColor color = getCellColor(cell.cellState(), minesAroundCell);

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
    scrollPosChanged(0, pos);
    return;
}

void MinesFieldWidget::horizontalScrollPosChanged(int pos)
{
    scrollPosChanged(pos, 0);
    return;
}

void MinesFieldWidget::scrollPosChanged(int horizontal_pos, int vertical_pos)
{
    viewport.start_col += horizontal_pos;
    viewport.start_row += vertical_pos;
    if (viewport.start_col < 0)
        viewport.start_col = 0;
    else if (viewport.start_col > field->getCols() - 1)
        viewport.start_col = field->getCols() - 1;

    if (viewport.start_row < 0)
        viewport.start_row = 0;
    else if (viewport.start_row > field->getRows() - 1)
        viewport.start_row = field->getRows() - 1;

    viewport.x = viewport.start_col * (cellSize.width() + borderSize.width());
    viewport.y = viewport.start_row * (cellSize.height() + borderSize.height());
    updatePixmap();
}
