/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QPushButton *loginPushButton;
    QLineEdit *usrLineEdit;
    QLineEdit *pwdLineEdit;
    QPushButton *selectLoginButton;
    QPushButton *selectSignButton;
    QLabel *bgLabel;
    QPushButton *signPushButton;
    QLineEdit *s_usrLineEdit;
    QLineEdit *s_EmailLineEdit;
    QLineEdit *s_phoneLineEdit;
    QLineEdit *s_pwdLineEdit;
    QLabel *s_noiticeLabel;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QStringLiteral("LoginDialog"));
        LoginDialog->resize(550, 550);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(11);
        LoginDialog->setFont(font);
        loginPushButton = new QPushButton(LoginDialog);
        loginPushButton->setObjectName(QStringLiteral("loginPushButton"));
        loginPushButton->setGeometry(QRect(120, 440, 311, 43));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(12);
        font1.setBold(false);
        font1.setWeight(50);
        loginPushButton->setFont(font1);
        loginPushButton->setFlat(true);
        usrLineEdit = new QLineEdit(LoginDialog);
        usrLineEdit->setObjectName(QStringLiteral("usrLineEdit"));
        usrLineEdit->setGeometry(QRect(165, 274, 263, 36));
        usrLineEdit->setFont(font1);
        usrLineEdit->setAlignment(Qt::AlignCenter);
        pwdLineEdit = new QLineEdit(LoginDialog);
        pwdLineEdit->setObjectName(QStringLiteral("pwdLineEdit"));
        pwdLineEdit->setGeometry(QRect(165, 350, 263, 36));
        pwdLineEdit->setFont(font1);
        pwdLineEdit->setEchoMode(QLineEdit::Password);
        pwdLineEdit->setAlignment(Qt::AlignCenter);
        selectLoginButton = new QPushButton(LoginDialog);
        selectLoginButton->setObjectName(QStringLiteral("selectLoginButton"));
        selectLoginButton->setGeometry(QRect(32, 8, 218, 63));
        selectLoginButton->setFont(font1);
        selectLoginButton->setAutoDefault(true);
        selectLoginButton->setFlat(true);
        selectSignButton = new QPushButton(LoginDialog);
        selectSignButton->setObjectName(QStringLiteral("selectSignButton"));
        selectSignButton->setGeometry(QRect(300, 8, 218, 63));
        selectSignButton->setFont(font1);
        selectSignButton->setAutoDefault(true);
        selectSignButton->setFlat(true);
        bgLabel = new QLabel(LoginDialog);
        bgLabel->setObjectName(QStringLiteral("bgLabel"));
        bgLabel->setGeometry(QRect(0, 0, 550, 550));
        signPushButton = new QPushButton(LoginDialog);
        signPushButton->setObjectName(QStringLiteral("signPushButton"));
        signPushButton->setGeometry(QRect(120, 440, 311, 43));
        signPushButton->setFont(font1);
        signPushButton->setFlat(true);
        s_usrLineEdit = new QLineEdit(LoginDialog);
        s_usrLineEdit->setObjectName(QStringLiteral("s_usrLineEdit"));
        s_usrLineEdit->setGeometry(QRect(160, 182, 263, 35));
        s_usrLineEdit->setFont(font1);
        s_usrLineEdit->setAlignment(Qt::AlignCenter);
        s_EmailLineEdit = new QLineEdit(LoginDialog);
        s_EmailLineEdit->setObjectName(QStringLiteral("s_EmailLineEdit"));
        s_EmailLineEdit->setGeometry(QRect(160, 240, 263, 35));
        s_EmailLineEdit->setFont(font1);
        s_EmailLineEdit->setAlignment(Qt::AlignCenter);
        s_phoneLineEdit = new QLineEdit(LoginDialog);
        s_phoneLineEdit->setObjectName(QStringLiteral("s_phoneLineEdit"));
        s_phoneLineEdit->setGeometry(QRect(160, 298, 263, 35));
        s_phoneLineEdit->setFont(font1);
        s_phoneLineEdit->setAlignment(Qt::AlignCenter);
        s_pwdLineEdit = new QLineEdit(LoginDialog);
        s_pwdLineEdit->setObjectName(QStringLiteral("s_pwdLineEdit"));
        s_pwdLineEdit->setGeometry(QRect(160, 357, 263, 35));
        s_pwdLineEdit->setFont(font1);
        s_pwdLineEdit->setAlignment(Qt::AlignCenter);
        s_noiticeLabel = new QLabel(LoginDialog);
        s_noiticeLabel->setObjectName(QStringLiteral("s_noiticeLabel"));
        s_noiticeLabel->setGeometry(QRect(140, 410, 251, 16));
        QFont font2;
        font2.setPointSize(9);
        s_noiticeLabel->setFont(font2);
        bgLabel->raise();
        loginPushButton->raise();
        usrLineEdit->raise();
        pwdLineEdit->raise();
        selectLoginButton->raise();
        selectSignButton->raise();
        signPushButton->raise();
        s_usrLineEdit->raise();
        s_EmailLineEdit->raise();
        s_phoneLineEdit->raise();
        s_pwdLineEdit->raise();
        s_noiticeLabel->raise();

        retranslateUi(LoginDialog);

        selectLoginButton->setDefault(false);
        selectSignButton->setDefault(false);


        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QApplication::translate("LoginDialog", "\347\256\200\350\201\212", Q_NULLPTR));
        loginPushButton->setText(QApplication::translate("LoginDialog", "\347\231\273 \345\275\225", Q_NULLPTR));
        usrLineEdit->setText(QString());
        selectLoginButton->setText(QString());
        selectSignButton->setText(QString());
        bgLabel->setText(QString());
        signPushButton->setText(QApplication::translate("LoginDialog", "\346\263\250 \345\206\214", Q_NULLPTR));
        s_usrLineEdit->setText(QString());
        s_EmailLineEdit->setText(QString());
        s_phoneLineEdit->setText(QString());
        s_pwdLineEdit->setText(QString());
        s_noiticeLabel->setText(QApplication::translate("LoginDialog", "\346\263\250\357\274\232\350\201\224\347\263\273\346\226\271\345\274\217\350\256\276\347\275\256\345\220\216\344\270\215\345\217\257\344\277\256\346\224\271\343\200\201\344\270\215\345\217\257\351\207\215\345\244\215", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
