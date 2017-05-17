#include "mainwindow.h"
#include "minesfield.h"
#include "minesfieldwidget.h"
#include <QApplication>

#include <QtWidgets>
#include <ctime>

// add showing mines left
int main(int argc, char* argv[])
{
    srand(time(0));
    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    return a.exec();
}
