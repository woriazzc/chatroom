#include "login.h"
#include "ui_login.h"
#include "widget.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    tcpSocket = new QTcpSocket(this);
    tcpSocket->connectToHost(QHostAddress(SERVER_IP), SERVER_PORT);

    connect(ui->enr_btn, &QPushButton::clicked, this, &Login::sndEnrMsg);

    connect(ui->acc_btn, &QPushButton::clicked, this, &Login::sndAccMsg);

    connect(tcpSocket, &QTcpSocket::readyRead, this, &Login::recvMsg);
}

void Login::sndAccMsg(){
    QString user = ui->userTxt->text();
    QString pwd = ui->pwdTxt->text();
    QString msg = "0\n" + user + "\n" + pwd;
    tcpSocket->write(msg.toUtf8());
    this->userName = user;
}

void Login::recvMsg(){
    QString msg = tcpSocket->readAll();
    QString type = msg.section('\n', 0, 0);
    if(type == "0"){
        if(msg.section('\n', 1, 1) == "1"){
            Widget* w = new Widget(this->userName);
            w->show();
            this->close();
        }
        else{
            QMessageBox::warning(this, "错误", "用户名或密码错误!");
            return;
        }
    }
    else if(type == "3"){
        if(msg.section('\n', 1, 1) == "1"){
            Widget* w = new Widget(this->userName);
            w->show();
            this->close();
        }
        else{
            QMessageBox::warning(this, "错误", "注册失败!");
            return;
        }
    }
}

void Login::sndEnrMsg(){
    QString user = ui->userTxt->text();
    QString pwd = ui->pwdTxt->text();
    QString msg = "3\n" + user + "\n" + pwd;
    tcpSocket->write(msg.toUtf8());
    this->userName = user;
}

void Login::closeEvent(QCloseEvent * event){
    tcpSocket->close();
    tcpSocket->destroyed();
    event->accept();
}

Login::~Login()
{
    delete ui;
}
