#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QTextEdit>
#include <QMessageBox>
#include <QCloseEvent>
#include "config.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QString userName, QString uid, QWidget *parent = 0);
    void closeEvent(QCloseEvent *);
    ~Widget();
private slots:
    void recvUdpMsg();
    void sndMsg();
    QString getMsg(QTextEdit* msgTxtEdit);
private:
    Ui::Widget *ui;
    QString uid;
    QString userName;
    QTcpSocket* tcpSocket;
    QUdpSocket* udpSocket;
};

#endif // WIDGET_H
