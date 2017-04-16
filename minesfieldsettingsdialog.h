#ifndef MINESFIELDSETTINGSDIALOG_H
#define MINESFIELDSETTINGSDIALOG_H

#include "minesfieldwidget.h"
#include "minesfieldwidgetsettings.h"

#include <QDialog>

namespace Ui {
class MinesFieldSettingsDialog;
}

class MinesFieldSettingsDialog : public QDialog {
    Q_OBJECT

public:
    MinesFieldSettingsDialog(MinesFieldWidget* minesFieldWidget, QWidget* parent = 0);
    ~MinesFieldSettingsDialog();

    MinesFieldWidgetSettings getSettings() const;

private slots:
    void updateSettings();

private:
    Ui::MinesFieldSettingsDialog* ui;
    MinesFieldWidget* minesFieldWidget;
    MinesFieldWidgetSettings& settings;
};

#endif // MINESFIELDSETTINGSDIALOG_H
