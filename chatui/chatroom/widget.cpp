#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    tcpSocket = new QTcpSocket(this);
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::AnyIPv4, G_PORT, QUdpSocket::ShareAddress|QUdpSocket::ReuseAddressHint);
    udpSocket->joinMulticastGroup(QHostAddress(GROUP_IP));
    tcpSocket->connectToHost(QHostAddress(SERVER_IP), SERVER_PORT);
    connect(udpSocket, &QUdpSocket::readyRead, this, &Widget::recvUdpMsg);
    connect(ui->sendBtn, &QPushButton::clicked, this, &Widget::sndMsg);
}

void Widget::recvUdpMsg(){
    QByteArray datagram;
    datagram.resize(udpSocket->pendingDatagramSize());
    udpSocket->readDatagram(datagram.data(), datagram.size());
    ui->msgBrowser->append(QString(datagram));
}

QString Widget::getMsg(QTextEdit *msgTxtEdit){
    QString msg = msgTxtEdit->toPlainText();
    msgTxtEdit->clear();
    msgTxtEdit->setFocus();
    return msg;
}

void Widget::sndMsg(){
    QString msg = getMsg(ui->msgTxtEdit);
    if(msg == ""){
        QMessageBox::warning(this,"警告","发送的聊天内容不能为空!");
        return;
    }
    tcpSocket->write(msg.toUtf8());
    tcpSocket->flush();
}

Widget::~Widget()
{
    delete ui;
}
