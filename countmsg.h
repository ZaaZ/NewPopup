#ifndef COUNTMSG_H
#define COUNTMSG_H

#include <QWidget>

namespace Ui {
class CountMsg;
}

class CountMsg : public QWidget
{
    Q_OBJECT

public:
    explicit CountMsg(QWidget *parent = 0);
    ~CountMsg();

    void setCount(int cnt);

private:
    Ui::CountMsg *ui;
};

#endif // COUNTMSG_H
