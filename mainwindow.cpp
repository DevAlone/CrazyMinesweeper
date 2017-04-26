#include "mainwindow.h"
#include "minesfieldsettingsdialog.h"
#include "newgamedialog.h"
#include "ui_mainwindow.h"
#include "wongamedialog.h"

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

void MainWindow::keyPressEvent(QKeyEvent*)
{
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
