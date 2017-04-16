#include "newgamedialog.h"
#include "ui_newgamedialog.h"

// TODO: make saving previous state
NewGameDialog::NewGameDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::NewGameDialog)
{
    ui->setupUi(this);
    ui->fieldWidth->setValidator(new QIntValidator(1, 10000, this));
    ui->fieldHeight->setValidator(new QIntValidator(1, 10000, this));
    ui->cellWidth->setValidator(new QIntValidator(1, 100, this));
    ui->cellHeight->setValidator(new QIntValidator(1, 100, this));
    ui->borderWidth->setValidator(new QIntValidator(1, 100, this));
    ui->borderHeight->setValidator(new QIntValidator(1, 100, this));
    ui->minesPercent->setValidator(new QIntValidator(1, 100, this));

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(updateData()));

    ui->stackedWidget->setCurrentIndex(1);
}

NewGameDialog::~NewGameDialog()
{
    delete ui;
}

NewGameDialogData NewGameDialog::getEnteredData() const
{
    return data;
}

void NewGameDialog::updateData()
{
    //    bool isOk = false;
    data.fieldSize.setWidth(ui->fieldWidth->text().toInt());
    data.fieldSize.setHeight(ui->fieldHeight->text().toInt());

    data.cellSize.setWidth(ui->cellWidth->text().toInt());
    data.cellSize.setHeight(ui->cellHeight->text().toInt());

    data.borderSize.setWidth(ui->borderWidth->text().toInt());
    data.borderSize.setHeight(ui->borderHeight->text().toInt());

    if (data.fieldSize.width() < 1)
        data.fieldSize.setWidth(1);
    if (data.fieldSize.height() < 1)
        data.fieldSize.setHeight(1);

    if (data.cellSize.width() < 1)
        data.cellSize.setWidth(1);
    if (data.cellSize.height() < 1)
        data.cellSize.setHeight(1);

    if (data.borderSize.width() < 0)
        data.borderSize.setWidth(0);
    if (data.borderSize.height() < 0)
        data.borderSize.setHeight(0);

    data.minesPercent = ui->minesPercent->text().toInt();
    if (data.minesPercent < 1)
        data.minesPercent = 1;
    else if (data.minesPercent > 100)
        data.minesPercent = 100;
}

void NewGameDialog::on_pushButtonEasy_clicked()
{
    data.fieldSize = QSize(25, 25);
    data.cellSize = QSize(25, 25);
    data.borderSize = QSize(0, 0);
    data.minesPercent = 20;

    accept();
}

void NewGameDialog::on_pushButtonLIttleHarder_clicked()
{
    data.fieldSize = QSize(50, 50);
    data.cellSize = QSize(25, 25);
    data.borderSize = QSize(1, 1);
    data.minesPercent = 20;

    accept();
}

void NewGameDialog::on_pushButtonAsianMode_clicked()
{
    data.fieldSize = QSize(1000, 1000);
    data.cellSize = QSize(1, 1);
    data.borderSize = QSize(0, 0);
    data.minesPercent = 10;

    accept();
}

void NewGameDialog::on_pushButtonManually_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
