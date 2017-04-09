#include "mainwindow.h"
#include "minesfield.h"
#include "minesfieldwidget.h"
#include <QApplication>

#include <QtWidgets>

unsigned field_width = 1000;
unsigned field_height = 1000;

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    return a.exec();
}
