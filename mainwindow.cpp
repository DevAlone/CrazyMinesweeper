#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
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

//bool MainWindow::event(QEvent* event)
//{
// return true;
//}
