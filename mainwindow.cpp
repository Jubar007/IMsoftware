#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filesrvdlg.h"
#include "filecntdlg.h"
#include "useritemdelegate.h"
#include "UserListData.h"
#include "sqlite.h"
#include <QTextCodec>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QList>
#include <QStringList>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);    
    initMainWindow();
    QPixmap pix;
    QImage image(":/img/ChatBG.jpg");
    ui->OriginalBg->setPixmap(pix.fromImage(image));
    ui->OriginalBg->setScaledContents(true);
    ui->OriginalBg->show();
}
MainWindow::~MainWindow()
{
    delete ui;
}

//TODO: 窗口初始化
void MainWindow::initMainWindow()
{
    myUdpSocket = new QUdpSocket(this);
    myUdpPort = 23232;
    myUdpSocket->bind(myUdpPort, QUdpSocket::ShareAddress|QUdpSocket::ReuseAddressHint);
    connect(myUdpSocket, SIGNAL(readyRead()), this, SLOT(recvAndProcessChatMsg()));
    myfsrv = new FileSrvDlg(this);
    connect(myfsrv, SIGNAL(sendFileName(QString)), this, SLOT(getSfileName(QString)));
}
void MainWindow:: getFriendsList(QString usrid){
    QTextCodec::setCodecForLocale (QTextCodec:: codecForLocale ()) ;
    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
                 db = QSqlDatabase::database("qt_sql_default_connection");
               else
                 db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:\\02_work\\04_QT\\04_IMsoft\\MyWeiXin0531\\sqlite\\simpleChat.db");
    if(!db.open()){
        qDebug()<<db.lastError().text();
        return;
    }
    QSqlQuery query;
    //qDebug()<<"select U_HeadPortrait,F_Name,U_SignaTure from Friends,User where Friends.F_UserID = "+usrid+" and Friends.F_FirendID = User.U_ID";
    if(query.exec("select U_HeadPortrait,F_Name,U_SignaTure from Friends,User where Friends.F_UserID = "+usrid+" and Friends.F_FirendID = User.U_ID"))
    {
        while(query.next()){
            //qDebug()<<query.value("U_HeadPortrait").toString()<<query.value("F_Name").toString()<<query.value("U_SignaTure").toString();
            headpics.append(query.value("U_HeadPortrait").toString());
            names.append(query.value("F_Name").toString());
            userSignal.append(query.value("U_SignaTure").toString());
        }
     }
}

//单击鼠标单击item信息
void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    ui->OriginalBg->setVisible(false);//聊天背景不可见
    //获取选中的用户信息
    QVariant var = index.data(Qt::UserRole+1);
    UserItemData ItemData = var.value<UserItemData>();
    QString sUserName = ItemData.sUserName;
    clickname = sUserName;
    QString headpics = ItemData.sHeadPic;
    ui->FriendNameLabel->setText(sUserName);
    ui->StateLabel->setText("在线");
    ui->FriendHead->setPixmap(QPixmap(headpics));

    //弹出聊天控件
    //创建聊天记录文件
    p2p(clickname);  //点击的名字和自己的名字
    groupChat();
}
//聊天记录里保存
void MainWindow::chatHistory(QString clickname)
{
    QString historyPath ="F:/Download/"+myname+"to"+ clickname+".txt";
    QFile fp(historyPath);
    //不存在就创建  存在就追加写
    if (!fp.open(QIODevice::WriteOnly | QIODevice::Text))
     {
       qDebug()<<"文件创建失败";
       return;
     };
    QTextStream in(&fp);
    //判断Textbrower是否为空，
    //写入text上的数据
    if(userTextBrower)
    {
        in <<userTextBrower->toPlainText().toUtf8();
    }

    fp.close();
}

void MainWindow::p2p(QString clickname)
{
    //创建一对多聊天室
    userTextBrower = new QTextBrowser;
    userTextBrower->setGeometry(250,65,491,300);
    userTextBrower->setParent(this);
    userTextBrower->setTextColor(Qt::darkGreen);
    userTextBrower->setCurrentFont(QFont("Times New Roman", 14));

    //根据clickname 读取聊天记录文件
    QString historyPath = "F:/Download/"+myname+"to"+ clickname+".txt";
    QFile fps(historyPath);
    if (!fps.open(QIODevice::ReadWrite | QIODevice::Text))
     {
       qDebug()<<"文件读取失败";
       return;
     };
    QTextStream out(&fps);
    while(!out.atEnd() )
    {
        QString buf= out.readLine();
        userTextBrower->append(buf);
    }
    userTextBrower->show();
}

//显示好友列表
void MainWindow::sendUserData(int data)
{
    myname = this->windowTitle();
    usrid = QString::number(data);
    //获取当前用户的好友列表-->更新用户列表数据
    getFriendsList(usrid);
    //循环插入数据
    m_pModel = new QStandardItemModel;
    for (int i=0; i<headpics.size(); ++i) {
        QStandardItem *pItem = new QStandardItem;
        UserItemData ItemData;
        ItemData.sUserName = names.at(i);
        ItemData.userSignalTrue = userSignal.at(i);
        ItemData.sHeadPic = headpics.at(i);
        pItem->setData(QVariant::fromValue(ItemData), Qt::UserRole+1);
        m_pModel->appendRow(pItem);
    }
    UserItemDelegate* pUserItemDelegate = new UserItemDelegate;
    //绑定到listview
    ui->listView->setItemDelegate(pUserItemDelegate);
    ui->listView->setModel(m_pModel);
}

