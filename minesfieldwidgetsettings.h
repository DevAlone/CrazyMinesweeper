#ifndef MINESFIELDWIDGETSETTINGS_H
#define MINESFIELDWIDGETSETTINGS_H

#include <QColor>

struct MinesFieldWidgetSettings {
    QColor backgroundColor;
    QColor cellColor;

    bool isZoomEnabled = false;
};

#endif // MINESFIELDWIDGETSETTINGS_H
