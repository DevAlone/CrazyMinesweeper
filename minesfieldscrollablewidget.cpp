#include "minesfieldscrollablewidget.h"

MinesFieldScrollableWidget::MinesFieldScrollableWidget(QWidget* parent)
    : QWidget(parent)
{
    minesFieldWidget = new MinesFieldWidget(this);

    QGridLayout* layout = new QGridLayout;

    QScrollBar* verticalScrollBar = new QScrollBar;
    verticalScrollBar->setRange(0, 30); // TODO: do it

    QScrollBar* horizontalScrollBar = new QScrollBar;
    horizontalScrollBar->setRange(0, 30); // TODO: do it
    horizontalScrollBar->setOrientation(Qt::Horizontal);

    QObject::connect(horizontalScrollBar, SIGNAL(valueChanged(int)),
        minesFieldWidget, SLOT(horizontalScrollPosChanged(int)));
    QObject::connect(verticalScrollBar, SIGNAL(valueChanged(int)),
        minesFieldWidget, SLOT(verticalScrollPosChanged(int)));

    layout->addWidget(minesFieldWidget, 0, 0);
    layout->addWidget(verticalScrollBar, 0, 1);
    layout->addWidget(horizontalScrollBar, 1, 0);

    setLayout(layout);
}

void MinesFieldScrollableWidget::keyPressEvent(QKeyEvent* event)
{
    // TODO: make it working
    // TODO: fix multiple events!
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        QPoint cursorPos = cursor().pos();

        if (keyEvent->key() == Qt::Key_A)
            cursorPos.setX(cursorPos.x() - 1);
        else if (keyEvent->key() == Qt::Key_D)
            cursorPos.setX(cursorPos.x() + 1);
        else if (keyEvent->key() == Qt::Key_W)
            cursorPos.setY(cursorPos.y() - 1);
        else if (keyEvent->key() == Qt::Key_S)
            cursorPos.setY(cursorPos.y() + 1);

        cursor().setPos(cursorPos);
    }
}

MinesFieldWidget* MinesFieldScrollableWidget::getMinesFieldWidget() const
{
    return minesFieldWidget;
}
