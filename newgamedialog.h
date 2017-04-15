#ifndef NEWGAMEDIALOG_H
#define NEWGAMEDIALOG_H

#include <QDialog>

struct NewGameDialogData {
    QSize fieldSize,
        cellSize,
        borderSize;
};

namespace Ui {
class NewGameDialog;
}

class NewGameDialog : public QDialog {
    Q_OBJECT

public:
    explicit NewGameDialog(QWidget* parent = 0);
    ~NewGameDialog();
    NewGameDialogData getEnteredData() const;

private slots:
    void updateData();

    void on_pushButtonEasy_clicked();

    void on_pushButtonLIttleHarder_clicked();

    void on_pushButtonAsianMode_clicked();

    void on_pushButtonManually_clicked();

private:
    Ui::NewGameDialog* ui;
    NewGameDialogData data;
};

#endif // NEWGAMEDIALOG_H