//点击发送按钮
void MainWindow::on_sendPushButton_clicked()
{
    //发出广播
    sendChatMsg(ChatMsg);
}

//发UDP广播
void MainWindow::sendChatMsg(ChatMsgType msgType, QString rmtName)
{

    QByteArray qba;
    QDataStream write(&qba, QIODevice::WriteOnly);
    QString locHostIp = getLocHostIp();
    QString locChatMsg = getLocChatMsg();
    write << msgType << myname<<clickname;  //1、在发送的信息中，写入 消息类型+发送者用户名+好友名
    switch (msgType)
    {
    case ChatMsg:
        write << locHostIp << locChatMsg;  //2、在发送的信息中，写入 本机ip+聊天信息
        break;
    case OnLine:
        write << locHostIp;//2、在发送的信息中，写入本机ip
        break;
    case OffLine:
        break;
    case SfileName:
        write << locHostIp << rmtName << myFileName;//2、TODO：在发送的信息中，写入本机ip+接收端用户名+文件名
        break;
    case RefFile:
        write << locHostIp << rmtName;
        break;
    }
    myUdpSocket->writeDatagram(qba, qba.length(), QHostAddress::Broadcast, myUdpPort);  //完成消息处理后，发出广播
}

//接受UDP广播  TODO：设置一个标志，是否为点击的好友用户名
void MainWindow::recvAndProcessChatMsg()
{
    while (myUdpSocket->hasPendingDatagrams()) //判断是否读到消息
    {
        QByteArray qba;
        qba.resize(myUdpSocket->pendingDatagramSize());
        myUdpSocket->readDatagram(qba.data(), qba.size());
        QDataStream read(&qba, QIODevice::ReadOnly);
        int msgType;
        read >> msgType; //第一个数据就是  消息类型
        QString udpmyname,udpclickname, hostip, chatmsg, rname, fname;  //紧跟着发送用户名 接收用户名 IP地址 聊天内容 文件接收用户名 文件名等
        QString curtime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        switch (msgType)
        {
        case ChatMsg: {
            read >> udpmyname >>udpclickname>> hostip >> chatmsg;
            //显示聊天内容
            if((myname==udpmyname&&clickname==udpclickname)||
                    (myname==udpclickname&&clickname==udpmyname))
            {
                userTextBrower->append("[" +udpmyname + "]" + curtime);
                userTextBrower->append(chatmsg);
                userTextBrower->update();
                chatHistory(clickname);
            }

            break;
        }
//        case OnLine:
//            read >> name >> hostip;
//            onLine(name, curtime);
//            break;
//        case OffLine:
//            read >> name;
//            offLine(name, curtime);
//            break;
        case SfileName:
            read >> udpmyname >> hostip >> rname >> fname;
            recvFileName(udpmyname, hostip, rname, fname);
            break;
        case RefFile:
            read >> udpmyname >> hostip >> rname;
            if (myname == rname) myfsrv->cntRefused();
            break;
        }
    }
}

//获取聊天打字内容
QString MainWindow::getLocChatMsg()
{
    QString chatmsg = ui->chatTextEdit->toHtml();
    ui->chatTextEdit->clear();
    ui->chatTextEdit->setFocus();
    return chatmsg;
}

//获取ip
QString MainWindow::getLocHostIp()
{
    QList<QHostAddress> addrlist = QNetworkInterface::allAddresses();
    foreach (QHostAddress addr, addrlist)
    {
        if (addr.protocol() == QAbstractSocket::IPv4Protocol) return addr.toString();
    }
    return 0;
}

//建立群组
void MainWindow::groupChat()
{
    QStringList groupList,result;
    groupList<<"杨磊" << "吴汶憶" << "李群" ;
    result = groupList.filter("吴汶憶",Qt::CaseInsensitive);
    qDebug()<<result[0];
}

//文件发送按钮
void MainWindow::on_transPushButton_clicked()
{
//    if (ui->userListTableWidget->selectedItems().isEmpty())
//    {
//        QMessageBox::warning(0, tr("选择好友"), tr("请先选择文件接收方！"), QMessageBox::Ok);
//        return;
//    }
    myfsrv->show();
}

//获取文件名 并发送udp
void MainWindow::getSfileName(QString fname)
{
    myFileName = fname;
    sendChatMsg(SfileName, clickname);
}

//接收文件
void MainWindow::recvFileName(QString name, QString hostip, QString rmtname, QString filename)
{
    if (myname == rmtname)
    {
        int result = QMessageBox::information(this, tr("收到文件"), tr("好友 %1 给您发文件：\r\n%2，是否接收？").arg(name).arg(filename), QMessageBox::Yes, QMessageBox::No);
        if (result == QMessageBox::Yes)
        {
            QString fname = QFileDialog::getSaveFileName(0, tr("保 存"), filename);
            if (!fname.isEmpty())
            {
                FileCntDlg *fcnt = new FileCntDlg(this);
                fcnt->getLocPath(fname);
                fcnt->getSrvAddr(QHostAddress(hostip));
                fcnt->show();
            }
        } else {
            sendChatMsg(RefFile, name);
        }
    }
}


