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
#include <QTextBrowser>
#include "perfectpersonaldata.h"

class FileSrvDlg;

namespace Ui {
class MainWindow;
}
enum ChatMsgType { ChatMsg, OnLine, OffLine, SfileName, RefFile };//消息类型
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QString usrid;//当前用户的id
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();    
    void initMainWindow();
    void sendUserData(QList<QStringList> data); //在子窗口创建public函数用来获取传递的数据
    void getFriendsList(QString usrid); //好友列表数据获取
    void onLine(QString name, QString time);//处理新用户加入
    void offLine(QString name, QString time);//处理用户离开
    void sendChatMsg(ChatMsgType msgType, QString rmtName = "");//广播UDP消息
    QString getLocHostIp();//获取本端IP地址
    QString getLocChatMsg();//获取本端聊天信息内容
    void recvFileName(QString name, QString hostip, QString rmtname, QString filename);
    QTextBrowser *userTextBrower=0;
    void p2p(QString);
    void chatHistory(QString);
    bool isContacts = true;//底部导航栏选中标识
    void contactVisible(bool);
    void GroupVisible(bool);
    void getGroupMenbers(QString);
    void getGroupMebs(QString);
    bool isBelongGroup(QString);

protected:
    //用户及用户的好友数据
    QList<QStringList> usrInfo;
    //用户加入群的信息
    QList<QStringList> usrGroupInfo;
    //群成员信息
    QList<QStringList> groupMenInfo;
    //用户列表数据
    QStringList headpics;
    QStringList names;
    QStringList userSignal;
//    void closeEvent(QCloseEvent *event);//重写关闭窗口方法以便发送通知离开消息


private slots:
    void on_listView_clicked(const QModelIndex &index);
    void on_sendPushButton_clicked();  //发送按钮单击事件

    void recvAndProcessChatMsg();//接收并处理UDP数据报

//    void on_searchPushButton_clicked();  //搜索在线用户

   void getSfileName(QString);

    void on_transPushButton_clicked();
    void on_contactsPushButton_clicked();

    void on_groupPushButton_clicked();

    void on_perfectInfoPushButton_clicked();
    void receiveData(QStringList data);   //接收修改用户个人信息传递过来的数据的槽
private:
    Ui::MainWindow *ui;
    QStandardItemModel *m_pModel;
    QString myName = "";//本端用户名
    QString clickName = "";//选中私聊用户名
    QString groupname = ""; //群组名
    QUdpSocket *myUdpSocket;  //UDP套接口指针
    qint16 myUdpPort;          //UDP端口号
    QDomDocument myDoc;
    QString myFileName;
    FileSrvDlg *myfsrv;
    QStringList groupMebs;
    perfectPersonalData *perfectWindow;
};

#endif // MAINWINDOW_H
