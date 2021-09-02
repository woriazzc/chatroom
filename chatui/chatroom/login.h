#ifndef LOGIN_H
#define LOGIN_H

#include "config.h"
#include <QWidget>
#include <QTcpSocket>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    void closeEvent(QCloseEvent *);
    ~Login();
private slots:
    void sndAccMsg();
    void recvMsg();
    void sndEnrMsg();
private:
    QString userName;
    Ui::Login *ui;
    QTcpSocket* tcpSocket;
};

#endif // LOGIN_H
