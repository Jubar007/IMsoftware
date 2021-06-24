/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *FriendNameLabel;
    QTextBrowser *chatTextBrowser;
    QLabel *label_5;
    QTextEdit *chatTextEdit;
    QListView *listView;
    QLabel *userHead;
    QLabel *label;
    QLabel *HeadTitleBg;
    QLabel *birthdayLabel;
    QLabel *EmailLabel;
    QLabel *PhoneLabel;
    QLabel *sexLabel;
    QLabel *label_9;
    QLabel *introLabel;
    QLabel *StateLabel;
    QLabel *FriendHead;
    QLabel *OriginalBg;
    QLabel *navLabel;
    QPushButton *contactsPushButton;
    QPushButton *groupPushButton;
    QLabel *nickNameLabel;
    QLabel *groupLabel;
    QLabel *G_groupHead;
    QLabel *G_groupNameLabel;
    QLabel *G_introLabel;
    QLabel *G_NoticeLabel;
    QLabel *G_menberTitleLabel;
    QListView *G_listView;
    QPushButton *perfectInfoPushButton;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *historySave;
    QPushButton *clearHistory;
    QPushButton *transPushButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *sendPushButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(991, 500);
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(11);
        MainWindow->setFont(font);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(0, 0, 251, 71));
        label_2->setFrameShape(QFrame::Box);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setPixmap(QPixmap(QString::fromUtf8("../../\345\276\256\344\277\241/img/search.jpg")));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(250, 0, 492, 67));
        label_3->setFrameShape(QFrame::Box);
        label_3->setFrameShadow(QFrame::Sunken);
        FriendNameLabel = new QLabel(centralWidget);
        FriendNameLabel->setObjectName(QStringLiteral("FriendNameLabel"));
        FriendNameLabel->setGeometry(QRect(330, 9, 121, 31));
        FriendNameLabel->setFont(font);
        FriendNameLabel->setAutoFillBackground(false);
        FriendNameLabel->setFrameShape(QFrame::NoFrame);
        FriendNameLabel->setFrameShadow(QFrame::Plain);
        FriendNameLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        chatTextBrowser = new QTextBrowser(centralWidget);
        chatTextBrowser->setObjectName(QStringLiteral("chatTextBrowser"));
        chatTextBrowser->setGeometry(QRect(250, 65, 491, 300));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(250, 365, 492, 40));
        label_5->setFrameShape(QFrame::Box);
        label_5->setFrameShadow(QFrame::Sunken);
        chatTextEdit = new QTextEdit(centralWidget);
        chatTextEdit->setObjectName(QStringLiteral("chatTextEdit"));
        chatTextEdit->setGeometry(QRect(250, 403, 491, 97));
        listView = new QListView(centralWidget);
        listView->setObjectName(QStringLiteral("listView"));
        listView->setGeometry(QRect(0, 65, 250, 391));
        userHead = new QLabel(centralWidget);
        userHead->setObjectName(QStringLiteral("userHead"));
        userHead->setGeometry(QRect(833, 30, 60, 55));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(770, 100, 191, 16));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font1.setPointSize(14);
        label->setFont(font1);
        label->setAlignment(Qt::AlignCenter);
        HeadTitleBg = new QLabel(centralWidget);
        HeadTitleBg->setObjectName(QStringLiteral("HeadTitleBg"));
        HeadTitleBg->setGeometry(QRect(740, 1, 255, 500));
        birthdayLabel = new QLabel(centralWidget);
        birthdayLabel->setObjectName(QStringLiteral("birthdayLabel"));
        birthdayLabel->setGeometry(QRect(775, 171, 190, 18));
        QFont font2;
        font2.setPointSize(10);
        birthdayLabel->setFont(font2);
        EmailLabel = new QLabel(centralWidget);
        EmailLabel->setObjectName(QStringLiteral("EmailLabel"));
        EmailLabel->setGeometry(QRect(775, 276, 190, 18));
        EmailLabel->setFont(font2);
        PhoneLabel = new QLabel(centralWidget);
        PhoneLabel->setObjectName(QStringLiteral("PhoneLabel"));
        PhoneLabel->setGeometry(QRect(775, 311, 190, 18));
        PhoneLabel->setFont(font2);
        sexLabel = new QLabel(centralWidget);
        sexLabel->setObjectName(QStringLiteral("sexLabel"));
        sexLabel->setGeometry(QRect(775, 136, 190, 18));
        sexLabel->setFont(font2);
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(775, 346, 190, 18));
        label_9->setFont(font2);
        introLabel = new QLabel(centralWidget);
        introLabel->setObjectName(QStringLiteral("introLabel"));
        introLabel->setGeometry(QRect(790, 370, 161, 51));
        introLabel->setFont(font2);
        introLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        introLabel->setWordWrap(true);
        StateLabel = new QLabel(centralWidget);
        StateLabel->setObjectName(QStringLiteral("StateLabel"));
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
        FriendHead->setObjectName(QStringLiteral("FriendHead"));
        FriendHead->setGeometry(QRect(272, 14, 45, 40));
        FriendHead->setAutoFillBackground(false);
        OriginalBg = new QLabel(centralWidget);
        OriginalBg->setObjectName(QStringLiteral("OriginalBg"));
        OriginalBg->setGeometry(QRect(250, 20, 491, 500));
        navLabel = new QLabel(centralWidget);
        navLabel->setObjectName(QStringLiteral("navLabel"));
        navLabel->setGeometry(QRect(0, 450, 250, 61));
        navLabel->setFrameShape(QFrame::Box);
        navLabel->setFrameShadow(QFrame::Sunken);
        navLabel->setPixmap(QPixmap(QString::fromUtf8("../../\345\276\256\344\277\241/img/search.jpg")));
        contactsPushButton = new QPushButton(centralWidget);
        contactsPushButton->setObjectName(QStringLiteral("contactsPushButton"));
        contactsPushButton->setGeometry(QRect(0, 450, 125, 61));
        contactsPushButton->setFocusPolicy(Qt::StrongFocus);
        contactsPushButton->setContextMenuPolicy(Qt::DefaultContextMenu);
        contactsPushButton->setLayoutDirection(Qt::LeftToRight);
        contactsPushButton->setFlat(true);
        groupPushButton = new QPushButton(centralWidget);
        groupPushButton->setObjectName(QStringLiteral("groupPushButton"));
        groupPushButton->setGeometry(QRect(125, 450, 125, 61));
        groupPushButton->setFocusPolicy(Qt::StrongFocus);
        groupPushButton->setContextMenuPolicy(Qt::DefaultContextMenu);
        groupPushButton->setLayoutDirection(Qt::LeftToRight);
        groupPushButton->setFlat(true);
        nickNameLabel = new QLabel(centralWidget);
        nickNameLabel->setObjectName(QStringLiteral("nickNameLabel"));
        nickNameLabel->setGeometry(QRect(775, 206, 190, 18));
        nickNameLabel->setFont(font2);
        groupLabel = new QLabel(centralWidget);
        groupLabel->setObjectName(QStringLiteral("groupLabel"));
        groupLabel->setGeometry(QRect(775, 241, 190, 18));
        groupLabel->setFont(font2);
        G_groupHead = new QLabel(centralWidget);
        G_groupHead->setObjectName(QStringLiteral("G_groupHead"));
        G_groupHead->setGeometry(QRect(760, 20, 60, 55));
        G_groupNameLabel = new QLabel(centralWidget);
        G_groupNameLabel->setObjectName(QStringLiteral("G_groupNameLabel"));
        G_groupNameLabel->setGeometry(QRect(830, 27, 141, 41));
        G_groupNameLabel->setFont(font1);
        G_groupNameLabel->setAlignment(Qt::AlignCenter);
        G_groupNameLabel->setWordWrap(true);
        G_introLabel = new QLabel(centralWidget);
        G_introLabel->setObjectName(QStringLiteral("G_introLabel"));
        G_introLabel->setGeometry(QRect(770, 120, 190, 18));
        G_introLabel->setFont(font2);
        G_NoticeLabel = new QLabel(centralWidget);
        G_NoticeLabel->setObjectName(QStringLiteral("G_NoticeLabel"));
        G_NoticeLabel->setGeometry(QRect(770, 160, 190, 18));
        G_NoticeLabel->setFont(font2);
        G_menberTitleLabel = new QLabel(centralWidget);
        G_menberTitleLabel->setObjectName(QStringLiteral("G_menberTitleLabel"));
        G_menberTitleLabel->setGeometry(QRect(802, 236, 81, 18));
        G_menberTitleLabel->setFont(font2);
        G_listView = new QListView(centralWidget);
        G_listView->setObjectName(QStringLiteral("G_listView"));
        G_listView->setGeometry(QRect(740, 270, 261, 231));
        G_listView->setLineWidth(0);
        perfectInfoPushButton = new QPushButton(centralWidget);
        perfectInfoPushButton->setObjectName(QStringLiteral("perfectInfoPushButton"));
        perfectInfoPushButton->setGeometry(QRect(880, 0, 121, 31));
        QFont font4;
        font4.setPointSize(9);
        perfectInfoPushButton->setFont(font4);
        perfectInfoPushButton->setAutoDefault(true);
        perfectInfoPushButton->setFlat(true);
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(260, 363, 471, 41));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        historySave = new QPushButton(widget);
        historySave->setObjectName(QStringLiteral("historySave"));
        historySave->setFont(font);
        historySave->setIconSize(QSize(16, 16));

        horizontalLayout->addWidget(historySave);

        clearHistory = new QPushButton(widget);
        clearHistory->setObjectName(QStringLiteral("clearHistory"));
        clearHistory->setFont(font);
        clearHistory->setIconSize(QSize(16, 16));

        horizontalLayout->addWidget(clearHistory);

        transPushButton = new QPushButton(widget);
        transPushButton->setObjectName(QStringLiteral("transPushButton"));
        transPushButton->setFont(font);
        transPushButton->setIconSize(QSize(16, 16));

        horizontalLayout->addWidget(transPushButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        sendPushButton = new QPushButton(widget);
        sendPushButton->setObjectName(QStringLiteral("sendPushButton"));
        sendPushButton->setFont(font);

        horizontalLayout->addWidget(sendPushButton);

        historySave->raise();
        clearHistory->raise();
        transPushButton->raise();
        sendPushButton->raise();
        MainWindow->setCentralWidget(centralWidget);
        label_5->raise();
        HeadTitleBg->raise();
        chatTextEdit->raise();
        label_2->raise();
        label_3->raise();
        FriendNameLabel->raise();
        chatTextBrowser->raise();
        listView->raise();
        userHead->raise();
        label->raise();
        birthdayLabel->raise();
        EmailLabel->raise();
        PhoneLabel->raise();
        sexLabel->raise();
        label_9->raise();
        introLabel->raise();
        StateLabel->raise();
        FriendHead->raise();
        navLabel->raise();
        contactsPushButton->raise();
        groupPushButton->raise();
        OriginalBg->raise();
        nickNameLabel->raise();
        groupLabel->raise();
        G_groupHead->raise();
        G_groupNameLabel->raise();
        G_introLabel->raise();
        G_NoticeLabel->raise();
        G_menberTitleLabel->raise();
        G_listView->raise();
        perfectInfoPushButton->raise();
        widget->raise();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label_2->setText(QString());
        label_3->setText(QString());
        FriendNameLabel->setText(QApplication::translate("MainWindow", "FriendName", Q_NULLPTR));
        label_5->setText(QString());
        userHead->setText(QString());
        label->setText(QApplication::translate("MainWindow", "userName", Q_NULLPTR));
        HeadTitleBg->setText(QString());
        birthdayLabel->setText(QApplication::translate("MainWindow", "birthday", Q_NULLPTR));
        EmailLabel->setText(QApplication::translate("MainWindow", "Email@edu.cn", Q_NULLPTR));
        PhoneLabel->setText(QApplication::translate("MainWindow", "+86XXX", Q_NULLPTR));
        sexLabel->setText(QApplication::translate("MainWindow", "sex", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "\344\270\252\344\272\272\347\256\200\344\273\213", Q_NULLPTR));
        introLabel->setText(QApplication::translate("MainWindow", "\346\210\221\346\230\257\351\230\277\345\267\264\351\230\277\345\267\264\351\230\277\345\267\264\345\267\264\345\267\264\345\267\264\351\230\277\345\267\264\345\267\264", Q_NULLPTR));
        StateLabel->setText(QApplication::translate("MainWindow", "FriendState", Q_NULLPTR));
        FriendHead->setText(QString());
        OriginalBg->setText(QString());
        navLabel->setText(QString());
        contactsPushButton->setText(QString());
        groupPushButton->setText(QString());
        nickNameLabel->setText(QApplication::translate("MainWindow", "nickNameLabel", Q_NULLPTR));
        groupLabel->setText(QApplication::translate("MainWindow", "groupLabel", Q_NULLPTR));
        G_groupHead->setText(QString());
        G_groupNameLabel->setText(QApplication::translate("MainWindow", "G_group NameLabel", Q_NULLPTR));
        G_introLabel->setText(QApplication::translate("MainWindow", "G_introLabel", Q_NULLPTR));
        G_NoticeLabel->setText(QApplication::translate("MainWindow", "G_NoticeLabel", Q_NULLPTR));
        G_menberTitleLabel->setText(QApplication::translate("MainWindow", "\347\276\244\346\210\220\345\221\230", Q_NULLPTR));
        perfectInfoPushButton->setText(QApplication::translate("MainWindow", "\345\256\214\345\226\204\344\270\252\344\272\272\344\277\241\346\201\257", Q_NULLPTR));
        historySave->setText(QString());
        clearHistory->setText(QString());
        transPushButton->setText(QString());
        sendPushButton->setText(QApplication::translate("MainWindow", "\345\217\221 \351\200\201(S)", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
