#include "minesfield.h"
#include "minesfieldwidget.h"
#include <QApplication>

#include <QtWidgets>

unsigned field_width = 30;
unsigned field_height = 30;

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    QWidget w;
    QGridLayout* layout = new QGridLayout;

    MinesFieldWidget* field = new MinesFieldWidget(field_width, field_height);

    QScrollBar* verticalScrollBar = new QScrollBar;
    verticalScrollBar->setRange(0, field_height);

    QScrollBar* horizontalScrollBar = new QScrollBar;
    horizontalScrollBar->setRange(0, field_width);
    horizontalScrollBar->setOrientation(Qt::Horizontal);

    QObject::connect(horizontalScrollBar, SIGNAL(valueChanged(int)),
        field, SLOT(horizontalScrollPosChanged(int)));
    QObject::connect(verticalScrollBar, SIGNAL(valueChanged(int)),
        field, SLOT(verticalScrollPosChanged(int)));

    layout->addWidget(field, 0, 0);
    layout->addWidget(verticalScrollBar, 0, 1);
    layout->addWidget(horizontalScrollBar, 1, 0);

    w.setLayout(layout);

    w.show();

    return a.exec();
}
