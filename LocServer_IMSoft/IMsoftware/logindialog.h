#ifndef SQLITEHELPER_H
#define SQLITEHELPER_H

#include <QDialog>
#include "mainwindow.h"
#include <QFile>
#include "qdom.h"
#include <QUdpSocket>
#include <QNetworkInterface>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

public:
    void showChatWindow(QList<QStringList>);
    void paintEvent(QPaintEvent *);
    QList<QStringList> usrsInfo;
    QStringList usrInfo;
    bool queryphone(QString phone);
    void logCntSend(ChatMsgType msgType,QString,QString,QStringList = {});

private slots:
    void on_selectLoginButton_clicked();

    void on_selectSignButton_clicked();

    void on_signPushButton_clicked();

    void on_loginPushButton_clicked();

    void logCntRcv();

private:
    Ui::LoginDialog *ui;
    MainWindow *chatWindow;
    QDomDocument mydoc;
    QUdpSocket *logUdpSocket;  //UDP套接口指针
    qint16 myUdpPort;          //UDP端口
};

#endif // LOGINDIALOG_H
