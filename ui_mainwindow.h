/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *sendPushButton;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *FriendNameLabel;
    QTextBrowser *chatTextBrowser;
    QLabel *label_5;
    QTextEdit *chatTextEdit;
    QPushButton *searchPushButton;
    QPushButton *transPushButton;
    QListView *listView;
    QLabel *userHead;
    QLabel *label;
    QLabel *HeadTitleBg;
    QLabel *label_4;
    QLabel *birthdayLabel;
    QLabel *label_6;
    QLabel *EmailLabel;
    QLabel *label_7;
    QLabel *PhoneLabel;
    QLabel *label_8;
    QLabel *sexLabel;
    QLabel *label_9;
    QLabel *introLabel;
    QLabel *StateLabel;
    QLabel *FriendHead;
    QLabel *OriginalBg;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(991, 500);
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(11);
        MainWindow->setFont(font);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        sendPushButton = new QPushButton(centralWidget);
        sendPushButton->setObjectName(QString::fromUtf8("sendPushButton"));
        sendPushButton->setGeometry(QRect(650, 372, 85, 24));
        sendPushButton->setFont(font);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(0, 0, 251, 71));
        label_2->setFrameShape(QFrame::Box);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setPixmap(QPixmap(QString::fromUtf8("../../\345\276\256\344\277\241/img/search.jpg")));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(250, 0, 492, 67));
        label_3->setFrameShape(QFrame::Box);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setPixmap(QPixmap(QString::fromUtf8("../../\345\276\256\344\277\241/img/title.jpg")));
        FriendNameLabel = new QLabel(centralWidget);
        FriendNameLabel->setObjectName(QString::fromUtf8("FriendNameLabel"));
        FriendNameLabel->setGeometry(QRect(330, 10, 121, 31));
        FriendNameLabel->setFont(font);
        FriendNameLabel->setAutoFillBackground(false);
        FriendNameLabel->setFrameShape(QFrame::NoFrame);
        FriendNameLabel->setFrameShadow(QFrame::Plain);
        FriendNameLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        chatTextBrowser = new QTextBrowser(centralWidget);
        chatTextBrowser->setObjectName(QString::fromUtf8("chatTextBrowser"));
        chatTextBrowser->setGeometry(QRect(250, 65, 491, 300));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(250, 365, 492, 40));
        label_5->setFrameShape(QFrame::Box);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setPixmap(QPixmap(QString::fromUtf8("../../\345\276\256\344\277\241/img/tool.jpg")));
        chatTextEdit = new QTextEdit(centralWidget);
        chatTextEdit->setObjectName(QString::fromUtf8("chatTextEdit"));
        chatTextEdit->setGeometry(QRect(250, 403, 491, 97));
        searchPushButton = new QPushButton(centralWidget);
        searchPushButton->setObjectName(QString::fromUtf8("searchPushButton"));
        searchPushButton->setGeometry(QRect(20, 30, 191, 26));
        searchPushButton->setFlat(true);
        transPushButton = new QPushButton(centralWidget);
        transPushButton->setObjectName(QString::fromUtf8("transPushButton"));
        transPushButton->setGeometry(QRect(270, 370, 31, 23));
        transPushButton->setFlat(true);
        listView = new QListView(centralWidget);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setGeometry(QRect(0, 65, 250, 435));
        userHead = new QLabel(centralWidget);
        userHead->setObjectName(QString::fromUtf8("userHead"));
        userHead->setGeometry(QRect(830, 10, 71, 71));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(770, 100, 191, 16));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font1.setPointSize(14);
        label->setFont(font1);
        label->setAlignment(Qt::AlignCenter);
        HeadTitleBg = new QLabel(centralWidget);
        HeadTitleBg->setObjectName(QString::fromUtf8("HeadTitleBg"));
        HeadTitleBg->setGeometry(QRect(743, 1, 251, 131));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(780, 180, 41, 21));
        birthdayLabel = new QLabel(centralWidget);
        birthdayLabel->setObjectName(QString::fromUtf8("birthdayLabel"));
        birthdayLabel->setGeometry(QRect(800, 210, 121, 16));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(780, 240, 51, 21));
        EmailLabel = new QLabel(centralWidget);
        EmailLabel->setObjectName(QString::fromUtf8("EmailLabel"));
        EmailLabel->setGeometry(QRect(800, 270, 121, 16));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(780, 300, 51, 21));
        PhoneLabel = new QLabel(centralWidget);
        PhoneLabel->setObjectName(QString::fromUtf8("PhoneLabel"));
        PhoneLabel->setGeometry(QRect(800, 330, 121, 16));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(780, 130, 41, 21));
        sexLabel = new QLabel(centralWidget);
        sexLabel->setObjectName(QString::fromUtf8("sexLabel"));
        sexLabel->setGeometry(QRect(800, 156, 121, 16));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(780, 360, 71, 21));
        introLabel = new QLabel(centralWidget);
        introLabel->setObjectName(QString::fromUtf8("introLabel"));
        introLabel->setGeometry(QRect(790, 390, 161, 71));
        QFont font2;
        font2.setPointSize(10);
        introLabel->setFont(font2);
        introLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        introLabel->setWordWrap(true);
        StateLabel = new QLabel(centralWidget);
        StateLabel->setObjectName(QString::fromUtf8("StateLabel"));
        StateLabel->setGeometry(QRect(330, 42, 121, 21));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font3.setPointSize(9);
        StateLabel->setFont(font3);
        StateLabel->setAutoFillBackground(false);
        StateLabel->setFrameShape(QFrame::NoFrame);
        StateLabel->setFrameShadow(QFrame::Plain);
        StateLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        FriendHead = new QLabel(centralWidget);
        FriendHead->setObjectName(QString::fromUtf8("FriendHead"));
        FriendHead->setGeometry(QRect(264, 8, 50, 50));
        FriendHead->setAutoFillBackground(false);
        OriginalBg = new QLabel(centralWidget);
        OriginalBg->setObjectName(QString::fromUtf8("OriginalBg"));
        OriginalBg->setGeometry(QRect(250, -1, 491, 501));
        MainWindow->setCentralWidget(centralWidget);
        HeadTitleBg->raise();
        label_5->raise();
        chatTextEdit->raise();
        sendPushButton->raise();
        label_2->raise();
        label_3->raise();
        FriendNameLabel->raise();
        chatTextBrowser->raise();
        searchPushButton->raise();
        transPushButton->raise();
        listView->raise();
        userHead->raise();
        label->raise();
        label_4->raise();
        birthdayLabel->raise();
        label_6->raise();
        EmailLabel->raise();
        label_7->raise();
        PhoneLabel->raise();
        label_8->raise();
        sexLabel->raise();
        label_9->raise();
        introLabel->raise();
        StateLabel->raise();
        FriendHead->raise();
        OriginalBg->raise();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        sendPushButton->setText(QCoreApplication::translate("MainWindow", "\345\217\221 \351\200\201(S)", nullptr));
        label_2->setText(QString());
        label_3->setText(QString());
        FriendNameLabel->setText(QCoreApplication::translate("MainWindow", "FriendName", nullptr));
        label_5->setText(QString());
        searchPushButton->setText(QString());
        transPushButton->setText(QString());
        userHead->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "userName", nullptr));
        HeadTitleBg->setText(QString());
        label_4->setText(QCoreApplication::translate("MainWindow", "\347\224\237\346\227\245", nullptr));
        birthdayLabel->setText(QCoreApplication::translate("MainWindow", "birthday", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        EmailLabel->setText(QCoreApplication::translate("MainWindow", "Email@edu.cn", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\347\224\265\350\257\235", nullptr));
        PhoneLabel->setText(QCoreApplication::translate("MainWindow", "+86XXX", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\346\200\247\345\210\253", nullptr));
        sexLabel->setText(QCoreApplication::translate("MainWindow", "sex", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "\344\270\252\344\272\272\347\256\200\344\273\213", nullptr));
        introLabel->setText(QCoreApplication::translate("MainWindow", "\346\210\221\346\230\257\351\230\277\345\267\264\351\230\277\345\267\264\351\230\277\345\267\264\345\267\264\345\267\264\345\267\264\351\230\277\345\267\264\345\267\264", nullptr));
        StateLabel->setText(QCoreApplication::translate("MainWindow", "FriendState", nullptr));
        FriendHead->setText(QString());
        OriginalBg->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
