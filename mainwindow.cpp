#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QUuid>
#include <QDebug>
#include <stdio.h>

#include <QGraphicsDropShadowEffect>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    coordY = 20;
    cntmsg = new CountMsg(this);
    cntmsg->setHidden(true);
    popups = new QList<popupmsg *>();
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
    msg->setText(QString::number(popups->size()+1)+text);
    msg->setFile(true);
    int x = width()-msg->width()-interval_msg;
    msg->move(x,coordY);
    coordY += msg->height()+interval_msg;
    QString Id = QUuid::createUuid().toRfc4122().toHex();
    popups->append(msg);
    if (height()> coordY)
        msg->show();
    else {
            qDebug() << "Update cntmsg";
            cntmsg->setCount(popups->size());
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
    popupmsg *tmpMsg = qobject_cast<popupmsg *> (sender());
    int offsetMsg = tmpMsg->height()+interval_msg;
    int num = popups->indexOf(tmpMsg);
    popups->removeAt(num);
    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(this);
    tmpMsg->setGraphicsEffect(opacityEffect);
    for (float i = 0.8; i > 0; i -= 0.2){
        opacityEffect->setOpacity(i);
        QApplication::processEvents();
        Sleeper::msleep(50);
    }
    tmpMsg->hide();
    for (int i = num; i < popups->size(); i++){
         popups->at(i)->move(popups->at(i)->x(),popups->at(i)->y()-10);
         if (popups->at(i)->isHidden()){
                popups->at(i)->show();
                break;
            }
        }
    for (int i = 1; i < 4; i++) {
        QApplication::processEvents();
        //Sleeper::msleep(5);
        for (int x = num; x < popups->size(); x++){
            if (popups->at(x)->isHidden())
                break;
            popups->at(x)->move(popups->at(x)->x(),popups->at(x)->y()-40);
        }
    }
    for (int i = num; i < popups->size(); i++)
        if (popups->at(i)->isHidden())
            popups->at(i)->move(popups->at(i)->x(),popups->at(i)->y()-offsetMsg);
    coordY -= offsetMsg;
    if (height()> coordY)
            cntmsg->hide();
    else {
        cntmsg->setCount(popups->size());
        cntmsg->update();
        }
    //delete tmpMsg;
}
