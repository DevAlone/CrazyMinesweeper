#ifndef MINESFIELDSCROLLABLEWIDGET_H
#define MINESFIELDSCROLLABLEWIDGET_H

#include "minesfieldwidget.h"

#include <QWidget>

class MinesFieldScrollableWidget : public QWidget {
    Q_OBJECT
public:
    explicit MinesFieldScrollableWidget(QWidget* parent = 0);

    MinesFieldWidget* getMinesFieldWidget() const;

    bool eventFilter(QObject* obj, QEvent* event);

signals:

public slots:
    void horizontalScrollBarPositionChanged(int value);
    void verticalScrollBarPositionChanged(int value);

protected:
    void keyPressEvent(QKeyEvent* event);

private:
    MinesFieldWidget* minesFieldWidget = 0;
    QScrollBar* verticalScrollBar = 0;
    QScrollBar* horizontalScrollBar = 0;
};

#endif // MINESFIELDSCROLLABLEWIDGET_H
