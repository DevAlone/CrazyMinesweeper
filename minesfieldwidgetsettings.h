#ifndef MINESFIELDWIDGETSETTINGS_H
#define MINESFIELDWIDGETSETTINGS_H

#include <QColor>

struct MinesFieldWidgetSettings {
    QColor backgroundColor = Qt::gray;
    QColor closedCellColor = Qt::white;
    QColor openedCellColor = Qt::lightGray;
    QColor markedAsBombColor = Qt::red;
    QColor markedAsQuestionColor = Qt::yellow;
    QColor borderColor = Qt::black;
    QColor minesAroundColor = QColor::fromRgb(0, 255, 0);

    bool isZoomEnabled = false;
    bool isHintsEnabled = true;
};

#endif // MINESFIELDWIDGETSETTINGS_H
