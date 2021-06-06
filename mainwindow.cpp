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
#include "sqlite.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);    
    initMainWindow();
    QPixmap pix;
    //初始聊天界面被一张图片盖住
    QImage image(":/img/ChatBG.jpg");
    ui->OriginalBg->setPixmap(pix.fromImage(image));
    ui->OriginalBg->setScaledContents(true);
    ui->OriginalBg->show();
    //好友列表下方导航栏的制作
    QImage image2(":/img/navBottom.jpg");
    ui->navLabel->setPixmap(pix.fromImage(image2));
    ui->navLabel->setScaledContents(true);
    ui->navLabel->show();
    //资料卡片背景图
    QImage image3(":/img/InfoBg.jpg");
    ui->HeadTitleBg->setPixmap(pix.fromImage(image3));
    ui->HeadTitleBg->setScaledContents(true);
    ui->HeadTitleBg->show();
    //默认选中联系人
    isContacts = true;
    GroupVisible(false);//群聊控件不可见
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
    Sqlite *db = new Sqlite("sqlite/simpleChat.db");
    QString sql ="select U_ID,U_HeadPortrait,F_Name,U_NickName,U_SignaTure,U_Sex,U_Birthday,U_Telephone,U_Email,US_Name,FG_Name from Friends,User,UserState,FriendGroups where Friends.F_UserID ="+usrid+" and Friends.F_FirendID = User.U_ID and User.U_UserStateID = UserState.US_ID and FriendGroups.FG_UserID = "+usrid;
    if(db->db_query(sql))
    {
        while(db->query.next()){
            //ListView绑定
            headpics.append(db->query.value("U_HeadPortrait").toString());
            names.append(db->query.value("F_Name").toString());
            userSignal.append(db->query.value("U_SignaTure").toString());
            //用户及用户的好友数据更新
            QStringList info;
            info.append(db->query.value("U_ID").toString());
            info.append(db->query.value("U_NickName").toString());
            info.append(db->query.value("U_SignaTure").toString());
            info.append(db->query.value("U_Sex").toString());
            info.append(db->query.value("U_Birthday").toString());
            info.append(db->query.value("U_Telephone").toString());
             info.append(db->query.value("U_Email").toString());
            info.append(db->query.value("U_HeadPortrait").toString());
            info.append(db->query.value("US_Name").toString());
            info.append(db->query.value("FG_Name").toString());
            usrInfo.append(info);
        }
     }
}
//联系人资料卡片可见设置
void  MainWindow::contactVisible(bool canv){
    if(canv){
        QPixmap pix;
        QImage image3(":/img/InfoBg.jpg");
        ui->HeadTitleBg->setPixmap(pix.fromImage(image3));
        ui->HeadTitleBg->setScaledContents(true);
        ui->HeadTitleBg->show();
    }
    ui->userHead->setVisible(canv);
    ui->label->setVisible(canv);
    ui->sexLabel->setVisible(canv);
    ui->birthdayLabel->setVisible(canv);
    ui->EmailLabel->setVisible(canv);
    ui->PhoneLabel->setVisible(canv);
    ui->introLabel->setVisible(canv);
    ui->nickNameLabel->setVisible(canv);
    ui->groupLabel->setVisible(canv);
}
//群聊资料卡片控件可见性设置
 void  MainWindow::GroupVisible(bool canv){
     if(canv){
         QPixmap pix;
         QImage image3(":/img/InfoGroupBg.jpg");
         ui->HeadTitleBg->setPixmap(pix.fromImage(image3));
         ui->HeadTitleBg->setScaledContents(true);
         ui->HeadTitleBg->show();
     }
     ui->G_groupHead->setVisible(canv);
     ui->G_groupNameLabel->setVisible(canv);
     ui->G_introLabel->setVisible(canv);
     ui->G_NoticeLabel->setVisible(canv);
     ui->G_menberTitleLabel->setVisible(canv);
     ui->G_listView->setVisible(canv);
 }
