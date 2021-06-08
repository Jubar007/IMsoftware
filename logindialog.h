#ifndef SQLITEHELPER_H
#define SQLITEHELPER_H

#include <QDialog>
#include "mainwindow.h"
#include <QFile>
#include "qdom.h"

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
    void showChatWindow();
    void paintEvent(QPaintEvent *);
    QList<QStringList> usrsInfo;
    bool queryphone(QString phone);

private slots:
    void on_selectLoginButton_clicked();

    void on_selectSignButton_clicked();

    void on_signPushButton_clicked();

private:
    Ui::LoginDialog *ui;
    MainWindow *chatWindow;
    QDomDocument mydoc;
};

#endif // LOGINDIALOG_H
