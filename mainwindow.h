#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QUdpSocket>
#include <QNetworkInterface>
#include <QDateTime>
#include <QFile>
#include <QFileDialog>
#include "qdom.h"
#include <QStandardItemModel>

class FileSrvDlg;

namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QString usrid;//当前用户的id
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();    
    void initMainWindow();
    void sendUserData(int data); //在子窗口创建public函数用来获取传递的数据
    void getFriendsList(QString usrid); //好友列表数据获取

protected:
    //用户列表数据
    QStringList headpics;
    QStringList names;
    QStringList userSignal;

private slots:
    void on_listView_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    QStandardItemModel *m_pModel;
};

#endif // MAINWINDOW_H
