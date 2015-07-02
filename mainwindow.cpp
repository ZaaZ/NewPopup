#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QUuid>
#include <QDebug>

#include <QGraphicsDropShadowEffect>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    coordY = 20;
    cntmsg = new CountMsg(this);
    cntmsg->setHidden(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
//    if (popup){
//        popup->show();
//    } else {
//        popup = new popupmsg(this);
//        popup->show();
//    }
    popupmsg *msg = new popupmsg(this);
//    QGraphicsDropShadowEffect *effect=new QGraphicsDropShadowEffect();
//    effect->setBlurRadius(5);
//    effect->setXOffset(5);
//    effect->setYOffset(5);
//    msg->setGraphicsEffect(effect);
//    msg->resize(400,120);
    QString text = trUtf8("Тут находится очень длинный текст с оповещением для руководителя и населения"
                          " Тут находится очень длинный текст с оповещением для руководителя и населения"
                          " Тут находится очень длинный текст с оповещением для руководителя и населения");
    msg->setText(text);
    msg->setFile(true);
    int x = width()-msg->width()-interval_msg;
    msg->move(x,coordY);
    coordY += msg->height()+interval_msg;
    QString Id = QUuid::createUuid().toRfc4122().toHex();
    popups.insert(Id,msg);
    if (height()> coordY)
        msg->show();
    else {
            qDebug() << "Update cntmsg";
            cntmsg->setCount(popups.size());
            if (cntmsg->isHidden()){
                cntmsg->move(x - interval_msg - cntmsg->width(),20);
                cntmsg->show();
            }
            else
                cntmsg->update();

    }
    connect(msg,SIGNAL(openedMsg(bool)),this,SLOT(openedMessage(bool)));
    connect(msg,SIGNAL(deleteMsg()),this,SLOT(deleteMsg()));

}

void MainWindow::openedMessage(bool show)
{
    popupmsg *tmpMsg = qobject_cast<popupmsg *> (sender());
    if (show){
        //показываем
        tmpMsg->move(width()-tmpMsg->width()-interval_msg,tmpMsg->y());

    } else {
        //скрываем
        tmpMsg->move(width()-tmpMsg->width()-interval_msg,tmpMsg->y());
    }
    //перерисовываем сообщения ниже
}

void MainWindow::deleteMsg()
{
    qDebug() << "Delete msg";
    popupmsg *tmpMsg = qobject_cast<popupmsg *> (sender());
    qDebug() << "Delete msg 2";
    QString key = popups.key(tmpMsg);
    qDebug() << "Delete msg 3";
    popups.remove(key);
    qDebug() << "Delete msg 4";
    tmpMsg->hide();
    delete tmpMsg;
}
