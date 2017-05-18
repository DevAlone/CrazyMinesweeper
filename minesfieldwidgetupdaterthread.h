#ifndef MINESFIELDWIDGETUPDATERTHREAD_H
#define MINESFIELDWIDGETUPDATERTHREAD_H

#include "minesfieldwidget.h"

#include <QtWidgets>

class MinesFieldWidget;

class MinesFieldWidgetUpdaterThread : public QThread {
    Q_OBJECT
public:
    explicit MinesFieldWidgetUpdaterThread(MinesFieldWidget* widget, QObject* parent = 0);

signals:

public slots:

    // QThread interface
protected:
    virtual void run();

private:
    MinesFieldWidget* minesFieldWidget;
};

#endif // MINESFIELDWIDGETUPDATERTHREAD_H
