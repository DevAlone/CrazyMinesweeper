#ifndef MINESFIELDWIDGETSETTINGS_H
#define MINESFIELDWIDGETSETTINGS_H

#include <QColor>

struct MinesFieldWidgetSettings {
    QColor backgroundColor = Qt::gray;
    QColor closedCellColor = Qt::white;
    QColor markedAsBombColor = Qt::red;
    QColor markedAsQuestionColor = Qt::yellow;
    QColor borderColor = Qt::black;

    bool isZoomEnabled = false;
};

#endif // MINESFIELDWIDGETSETTINGS_H
