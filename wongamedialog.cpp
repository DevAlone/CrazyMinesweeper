#include "wongamedialog.h"
#include "ui_wongamedialog.h"

WonGameDialog::WonGameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WonGameDialog)
{
    ui->setupUi(this);
}

WonGameDialog::~WonGameDialog()
{
    delete ui;
}
