#ifndef MINESFIELDSCROLLABLEWIDGET_H
#define MINESFIELDSCROLLABLEWIDGET_H

#include "minesfieldwidget.h"

#include <QWidget>

class MinesFieldScrollableWidget : public QWidget {
    Q_OBJECT
public:
    explicit MinesFieldScrollableWidget(QWidget* parent = 0);

signals:

public slots:

protected:
    void keyPressEvent(QKeyEvent* event);

private:
    MinesFieldWidget* minesFieldWidget;
};

#endif // MINESFIELDSCROLLABLEWIDGET_H
