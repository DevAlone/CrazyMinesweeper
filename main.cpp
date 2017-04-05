#include "mainwindow.h"
#include "minesfield.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    MinesField *field = new MinesField(1000, 1000);

    QScrollArea scrollArea;
    scrollArea.setWidget(field);

    scrollArea.show();

//    field.show();


    return a.exec();
}
