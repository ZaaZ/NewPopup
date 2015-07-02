#include "countmsg.h"
#include "ui_countmsg.h"

CountMsg::CountMsg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CountMsg)
{
    ui->setupUi(this);
}

CountMsg::~CountMsg()
{
    delete ui;
}

void CountMsg::setCount(int cnt)
{
    ui->label->setText(QString::number(cnt));
}
