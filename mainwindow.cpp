#include "mainwindow.h"
#include "minesfieldsettingsdialog.h"
#include "newgamedialog.h"
#include "ui_mainwindow.h"
#include "wongamedialog.h"

// TODO: добавить показ количества оставшихся мин
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    minesFieldWidget = ui->minesFieldScrollableWidget->getMinesFieldWidget();
    minesField = std::shared_ptr<MinesField>(new MinesField(20, 20, 20));
    minesFieldWidget->setField(minesField);
    minesFieldWidget->setCellSize(QSize(25, 25));
    minesFieldWidget->setBorderSize(QSize(0, 0));

    connect(minesField.get(), SIGNAL(userLost()), this, SLOT(loseGame()));
    connect(minesField.get(), SIGNAL(userWon()), this, SLOT(wonGame()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{

    QMainWindow::keyPressEvent(event);
}

bool MainWindow::event(QEvent* event)
{
    if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        QPoint cursorPos = cursor().pos();

        auto cell = minesFieldWidget->getCellByMousePoint(minesFieldWidget->mapFromGlobal(cursorPos));
        if (cell.x() <= 0) {
            cell.setX(0);
            minesFieldWidget->horizontalScrollPosChanged(-1);
        } else if (cell.x() > minesFieldWidget->getViewport().cols - 1) {
            cell.setX(minesFieldWidget->getViewport().cols - 1);
            minesFieldWidget->horizontalScrollPosChanged(1);
        }
        if (cell.y() <= 0) {
            cell.setY(0);
            minesFieldWidget->verticalScrollPosChanged(-1);
        } else if (cell.y() > minesFieldWidget->getViewport().rows - 1) {
            cell.setY(minesFieldWidget->getViewport().rows - 1);
            minesFieldWidget->verticalScrollPosChanged(1);
        }

        qDebug() << cursorPos << "?" << cell.x() << ":" << cell.y();

        auto stepSize = minesFieldWidget->getCellSize() + minesFieldWidget->getBorderSize();
        QPoint cellPos = QPoint(cell.x() * stepSize.width() + stepSize.width() / 2,
            cell.y() * stepSize.height() + stepSize.height() / 2);

        cursorPos = minesFieldWidget->mapToGlobal(cellPos);

        auto key = keyEvent->key();

        if (keyEvent->modifiers() & Qt::ControlModifier)
            stepSize = QSize(stepSize.width() * 2, stepSize.height() * 2);
        if (keyEvent->modifiers() & Qt::ShiftModifier)
            stepSize = QSize(stepSize.width() * 4, stepSize.height() * 4);

        if (event->type() == QEvent::KeyPress) {
            if (key == Qt::Key_A)
                cursorPos.setX(cursorPos.x() - stepSize.width());
            else if (key == Qt::Key_D)
                cursorPos.setX(cursorPos.x() + stepSize.width());
            else if (key == Qt::Key_W)
                cursorPos.setY(cursorPos.y() - stepSize.height());

            else if (key == Qt::Key_S)
                cursorPos.setY(cursorPos.y() + stepSize.height());
        }

        if (key == Qt::Key_Q || key == Qt::Key_E || key == Qt::Key_Tab) {
            auto cursorPos = minesFieldWidget->mapFromGlobal(QCursor::pos());
            // determining button
            auto button = key == Qt::Key_Q ? Qt::LeftButton
                                           : key == Qt::Key_E ? Qt::RightButton
                                                              : Qt::MiddleButton;

            QMouseEvent clickEvent(
                event->type() == QEvent::KeyPress ? QEvent::MouseButtonPress : QEvent::MouseButtonRelease,
                cursorPos,
                button,
                button,
                Qt::NoModifier);
            QCoreApplication::sendEvent(minesFieldWidget, &clickEvent);
        }

        cursor().setPos(cursorPos);

        return true;
    }

    return QMainWindow::event(event);
}

void MainWindow::loseGame()
{
    QMessageBox::warning(this, "looser", "you lose, lol");
    on_actionNew_game_triggered();
}

void MainWindow::wonGame()
{
    WonGameDialog dialog;

    if (dialog.exec() == QDialog::Accepted) {
        on_actionNew_game_triggered();
    }
}

//bool MainWindow::event(QEvent* event)
//{
// return true;
//}

void MainWindow::on_actionNew_game_triggered()
{
    std::unique_ptr<NewGameDialog> dialog;
    if (minesField)
        dialog = std::unique_ptr<NewGameDialog>(new NewGameDialog(0,
            QSize(minesField->getRows(), minesField->getCols()),
            minesFieldWidget->getCellSize(),
            minesFieldWidget->getBorderSize(),
            minesField->getMinesPercents() * 100.0));
    else
        dialog = std::unique_ptr<NewGameDialog>(new NewGameDialog);

    if (dialog->exec() == QDialog::Accepted) {
        auto data = dialog->getEnteredData();

        minesField = std::shared_ptr<MinesField>(
            new MinesField(data.fieldSize.width(), data.fieldSize.height(), data.minesPercent));
        minesFieldWidget->setField(minesField);

        connect(minesField.get(), SIGNAL(userLost()), this, SLOT(loseGame()));
        connect(minesField.get(), SIGNAL(userWon()), this, SLOT(wonGame()));

        minesFieldWidget->setCellSize(data.cellSize);
        minesFieldWidget->setBorderSize(data.borderSize);

        minesFieldWidget->updatePixmap();
    }
}

void MainWindow::on_actionSettings_triggered()
{
    MinesFieldWidgetSettings oldSettings = minesFieldWidget->getSettings();

    MinesFieldSettingsDialog dialog(minesFieldWidget);
    if (dialog.exec() == QDialog::Accepted) {
        // set settings here
        minesFieldWidget->setSettings(dialog.getSettings());
        minesFieldWidget->updatePixmap();
        return;
    }
    minesFieldWidget->setSettings(oldSettings);
    minesFieldWidget->updatePixmap();
}
