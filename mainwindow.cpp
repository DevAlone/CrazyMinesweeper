#include "mainwindow.h"
#include "newgamedialog.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    minesFieldWidget = ui->minesFieldScrollableWidget->getMinesFieldWidget();
    minesField = std::make_shared<MinesField>(20, 20);
    minesFieldWidget->setField(minesField);
    minesFieldWidget->setCellSize(QSize(25, 25));
    minesFieldWidget->setBorderSize(QSize(0, 0));

    connect(minesField.get(), SIGNAL(userLost()), this, SLOT(loseGame()));
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
    qDebug() << "you lose";
    on_actionNew_game_triggered();
}

//bool MainWindow::event(QEvent* event)
//{
// return true;
//}

void MainWindow::on_actionNew_game_triggered()
{
    NewGameDialog dialog;

    if (dialog.exec() == QDialog::Accepted) {
        auto data = dialog.getEnteredData();

        minesField = std::make_shared<MinesField>(data.fieldSize.width(), data.fieldSize.height());
        minesFieldWidget->setField(minesField);

        connect(minesField.get(), SIGNAL(userLost()), this, SLOT(loseGame()));

        minesFieldWidget->setCellSize(data.cellSize);
        minesFieldWidget->setBorderSize(data.borderSize);

        minesFieldWidget->updatePixmap();
    }
}

void MainWindow::on_actionSettings_triggered()
{
}
