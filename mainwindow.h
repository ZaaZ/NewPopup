#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "popupmsg.h"
#include "countmsg.h"

#include <QHash>
#include <QMainWindow>
#include <QThread>

static int interval_msg = 10;


class Sleeper: public QThread
{
    public:
        static void msleep(int ms)
        {
            QThread::msleep(ms);
        }
};


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
    void deleteMsg();

private:
    Ui::MainWindow *ui;
    popupmsg *popup;
    CountMsg *cntmsg;
    //QHash<QString, popupmsg *> popups;
    QList<popupmsg *> *popups;
    int coordY;
};

#endif // MAINWINDOW_H
