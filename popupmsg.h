#ifndef POPUPMSG_H
#define POPUPMSG_H

#include <QWidget>

static int closeWidth = 360;
static int closeHeight = 120;
static int widthText = 280;
static int openwidthText = 540;
static int heightText = 100;
static int openWidth = 620;

namespace Ui {
class popupmsg;
}

class popupmsg : public QWidget
{
    Q_OBJECT

public:
    explicit popupmsg(QWidget *parent = 0);
    ~popupmsg();
    void setText(const QString &text);

    bool getFile() const;
    void setFile(bool value);
    void showMessage();

private:
    void paintEvent(QPaintEvent *event );
    void mouseDoubleClickEvent ( QMouseEvent * event );

signals:
    void openedMsg(bool);

private:
    Ui::popupmsg *ui;
    QPixmap warnIcon;
    QPixmap fileIcon;
    bool file;
    bool bigMsg;
    bool openMessage;
};

#endif // POPUPMSG_H
