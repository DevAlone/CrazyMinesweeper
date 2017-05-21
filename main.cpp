#include "mainwindow.h"
#include "minesfield.h"
#include "minesfieldwidget.h"
#include <QApplication>

#include <QtWidgets>
#include <ctime>
// TODO: add hints, for example it will open cells, that marked as question
int main(int argc, char* argv[])
{
    srand(time(0));
    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    return a.exec();
}
