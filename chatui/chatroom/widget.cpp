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
}

void Widget::recvUdpMsg(){
    QByteArray datagram;
    datagram.resize(udpSocket->pendingDatagramSize());
    udpSocket->readDatagram(datagram.data(), datagram.size());
    ui->msgBrowser->append(QString(datagram));
}

Widget::~Widget()
{
    delete ui;
}
