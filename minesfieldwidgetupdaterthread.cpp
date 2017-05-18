#include "minesfieldwidgetupdaterthread.h"

MinesFieldWidgetUpdaterThread::MinesFieldWidgetUpdaterThread(MinesFieldWidget* widget, QObject* parent)
    : QThread(parent)
    , minesFieldWidget(widget)
{
}

void MinesFieldWidgetUpdaterThread::run()
{

    QPixmap lpixmap = QPixmap(minesFieldWidget->viewport.width, minesFieldWidget->viewport.height);

    lpixmap.fill(minesFieldWidget->settings.backgroundColor);
    QPainter painter(&lpixmap);
    int stepX = minesFieldWidget->cellSize.width() + minesFieldWidget->borderSize.width();
    int stepY = minesFieldWidget->cellSize.height() + minesFieldWidget->borderSize.height();

    // horizontal lines
    if (minesFieldWidget->borderSize.height() > 0) {
        painter.setPen(QPen(minesFieldWidget->settings.borderColor,
            minesFieldWidget->borderSize.height()));
        for (unsigned y = minesFieldWidget->borderSize.height() / 2;
             y <= minesFieldWidget->viewport.height; y += stepY)
            painter.drawLine(0, y, minesFieldWidget->viewport.width, y);
    }

    // vertical lines
    if (minesFieldWidget->borderSize.width() > 0) {
        painter.setPen(QPen(minesFieldWidget->settings.borderColor,
            minesFieldWidget->borderSize.width()));
        for (unsigned x = minesFieldWidget->borderSize.width() / 2;
             x <= minesFieldWidget->viewport.width; x += stepX)
            painter.drawLine(x, 0, x, minesFieldWidget->viewport.height);
    }

    for (unsigned y = minesFieldWidget->viewport.start_row;
         y < minesFieldWidget->viewport.start_row + minesFieldWidget->viewport.rows && y < minesFieldWidget->field->getRows();
         y++) {
        for (unsigned x = minesFieldWidget->viewport.start_col;
             x < minesFieldWidget->viewport.start_col + minesFieldWidget->viewport.cols && x < minesFieldWidget->field->getCols();
             x++) {
            unsigned i = minesFieldWidget->field->getCellIndex(Point(x, y));
            if (!minesFieldWidget->field->isCellIndexValid(i))
                continue;

            auto& cells = minesFieldWidget->field->getCells();
            const Cell& cell = cells.at(i);

            int minesAroundCell = cell.minesAround(); // TODO: ?
            QColor color = minesFieldWidget->getCellColor(cell.cellState(), minesAroundCell);

            painter.fillRect((x - minesFieldWidget->viewport.start_col) * stepX + minesFieldWidget->borderSize.width(),
                (y - minesFieldWidget->viewport.start_row) * stepY + minesFieldWidget->borderSize.height(),
                minesFieldWidget->cellSize.width(),
                minesFieldWidget->cellSize.height(),
                color);
        }
    }
    // atomic copy
    minesFieldWidget->updatingMutex.lock();
    minesFieldWidget->pixmap = lpixmap;
    minesFieldWidget->updatingMutex.unlock();
    static int n = 1;
    n++;
    qDebug() << "thread finished" << n;
}
