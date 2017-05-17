#include "minesfieldscrollablewidget.h"

MinesFieldScrollableWidget::MinesFieldScrollableWidget(QWidget* parent)
    : QWidget(parent)
{
    minesFieldWidget = new MinesFieldWidget(this);

    QGridLayout* layout = new QGridLayout;

    verticalScrollBar = new QScrollBar;
    verticalScrollBar->setRange(-10, 10);

    horizontalScrollBar = new QScrollBar;
    horizontalScrollBar->setRange(-10, 10);
    horizontalScrollBar->setOrientation(Qt::Horizontal);

    QObject::connect(horizontalScrollBar, SIGNAL(valueChanged(int)),
        minesFieldWidget, SLOT(horizontalScrollPosChanged(int)));
    QObject::connect(verticalScrollBar, SIGNAL(valueChanged(int)),
        minesFieldWidget, SLOT(verticalScrollPosChanged(int)));

    QObject::connect(horizontalScrollBar, SIGNAL(valueChanged(int)),
        this, SLOT(horizontalScrollBarPositionChanged(int)));
    QObject::connect(verticalScrollBar, SIGNAL(valueChanged(int)),
        this, SLOT(verticalScrollBarPositionChanged(int)));

    layout->addWidget(minesFieldWidget, 0, 0);
    layout->addWidget(verticalScrollBar, 0, 1);
    layout->addWidget(horizontalScrollBar, 1, 0);

    setLayout(layout);
}

MinesFieldWidget* MinesFieldScrollableWidget::getMinesFieldWidget() const
{
    return minesFieldWidget;
}

bool MinesFieldScrollableWidget::eventFilter(QObject*, QEvent*)
{
    return false;
}

void MinesFieldScrollableWidget::horizontalScrollBarPositionChanged(int)
{
    horizontalScrollBar->setValue(0);
}

void MinesFieldScrollableWidget::verticalScrollBarPositionChanged(int)
{
    verticalScrollBar->setValue(0);
}
