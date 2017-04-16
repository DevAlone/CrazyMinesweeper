#ifndef WONGAMEDIALOG_H
#define WONGAMEDIALOG_H

#include <QDialog>

namespace Ui {
class WonGameDialog;
}

class WonGameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WonGameDialog(QWidget *parent = 0);
    ~WonGameDialog();

private:
    Ui::WonGameDialog *ui;
};

#endif // WONGAMEDIALOG_H
