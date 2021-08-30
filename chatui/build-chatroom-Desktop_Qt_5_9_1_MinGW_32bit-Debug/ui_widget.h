/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QHBoxLayout *horizontalLayout_13;
    QWidget *widget_8;
    QHBoxLayout *horizontalLayout_7;
    QWidget *widget_9;
    QVBoxLayout *verticalLayout_4;
    QWidget *widget_10;
    QVBoxLayout *verticalLayout_5;
    QWidget *widget_11;
    QVBoxLayout *verticalLayout_6;
    QWidget *widget_12;
    QHBoxLayout *horizontalLayout_8;
    QTextBrowser *msgBrowser;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout_9;
    QFontComboBox *fontCbx;
    QComboBox *sizeCbx;
    QToolButton *boldTBtn;
    QToolButton *italicTbtn;
    QToolButton *underlineTBtn;
    QToolButton *colorTBtn;
    QToolButton *saveTBtn;
    QToolButton *clearTBtn;
    QTextEdit *msgTxtEdit;
    QWidget *widget_14;
    QHBoxLayout *horizontalLayout_11;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *sendBtn;
    QSpacerItem *horizontalSpacer_5;
    QLabel *userNumLbl;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *exitBtn;
    QWidget *widget_15;
    QHBoxLayout *horizontalLayout_12;
    QTableWidget *tableWidget;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(851, 835);
        horizontalLayout_13 = new QHBoxLayout(Widget);
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        widget_8 = new QWidget(Widget);
        widget_8->setObjectName(QStringLiteral("widget_8"));
        horizontalLayout_7 = new QHBoxLayout(widget_8);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        widget_9 = new QWidget(widget_8);
        widget_9->setObjectName(QStringLiteral("widget_9"));
        verticalLayout_4 = new QVBoxLayout(widget_9);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        widget_10 = new QWidget(widget_9);
        widget_10->setObjectName(QStringLiteral("widget_10"));
        verticalLayout_5 = new QVBoxLayout(widget_10);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        widget_11 = new QWidget(widget_10);
        widget_11->setObjectName(QStringLiteral("widget_11"));
        verticalLayout_6 = new QVBoxLayout(widget_11);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        widget_12 = new QWidget(widget_11);
        widget_12->setObjectName(QStringLiteral("widget_12"));
        horizontalLayout_8 = new QHBoxLayout(widget_12);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        msgBrowser = new QTextBrowser(widget_12);
        msgBrowser->setObjectName(QStringLiteral("msgBrowser"));
        QFont font;
        font.setPointSize(14);
        msgBrowser->setFont(font);

        horizontalLayout_8->addWidget(msgBrowser);


        verticalLayout_6->addWidget(widget_12);

        frame_3 = new QFrame(widget_11);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setFrameShape(QFrame::Box);
        horizontalLayout_9 = new QHBoxLayout(frame_3);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        fontCbx = new QFontComboBox(frame_3);
        fontCbx->setObjectName(QStringLiteral("fontCbx"));
        fontCbx->setEnabled(true);
        QFont font1;
        font1.setPointSize(11);
        fontCbx->setFont(font1);

        horizontalLayout_9->addWidget(fontCbx);

        sizeCbx = new QComboBox(frame_3);
        sizeCbx->setObjectName(QStringLiteral("sizeCbx"));
        sizeCbx->setFont(font1);

        horizontalLayout_9->addWidget(sizeCbx);

        boldTBtn = new QToolButton(frame_3);
        boldTBtn->setObjectName(QStringLiteral("boldTBtn"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/bold.png"), QSize(), QIcon::Normal, QIcon::Off);
        boldTBtn->setIcon(icon);
        boldTBtn->setCheckable(true);

        horizontalLayout_9->addWidget(boldTBtn);

        italicTbtn = new QToolButton(frame_3);
        italicTbtn->setObjectName(QStringLiteral("italicTbtn"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/italic.png"), QSize(), QIcon::Normal, QIcon::Off);
        italicTbtn->setIcon(icon1);
        italicTbtn->setCheckable(true);

        horizontalLayout_9->addWidget(italicTbtn);

        underlineTBtn = new QToolButton(frame_3);
        underlineTBtn->setObjectName(QStringLiteral("underlineTBtn"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/under.png"), QSize(), QIcon::Normal, QIcon::Off);
        underlineTBtn->setIcon(icon2);
        underlineTBtn->setCheckable(true);

        horizontalLayout_9->addWidget(underlineTBtn);

        colorTBtn = new QToolButton(frame_3);
        colorTBtn->setObjectName(QStringLiteral("colorTBtn"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/color.png"), QSize(), QIcon::Normal, QIcon::Off);
        colorTBtn->setIcon(icon3);

        horizontalLayout_9->addWidget(colorTBtn);

        saveTBtn = new QToolButton(frame_3);
        saveTBtn->setObjectName(QStringLiteral("saveTBtn"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/images/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        saveTBtn->setIcon(icon4);

        horizontalLayout_9->addWidget(saveTBtn);

        clearTBtn = new QToolButton(frame_3);
        clearTBtn->setObjectName(QStringLiteral("clearTBtn"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/images/clear.png"), QSize(), QIcon::Normal, QIcon::Off);
        clearTBtn->setIcon(icon5);

        horizontalLayout_9->addWidget(clearTBtn);


        verticalLayout_6->addWidget(frame_3);


        verticalLayout_5->addWidget(widget_11);

        msgTxtEdit = new QTextEdit(widget_10);
        msgTxtEdit->setObjectName(QStringLiteral("msgTxtEdit"));
        msgTxtEdit->setEnabled(true);
        msgTxtEdit->setMaximumSize(QSize(16777215, 200));
        QFont font2;
        font2.setPointSize(13);
        msgTxtEdit->setFont(font2);

        verticalLayout_5->addWidget(msgTxtEdit);


        verticalLayout_4->addWidget(widget_10);

        widget_14 = new QWidget(widget_9);
        widget_14->setObjectName(QStringLiteral("widget_14"));
        horizontalLayout_11 = new QHBoxLayout(widget_14);
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_4);

        sendBtn = new QPushButton(widget_14);
        sendBtn->setObjectName(QStringLiteral("sendBtn"));

        horizontalLayout_11->addWidget(sendBtn);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_5);

        userNumLbl = new QLabel(widget_14);
        userNumLbl->setObjectName(QStringLiteral("userNumLbl"));
        QFont font3;
        font3.setPointSize(10);
        userNumLbl->setFont(font3);

        horizontalLayout_11->addWidget(userNumLbl);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_6);

        exitBtn = new QPushButton(widget_14);
        exitBtn->setObjectName(QStringLiteral("exitBtn"));

        horizontalLayout_11->addWidget(exitBtn);


        verticalLayout_4->addWidget(widget_14);


        horizontalLayout_7->addWidget(widget_9);

        widget_15 = new QWidget(widget_8);
        widget_15->setObjectName(QStringLiteral("widget_15"));
        widget_15->setMaximumSize(QSize(200, 16777215));
        horizontalLayout_12 = new QHBoxLayout(widget_15);
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        horizontalLayout_12->setContentsMargins(0, 0, 0, 0);
        tableWidget = new QTableWidget(widget_15);
        if (tableWidget->columnCount() < 1)
            tableWidget->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setFont(font1);

        horizontalLayout_12->addWidget(tableWidget);


        horizontalLayout_7->addWidget(widget_15);


        horizontalLayout_13->addWidget(widget_8);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", Q_NULLPTR));
        sizeCbx->clear();
        sizeCbx->insertItems(0, QStringList()
         << QApplication::translate("Widget", "5", Q_NULLPTR)
         << QApplication::translate("Widget", "6", Q_NULLPTR)
         << QApplication::translate("Widget", "7", Q_NULLPTR)
         << QApplication::translate("Widget", "8", Q_NULLPTR)
         << QApplication::translate("Widget", "9", Q_NULLPTR)
         << QApplication::translate("Widget", "10", Q_NULLPTR)
         << QApplication::translate("Widget", "11", Q_NULLPTR)
         << QApplication::translate("Widget", "12", Q_NULLPTR)
        );
#ifndef QT_NO_TOOLTIP
        boldTBtn->setToolTip(QApplication::translate("Widget", "\345\212\240\347\262\227", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        boldTBtn->setText(QApplication::translate("Widget", "...", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        italicTbtn->setToolTip(QApplication::translate("Widget", "\345\200\276\346\226\234", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        italicTbtn->setText(QApplication::translate("Widget", "...", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        underlineTBtn->setToolTip(QApplication::translate("Widget", "\344\270\213\345\210\222\347\272\277", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        underlineTBtn->setText(QApplication::translate("Widget", "...", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        colorTBtn->setToolTip(QApplication::translate("Widget", "\351\242\234\350\211\262", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        colorTBtn->setText(QApplication::translate("Widget", "...", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        saveTBtn->setToolTip(QApplication::translate("Widget", "\344\277\235\345\255\230", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        saveTBtn->setText(QApplication::translate("Widget", "...", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        clearTBtn->setToolTip(QApplication::translate("Widget", "\346\270\205\347\251\272", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        clearTBtn->setText(QApplication::translate("Widget", "...", Q_NULLPTR));
        sendBtn->setText(QApplication::translate("Widget", "\345\217\221\351\200\201", Q_NULLPTR));
        userNumLbl->setText(QApplication::translate("Widget", "\345\234\250\347\272\277\344\272\272\346\225\260:0\344\272\272", Q_NULLPTR));
        exitBtn->setText(QApplication::translate("Widget", "\351\200\200\345\207\272", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("Widget", "\347\224\250\346\210\267\345\220\215:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
