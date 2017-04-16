#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "minesfieldwidget.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent* event);
    //    bool event(QEvent* event);
public slots:
    void loseGame();
    void wonGame();
private slots:
    void on_actionNew_game_triggered();

    void on_actionSettings_triggered();

private:
    Ui::MainWindow* ui;

    MinesFieldWidget* minesFieldWidget;
    std::shared_ptr<MinesField> minesField;
};

#endif // MAINWINDOW_H
