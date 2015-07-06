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

void MainWindow::resizeEvent(QResizeEvent *event)
{
    bool isHideMsg = false;
    int x;
    for (int i = 0; i < popups->size(); i++){
        popupmsg *tmpP = popups->at(i);
        x = width()-tmpP->width()-interval_msg;
        tmpP->move(x,tmpP->y());
        if (height()-tmpP->height()-interval_msg > tmpP->y())
            tmpP->show();
        else {
            tmpP->hide();
            isHideMsg = true;
        }
    }
    if (x - interval_msg - cntmsg->width() > 0 && isHideMsg){
        cntmsg->move(x - interval_msg - cntmsg->width(),20);
        cntmsg->show();
    } else {
        cntmsg->hide();
    }
    QWidget::resizeEvent(event);
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
            int cntMsgX = x - interval_msg - cntmsg->width();
            if (cntmsg->isHidden() && cntMsgX > 0){
                cntmsg->move(cntMsgX,20);
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
    int num = popups->indexOf(tmpMsg);
    if (show){
        //показываем
        tmpMsg->move(width()-tmpMsg->width()-interval_msg,tmpMsg->y());
        coordY = tmpMsg->y() + tmpMsg->height() + interval_msg;
    } else {
        //скрываем
        tmpMsg->move(width()-tmpMsg->width()-interval_msg,tmpMsg->y());
        coordY = tmpMsg->y() + tmpMsg->height() + interval_msg;
    }
        for (int i = num+1; i < popups->size(); i++){
            popupmsg *tmpP = popups->at(i);
            tmpP->move(tmpP->x(),coordY);
            coordY = tmpP->y()+tmpP->height()+interval_msg;
            if (coordY > height())
                tmpP->hide();
            else
                tmpP->show();
        }

    //перерисовываем сообщения ниже
}

void MainWindow::deleteMsg()
{        
    popupmsg *tmpMsg = qobject_cast<popupmsg *> (sender());
    disconnect(tmpMsg,SIGNAL(deleteMsg()),this,SLOT(deleteMsg()));
    int offsetMsg = tmpMsg->height()+interval_msg;
    qDebug() << offsetMsg;
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
    int cntIter = (int) offsetMsg/ (int) 40;
    int cntOst = offsetMsg-cntIter*40;
    qDebug() << cntIter << cntOst;

    if (cntOst > 0)
        for (int i = num; i < popups->size(); i++){
             popups->at(i)->move(popups->at(i)->x(),popups->at(i)->y()-cntOst);
             if (popups->at(i)->isHidden()){
                    popups->at(i)->show();
                    break;
                }
            }
    for (int i = 1; i <= cntIter; i++) {
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
