#include "minesfieldsettingsdialog.h"

#include <ui_minesfieldsettingsdialog.h>
MinesFieldSettingsDialog::MinesFieldSettingsDialog(MinesFieldWidget* minesFieldWidget, QWidget* parent)
    : QDialog(parent)
    , minesFieldWidget(minesFieldWidget)
    , ui(new Ui::MinesFieldSettingsDialog)
    , settings(&minesFieldWidget->getSettings())
{
    ui->setupUi(this);
    ui->backgroundColorButton->setColor(settings->backgroundColor);
    ui->closedCellColorButton->setColor(settings->closedCellColor);
    ui->openedCellColorButton->setColor(settings->openedCellColor);
    ui->markedAsBombColorButton->setColor(settings->markedAsBombColor);
    ui->markedAsQuestionColorButton->setColor(settings->markedAsQuestionColor);
    ui->borderColorButton->setColor(settings->borderColor);
    ui->minesAroundColorButton->setColor(settings->minesAroundColor);
    ui->showZoom->setChecked(settings->isZoomEnabled);
    ui->showHints->setChecked(settings->isHintsEnabled);
    connect(this, SIGNAL(accepted()), this, SLOT(updateSettings()));

    connect(ui->backgroundColorButton, SIGNAL(clicked(bool)), this, SLOT(updateSettings()));
    connect(ui->closedCellColorButton, SIGNAL(clicked(bool)), this, SLOT(updateSettings()));
    connect(ui->openedCellColorButton, SIGNAL(clicked(bool)), this, SLOT(updateSettings()));
    connect(ui->markedAsBombColorButton, SIGNAL(clicked(bool)), this, SLOT(updateSettings()));
    connect(ui->markedAsQuestionColorButton, SIGNAL(clicked(bool)), this, SLOT(updateSettings()));
    connect(ui->borderColorButton, SIGNAL(clicked(bool)), this, SLOT(updateSettings()));
    connect(ui->minesAroundColorButton, SIGNAL(clicked(bool)), this, SLOT(updateSettings()));
    connect(ui->showZoom, SIGNAL(clicked(bool)), this, SLOT(updateSettings()));
    connect(ui->showHints, SIGNAL(clicked(bool)), this, SLOT(updateSettings()));
}

MinesFieldSettingsDialog::~MinesFieldSettingsDialog()
{
    delete ui;
}

MinesFieldWidgetSettings MinesFieldSettingsDialog::getSettings() const
{
    return *settings;
}

void MinesFieldSettingsDialog::updateSettings()
{
    settings->backgroundColor = ui->backgroundColorButton->getColor();
    settings->closedCellColor = ui->closedCellColorButton->getColor();
    settings->openedCellColor = ui->openedCellColorButton->getColor();
    settings->markedAsBombColor = ui->markedAsBombColorButton->getColor();
    settings->markedAsQuestionColor = ui->markedAsQuestionColorButton->getColor();
    settings->borderColor = ui->borderColorButton->getColor();
    settings->minesAroundColor = ui->minesAroundColorButton->getColor();
    settings->isZoomEnabled = ui->showZoom->isChecked();
    settings->isHintsEnabled = ui->showHints->isChecked();
    minesFieldWidget->updatePixmap();
}
