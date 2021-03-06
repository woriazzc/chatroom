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
    QString msg = QString(LOGIN) + "\n" + user + "\n" + pwd;
    tcpSocket->write(msg.toUtf8());
    this->userName = user;
}

void Login::recvMsg(){
    QString msg = tcpSocket->readAll();
    QString type = msg.section('\n', 0, 0);
    if(type == LOGIN){
        if(msg.section('\n', 1, 1) == "0"){
            QMessageBox::warning(this, "错误", "用户名或密码错误!");
            return;
        }
        else if(msg.section('\n', 1, 1) == "-1"){
            QMessageBox::warning(this, "错误", "用户已在线!");
            return;
        }
        else{
            Widget* w = new Widget(this->userName, msg.section('\n', 1, 1));
            w->show();
            this->close();
        }
    }
    else if(type == ENROLL){
        if(msg.section('\n', 1, 1) == "0"){
            QMessageBox::warning(this, "错误", "注册失败!");
            return;
        }
        else{
            Widget* w = new Widget(this->userName, msg.section('\n', 1, 1));
            w->show();
            this->close();
        }
    }
}

void Login::sndEnrMsg(){
    QString user = ui->userTxt->text();
    QString pwd = ui->pwdTxt->text();
    QString msg = QString(ENROLL) + "\n" + user + "\n" + pwd;
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