//单击鼠标单击item信息
void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    ui->OriginalBg->setVisible(false);//聊天背景不可见
    //获取选中的用户信息
    QVariant var = index.data(Qt::UserRole+1);
    //qDebug()<<index.row()<<index.column();
    UserItemData ItemData = var.value<UserItemData>();
    QString sUserName = ItemData.sUserName;
    QString headpics = ItemData.sHeadPic;
    ui->FriendNameLabel->setText(sUserName);
    ui->StateLabel->setText("");
    QPixmap pix;
    QImage image(headpics);//filename，图片的路径名字
    ui->FriendHead->setPixmap(pix.fromImage(image));// ui->pix就是label的控件名字
    ui->FriendHead->setScaledContents(true);
    ui->FriendHead->show();
    //资料卡片内容对应变化
    //判断选中的导航栏是联系人还是群聊
    if(isContacts){
    int s = index.row()+1;
    QPixmap pix1;
    QImage image1(usrInfo[s][7]);//filename，图片的路径名字
    ui->userHead->setPixmap(pix1.fromImage(image1));// ui->pix就是label的控件名字
    ui->userHead->setScaledContents(true);
    ui->userHead->show();
    ui->label->setText(usrInfo[s][1]);
    if(usrInfo[s][3] == "1")
        ui->sexLabel->setText("性别: 男");
    else if(usrInfo[s][3] == "2")
        ui->sexLabel->setText("性别: 女");
    else
        ui->sexLabel->setText("性别: 未知");
    ui->birthdayLabel->setText("生日: "+usrInfo[s][4].mid(0, 10));
    ui->EmailLabel->setText("邮箱: "+usrInfo[s][6]);
    ui->PhoneLabel->setText("联系方式: "+usrInfo[s][5]);
    ui->introLabel->setText(usrInfo[s][2]);
    ui->nickNameLabel->setText("备注: "+sUserName);
    ui->groupLabel->setText("分组: "+usrInfo[s][9]);

    }else{
        //控件可见性设置
        contactVisible(false);
        GroupVisible(true);
        int s = index.row();
        QPixmap pix1;
        QImage image1(usrGroupInfo[s][2]);//filename，图片的路径名字
        ui->G_groupHead->setPixmap(pix1.fromImage(image1));// ui->pix就是label的控件名字
        ui->G_groupHead->setScaledContents(true);
        ui->G_groupHead->show();
        ui->G_groupNameLabel->setText(usrGroupInfo[s][0]);
        if(usrGroupInfo[s][4]!="")
            ui->G_introLabel->setText("群介绍: "+usrGroupInfo[s][4]);
        else
            ui->G_introLabel->setText("群介绍: 暂无");
        if(usrGroupInfo[s][3]!="")
            ui->G_NoticeLabel->setText("群公告: "+usrGroupInfo[s][3]);
        else
             ui->G_NoticeLabel->setText("群公告: 暂无");
        getGroupMenbers(usrGroupInfo[s][0]);
    }
    clickname = sUserName;
    //弹出聊天控
    p2p(clickname);  //点击的名字和自己的名字
    //groupChat();
}
//群成员的显示
void MainWindow::getGroupMenbers(QString groupName){
    QString sql = "select U_NickName,U_HeadPortrait,UG_ID,U_ID from User_Groups,User_GroupsToUser,User where UG_Name =\""+groupName+"\" and User_GroupsToUser.UG_UserID = User.U_ID and User_GroupsToUser.UG_GroupID = User_Groups.UG_ID";
    Sqlite *db = new Sqlite("sqlite/simpleChat.db");
    groupMenInfo.clear();
    if(db->db_query(sql))
    {
        while(db->query.next()){
            //用户及用户的好友数据更新
            QStringList info;
            info.append(db->query.value("U_NickName").toString());
            info.append(db->query.value("U_HeadPortrait").toString());
            info.append(db->query.value("UG_ID").toString());
            info.append(db->query.value("U_ID").toString());
            groupMenInfo.append(info);
        }
     }
    m_pModel = new QStandardItemModel;
    for (int i=0; i<groupMenInfo.size(); ++i) {
        QStandardItem *pItem = new QStandardItem;
        UserItemData ItemData;
        ItemData.sUserName = groupMenInfo[i][0];
        if(groupMenInfo[i][2] == groupMenInfo[i][3])
            ItemData.userSignalTrue = "群主";
        else
            ItemData.userSignalTrue = "成员";
        ItemData.sHeadPic = groupMenInfo[i][1];
        pItem->setData(QVariant::fromValue(ItemData), Qt::UserRole+1);
        m_pModel->appendRow(pItem);
    }
    UserItemDelegate* pUserItemDelegate = new UserItemDelegate;
    ui->G_listView->setItemDelegate(pUserItemDelegate);
    ui->G_listView->setModel(m_pModel);
}
//聊天记录里保存
void MainWindow::chatHistory(QString clickname)
{
    QString historyPath ="./"+myname+"to"+ clickname+".txt";
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
    QString historyPath = "./"+myname+"to"+ clickname+".txt";
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
void MainWindow::sendUserData(QList<QStringList> data)
{
    usrInfo = data;
    //绑定个人资料控件

    QPixmap pix;
    QImage image(data[0][7]);//filename，图片的路径名字
    ui->userHead->setPixmap(pix.fromImage(image));// ui->pix就是label的控件名字
    ui->userHead->setScaledContents(true);
    ui->userHead->show();
    ui->label->setText(usrInfo[0][1]);
    if(usrInfo[0][3] == "1")
        ui->sexLabel->setText("性别: 男");
    else if(usrInfo[0][3] == "2")
        ui->sexLabel->setText("性别: 女");
    else
        ui->sexLabel->setText("性别: 未知");
    ui->birthdayLabel->setText("生日: "+usrInfo[0][4].mid(0, 10));
    ui->EmailLabel->setText("邮箱: "+usrInfo[0][6]);
    ui->PhoneLabel->setText("联系方式: "+usrInfo[0][5]);
    ui->introLabel->setText(usrInfo[0][2]);
    //获取当前用户的好友列表-->更新用户列表数据
    getFriendsList(data[0][0]);
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
            else if(udpclickname ==groupname&&clickname == udpmyname)
            {
                if(groupChat(myname)==myname)
                {
                    userTextBrower->append("[" +udpmyname + "]" + curtime);
                    userTextBrower->append(chatmsg);
                    userTextBrower->update();
                    chatHistory(clickname);
                }
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
QString MainWindow::groupChat(QString myname)
{
    QStringList groupList,result;
    groupList<<"杨磊" << "吴汶憶" << "李群" ;
    result = groupList.filter(myname,Qt::CaseInsensitive);
    return result[0];
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


//点击导航栏联系人按钮
void MainWindow::on_contactsPushButton_clicked()
{
    //控件可见性设置
    contactVisible(true);
    GroupVisible(false);
    isContacts = true;
    QPixmap pix;
    //好友列表下方导航栏的制作
    QImage image(":/img/navBottom.jpg");
    ui->navLabel->setPixmap(pix.fromImage(image));
    ui->navLabel->setScaledContents(true);
    ui->navLabel->show();
    //绑定ListView
    m_pModel = new QStandardItemModel;
    for (int i=1; i<usrInfo.size(); ++i) {
        QStandardItem *pItem = new QStandardItem;
        UserItemData ItemData;
        ItemData.sUserName = usrInfo[i][1];
        ItemData.userSignalTrue = usrInfo[i][2];
        ItemData.sHeadPic = usrInfo[i][7];
        pItem->setData(QVariant::fromValue(ItemData), Qt::UserRole+1);
        m_pModel->appendRow(pItem);
    }
    UserItemDelegate* pUserItemDelegate = new UserItemDelegate;
    ui->listView->setItemDelegate(pUserItemDelegate);
    ui->listView->setModel(m_pModel);
}

//点击导航栏群聊按钮
void MainWindow::on_groupPushButton_clicked()
{
    isContacts = false;
    QPixmap pix;
    //好友列表下方导航栏的制作
    QImage image(":/img/navBottom_UG.jpg");
    ui->navLabel->setPixmap(pix.fromImage(image));
    ui->navLabel->setScaledContents(true);
    ui->navLabel->show();
    //数据库操作
    QString sqltoGroup = "select UG_Name,UG_AdminID,UG_ICon,UG_Notice,UG_Intro from User_Groups,User_GroupsToUser where User_GroupsToUser.UG_UserID = "+usrInfo[0][0]+" and User_Groups.UG_ID = User_GroupsToUser.UG_GroupID";
    Sqlite *db = new Sqlite("sqlite/simpleChat.db");
    usrGroupInfo.clear();
    if(db->db_query(sqltoGroup))
    {
        while(db->query.next()){
            //用户及用户的好友数据更新
            QStringList info;
            info.append(db->query.value("UG_Name").toString());
            info.append(db->query.value("UG_AdminID").toString());
            if(db->query.value("UG_ICon").toString()!="")
                info.append(db->query.value("UG_ICon").toString());
            else
                info.append(":/img/group3.png");
            info.append(db->query.value("UG_Notice").toString());
            info.append(db->query.value("UG_Intro").toString());
            usrGroupInfo.append(info);
        }
     }
    //绑定ListView
    m_pModel = new QStandardItemModel;
    for (int i=0; i<usrGroupInfo.size(); ++i) {
        QStandardItem *pItem = new QStandardItem;
        UserItemData ItemData;
        ItemData.sUserName = usrGroupInfo[i][0];
        ItemData.userSignalTrue = usrGroupInfo[i][4];
        ItemData.sHeadPic = usrGroupInfo[i][2];
        pItem->setData(QVariant::fromValue(ItemData), Qt::UserRole+1);
        m_pModel->appendRow(pItem);
    }
    UserItemDelegate* pUserItemDelegate = new UserItemDelegate;
    ui->listView->setItemDelegate(pUserItemDelegate);
    ui->listView->setModel(m_pModel);
}
