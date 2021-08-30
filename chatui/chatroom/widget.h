#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QTextEdit>
#include <QMessageBox>
#include <QCloseEvent>

#define GROUP_IP "239.0.0.2"
#define G_PORT 9000
#define SERVER_PORT 5005
#define SERVER_IP "127.0.0.1"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
private slots:
    void recvUdpMsg();
    void sndMsg();
    QString getMsg(QTextEdit* msgTxtEdit);
private:
    Ui::Widget *ui;
    QTcpSocket* tcpSocket;
    QUdpSocket* udpSocket;
};

#endif // WIDGET_H
