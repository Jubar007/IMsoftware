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
#include "addnews.h"
#include "agreefriend.h"
#include "changeremark.h"
#include "friendgroup.h"

class FileSrvDlg;

namespace Ui {
class MainWindow;
}
enum ChatMsgType { ChatMsg, OnLine, OffLine, SfileName, RefFile , FriendAdd, RefFriend, AcpFriend};//消息类型
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QString usrid;//当前用户的id

    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();
    void initMainWindow();
    void sendUserData(QList<QStringList> data); //在子窗口创建public函数用来获取传递的数据

    void onLine(QString name, QString time);//处理新用户加入
    void offLine(QString name, QString time);//处理用户离开
    void sendChatMsg(ChatMsgType msgType, QString rmtName = "",QStringList={""});//广播UDP消息
    QString getLocHostIp();//获取本端IP地址
    QString getLocChatMsg();//获取本端聊天信息内容
    void recvFileName(QString name, QString hostip, QString rmtname, QString filename);
    QTextBrowser *userTextBrower=nullptr;
    void p2p(QString);
    void chatHistory(QString);
    bool isContacts = true;//底部导航栏选中标识
    void contactVisible(bool);
    void GroupVisible(bool);
    void getGroupMenbers(QString);
    void getGroupMebs(QString);
    bool isBelongGroup(QString);
    void recvFriendAdd(QString ,QString,QStringList);//收到好友申请后处理方法
    QStringList peerInfoList;//发送的个人信息表
   void getFriendsList(QString usrid); //好友列表数据获取
    bool haveNewFriend(QString);
protected:
    //用户数据
    QList<QStringList> myInfo;
    //用户及用户的好友数据
    QList<QStringList> usrInfo;
    //用户加入群的信息
    QList<QStringList> usrGroupInfo;
    //群成员信息
    QList<QStringList> groupMenInfo;
    //新好友信息
    QList<QStringList> newFriendInfo;
    //用户列表数据
    QStringList headpics;
    QStringList names;
    QStringList userSignal;

    int s;//listview用选中的行数（从1开始）
//    void closeEvent(QCloseEvent *event);//重写关闭窗口方法以便发送通知离开消息


private slots:
    void on_listView_clicked(const QModelIndex &index);
    void on_sendPushButton_clicked();  //发送按钮单击事件

    void recvAndProcessChatMsg();//接收并处理UDP数据报

    void getSfileName(QString);
    void sendFriendAdd(QString);//发送好友请求处理
    void on_transPushButton_clicked();

    void on_contactsPushButton_clicked();

    void on_historySave_clicked();

    void on_groupPushButton_clicked();

    void on_perfectInfoPushButton_clicked();

    void on_clearHistory_clicked();

   bool saveFile(const QString& fileName);

    void receiveData(QStringList data);   //接收修改用户个人信息传递过来的数据的槽

    void on_addPushButton_clicked();

    void changeListViewPix(QString,QString,bool);//更改ListView中头像的有无消息的显示（头像上是否有红点显示）

    void changeNoticePix(bool);//右上角铃铛有无红点图片改变

    void agreeFriends(QString uid,QString friendId,QString nickname);
    void on_noticePushButton_clicked();


    void updateFriendsList(QString);


    void on_nickCPushButton_clicked();

    void changeRemarks(QString);

    void on_groupCPushButton_clicked();

    void changeGroup(QString);

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
    addNews *addWindow;
    agreeFriend *agreeFriendWindow;
    changeRemark *changeRemarkWindow;
    friendGroup *friendGroupWindow;
};

#endif // MAINWINDOW_H
