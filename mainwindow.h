#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "popupmsg.h"

#include <QHash>
#include <QMainWindow>

static int interval_msg = 10;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void openedMessage(bool show);

private:
    Ui::MainWindow *ui;
    popupmsg *popup;
    QHash<QString, QWidget *> popups;
    int coordY;
};

#endif // MAINWINDOW_H
