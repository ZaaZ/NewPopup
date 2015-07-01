#include "popupmsg.h"
#include "ui_popupmsg.h"

#include <QPainter>
#include <QDebug>
#include <QGraphicsDropShadowEffect>

popupmsg::popupmsg(QWidget *parent) :
    QWidget(parent),
    warnIcon("E:\\qt\\NewPopup\\NewPopup\\435.png"),
    fileIcon("E:\\qt\\NewPopup\\NewPopup\\file.png"),
    ui(new Ui::popupmsg)
{
    ui->setupUi(this);
    file = false;
    bigMsg = false;
    openMessage = false;
    QGraphicsDropShadowEffect *effect=new QGraphicsDropShadowEffect();
    effect->setBlurRadius(5);
    effect->setXOffset(5);
    effect->setYOffset(5);
    setGraphicsEffect(effect);
    resize(closeWidth, closeHeight);
}

popupmsg::~popupmsg()
{
    delete ui;
}

void popupmsg::setText(const QString &text)
{
    QFontMetrics fm(this->font());
    int row = (int) ui->labelMsg->height() / (int) fm.height();
    qDebug() << "Row" << row;
    int fullwidth = row * ui->labelMsg->width();
    QString elidText = fm.elidedText(text,Qt::ElideRight, fullwidth-150);
    if (elidText.length()< text.length()){
        bigMsg = true;
    }
    qDebug() << "Row" << row << "fullwidth" << fullwidth;
    ui->labelMsg->setText(elidText);
    ui->labelMsg->setToolTip(text);
}

void popupmsg::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    QBrush r(QColor("#e53935"));
    QBrush h(QColor("#d7d7d7"));
    int x = 40;
    QRect left(QPoint(0,0),QSize(x,this->height()));
    p.setBrushOrigin(left.topLeft());
    p.fillRect(left, r);
    QRect right(QPoint(x,0),QSize(this->width()-x,this->height()));
    p.setBrushOrigin(right.topLeft());
    p.fillRect(right, h);
    int xi = x - warnIcon.width()/2;
    QPoint picon(xi,this->height() - xi - warnIcon.height());
    p.drawPixmap(picon,warnIcon);

    if (file){
        xi = x - fileIcon.width()/2;
        QPoint ficon(xi,10);
        p.drawPixmap(ficon,fileIcon);
    }

    QWidget::paintEvent(event);
}

void popupmsg::mouseDoubleClickEvent(QMouseEvent *event)
{
        qDebug() << "Double Click";
    if (bigMsg){
        if (openMessage)
            openMessage = false;
        else
            openMessage = true;
        showMessage();
        emit openedMsg(openMessage);
    }
    QWidget::mouseDoubleClickEvent(event);
}


bool popupmsg::getFile() const
{
    return file;
}

void popupmsg::setFile(bool value)
{
    file = value;
}

void popupmsg::showMessage()
{
    QFontMetrics fm(this->font());
    QString tmp = ui->labelMsg->toolTip();
    if (openMessage){
     QRect textRect = fm.boundingRect(QRect(QPoint(0,0),QPoint(openwidthText,100)),Qt::TextWordWrap,tmp);
     qDebug() << textRect;
     ui->labelMsg->setText(tmp);
     ui->labelMsg->resize(textRect.width(),textRect.height());
     resize(openWidth, textRect.height()+19);
     qDebug() << rect();
    } else {
        ui->labelMsg->resize(widthText,heightText);
        int row = (int) ui->labelMsg->height() / (int) fm.height();
        int fullwidth = row * ui->labelMsg->width();
        QString elidText = fm.elidedText(tmp,Qt::ElideRight, fullwidth-150);
        ui->labelMsg->setText(elidText);
        resize(closeWidth,closeHeight);
        qDebug() << rect();
    }
}


