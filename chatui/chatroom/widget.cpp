#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QTextStream>
#include <QColorDialog>
#include <QDateTime>
#include <QFontComboBox>

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

    connect(ui->boldTBtn, &QToolButton::clicked, this, [=](bool checked){
        if(checked)ui->msgTxtEdit->setFontWeight(QFont::Bold);
        else ui->msgTxtEdit->setFontWeight(QFont::Normal);
    });

    connect(ui->clearTBtn, &QToolButton::clicked, this, [=](){
        ui->msgBrowser->clear();
    });

    connect(ui->saveTBtn, &QToolButton::clicked, this, [=](){
        if(ui->msgBrowser->toPlainText() == ""){
            QMessageBox::warning(this, tr("警告"), tr("保存的聊天内容不能为空!"));
        }
        else{
            QFileDialog fileDialog;
            QString filename = fileDialog.getSaveFileName(this, tr("Save File"), "untitled", tr("Text File(*.txt)"));
            QFile file(filename);
            if(!file.open(QIODevice::WriteOnly|QIODevice::Text)){
                QMessageBox::warning(this, tr("提示"), tr("文件错误"));
                return;
            }
            QTextStream textstream(&file);
            textstream << ui->msgBrowser->toPlainText();
            QMessageBox::warning(this, tr("提示"), tr("保存成功"));
            file.close();
        }
    });

    connect(ui->colorTBtn, &QToolButton::clicked, this, [=](){
        QColor color = QColorDialog(this).getColor();
        ui->msgTxtEdit->setTextColor(color);
    });

    connect(ui->exitBtn, &QPushButton::clicked, this, [=](){
        this->close();
    });

    connect(ui->italicTbtn, &QToolButton::clicked, this, [=](bool checked){
        ui->msgTxtEdit->setFontItalic(checked);
        ui->msgTxtEdit->setFocus();
    });

    connect(ui->underlineTBtn, &QToolButton::clicked, this, [=](bool checked){
        ui->msgTxtEdit->setFontUnderline(checked);
        ui->msgTxtEdit->setFocus();
    });

    connect(ui->fontCbx, QFontComboBox::currentFontChanged, this, [=](const QFont &font){
        ui->msgTxtEdit->setFontFamily(font.toString());
        ui->msgTxtEdit->setFocus();
    });

    connect(ui->sizeCbx, static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged), [=](const QString &text){
        ui->msgTxtEdit->setFontPointSize(text.toDouble());
        ui->msgTxtEdit->setFocus();
    });
}

void Widget::recvUdpMsg(){
    QByteArray datagram;
    datagram.resize(udpSocket->pendingDatagramSize());
    udpSocket->readDatagram(datagram.data(), datagram.size());
    QString msg = QString(datagram).trimmed();
    if(msg.contains("\n")){
        QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        ui->msgBrowser->setTextColor(QColor(Qt::blue));
        ui->msgBrowser->append(msg.section('\n', 0, 0).trimmed() + QString(":  ") + time);
        ui->msgBrowser->setTextColor(QColor(Qt::black));
        ui->msgBrowser->append(msg.section('\n', 1));
        ui->msgBrowser->append(QString("\n"));
    }
    else{
        QColor col;
        col.setRgb(150, 150, 150);
        ui->msgBrowser->setTextColor(col);
        ui->msgBrowser->append(msg);
        ui->msgBrowser->append(QString("\n"));
        ui->msgBrowser->setTextColor(QColor(Qt::black));
    }
}

QString Widget::getMsg(QTextEdit *msgTxtEdit){
    QString msg = msgTxtEdit->toHtml();
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
