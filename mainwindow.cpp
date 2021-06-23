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
#include "perfectpersonaldata.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);    
    initMainWindow();
    QPixmap icon1(tr(":/img/fileIo.png")),
            icon2(tr(":/img/download.png")),
            icon3(tr(":/img/clear.png"));
    ui->transPushButton->setIcon(icon1);
    ui->historySave->setIcon(icon2);
    ui->clearHistory->setIcon(icon3);
    ui->transPushButton->setStyleSheet("background-color:rgba(0,0,0,0)");
    ui->historySave->setStyleSheet("background-color:rgba(0,0,0,0)");
    ui->clearHistory->setStyleSheet("background-color:rgba(0,0,0,0)");

    //面板背景图
    QPixmap pix1;
    QImage image1(":/img/bg.png");//filename，图片的路径名字
    ui->bg->setPixmap(pix1.fromImage(image1));// ui->pix就是label的控件名字
    ui->bg->setScaledContents(true);
    ui->bg->show();
    //初始聊天界面被一张图片盖住
    QPixmap pix;
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
    //聊天操作按钮不可见设置
    ui->clearHistory->setVisible(false);
    ui->historySave->setVisible(false);
    ui->sendPushButton->setVisible(false);
    ui->transPushButton->setVisible(false);

    ui->perfectInfoPushButton->setStyleSheet("color:white;");


    //初始化TCP服务器
//    myfsrv = new FileSrvDlg(this);
//    connect(myfsrv, SIGNAL(sendFileName(QString)), this, SLOT(getSfileName(QString)));
}
MainWindow::~MainWindow()
{
    delete ui;
}

//TODO: 窗口初始化
void MainWindow::initMainWindow()
{
    //初始化UDP套接件
    myUdpSocket = new QUdpSocket(this);
    myUdpPort = 23232;
    myUdpSocket->bind(myUdpPort, QUdpSocket::ShareAddress|QUdpSocket::ReuseAddressHint);
    connect(myUdpSocket, SIGNAL(readyRead()), this, SLOT(recvAndProcessChatMsg()));
}

void MainWindow:: getFriendsList(QString usrid){
    QTextCodec::setCodecForLocale (QTextCodec:: codecForLocale ()) ;
    Sqlite *db = new Sqlite("sqlite/simpleChat.db");
    QString sql ="select U_ID,U_HeadPortrait,F_Name,U_NickName,U_SignaTure,U_Sex,U_Birthday,U_Telephone,U_Email,US_Name,FG_Name,isFriend from Friends,User,UserState,FriendGroups where Friends.F_UserID ="+usrid+" and Friends.F_FirendID = User.U_ID and User.U_UserStateID = UserState.US_ID and FriendGroups.FG_UserID = "+usrid;
     qDebug()<<sql;
    if(db->db_query(sql))
    {
        while(db->query.next()){
            if(db->query.value("isFriend").toString()=="1"){//同意添加好友显示
            //ListView绑定
            headpics.append(db->query.value("U_HeadPortrait").toString());
            names.append(db->query.value("F_Name").toString());
            userSignal.append(db->query.value("U_SignaTure").toString());
            //qDebug()<<db->query.value("isFriend").toString();//转换成string类型显示出的为“1”
            //用户及用户的好友数据更新
            QStringList info;
            info.append(db->query.value("U_ID").toString());//0
            info.append(db->query.value("U_NickName").toString());
            info.append(db->query.value("U_SignaTure").toString());
            info.append(db->query.value("U_Sex").toString());
            info.append(db->query.value("U_Birthday").toString());
            info.append(db->query.value("U_Telephone").toString());//5
             info.append(db->query.value("U_Email").toString());
            info.append(db->query.value("U_HeadPortrait").toString());
            info.append(db->query.value("US_Name").toString());
            info.append(db->query.value("FG_Name").toString());
            info.append(db->query.value("F_Name").toString());
            usrInfo.append(info);
            }
        }
     }
}

//联系人资料卡片可见设置
void MainWindow::contactVisible(bool canv){
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
    ui->perfectInfoPushButton->setVisible(canv);
    ui->perfectInfoPushButton->setStyleSheet("color:white;");
}

//群聊资料卡片控件可见性设置
void MainWindow::GroupVisible(bool canv){
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
    ui->nickNameLabel->setVisible(true);
    ui->groupLabel->setVisible(true);
    ui->perfectInfoPushButton->setVisible(false);
    ui->OriginalBg->setVisible(false);//聊天背景不可见

    //聊天操作按钮可见设置
    ui->clearHistory->setVisible(true);
    ui->historySave->setVisible(true);
    ui->sendPushButton->setVisible(true);
    ui->transPushButton->setVisible(true);

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
        //控件可见性设置  群聊面板右侧属性
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

    //选中的item属性，全局变量
    clickName = sUserName;//usrInfo[s][1]
    //弹出聊天空间
    p2p(clickName);
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

    //群聊信息出口 将函数分解为二： 1、获取群组信息  2、显示群组信息
}
void MainWindow::getGroupMebs(QString groupName)
{
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
    for (int i=0; i<groupMenInfo.size(); ++i) {
        groupMebs.append(groupMenInfo[i][0]);
    }

}

//聊天记录保存按钮
void MainWindow::on_historySave_clicked()
{
    if (userTextBrower->document()->isEmpty()) {
        QMessageBox::warning(0, tr("警告"), tr("聊天记录为空，无法保存！"), QMessageBox::Ok);
    } else {
        QString fileName = QFileDialog::getSaveFileName(this,
                                                        tr("保存聊天记录"), tr("聊天记录"), tr("文本(*.txt);;All File(*.*)"));
        if(!fileName.isEmpty())
            saveFile(fileName);
    }
}

//聊天记录文件
bool MainWindow::saveFile(const QString &fileName)
{

    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("保存文件"),
                             tr("无法保存文件 %1:\n %2").arg(fileName)
                             .arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);
    out << userTextBrower->toPlainText();

    return true;
}

//清除聊天记录
void MainWindow::on_clearHistory_clicked()
{
    userTextBrower->clear();
    QString historyPath ="./"+myName+"to"+ clickName+".txt";
    QFile fp(historyPath);
    if (!fp.open(QIODevice::WriteOnly | QIODevice::Text | QFile::Truncate))
    {
        qDebug()<<"文件清空失败";
    }
    fp.close();
}


//聊天记录内部存档
void MainWindow::chatHistory(QString clickname)
{
    QString historyPath ="./"+myName+"to"+ clickname+".txt";
    QFile fp(historyPath);
    //不存在就创建  存在就追加写
    if (!fp.open(QIODevice::WriteOnly | QIODevice::Text))
     {
       qDebug()<<"消息存档创建失败";
       return;
     };
    QTextStream in(&fp);
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
    QString historyPath = "./"+myName+"to"+ clickname+".txt";
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

//前置登录信息传入mainwindow
void MainWindow::sendUserData(QList<QStringList> data)
{
    //当前用户属性，全局变量
    myName = data[0][1];

    usrInfo = data;
    //绑定个人资料控件

    QPixmap pix;
    QImage image(data[0][7]);//filename，图片的路径名字
    ui->userHead->setPixmap(pix.fromImage(image));// ui->pix就是label的控件名字
    ui->userHead->setScaledContents(true);
    ui->userHead->show();

    ui->MyHead->setPixmap(pix.fromImage(image));
    ui->MyHead->setScaledContents(true);
    ui->MyHead->show();


    QIcon icon1;
     icon1.addFile(":/img/add.png");//添加图形，将加载进来的资源进行保存
     ui->addPushButton->setIcon(icon1);
     ui->addPushButton->setIconSize(QSize(21,21));
     ui->addPushButton->setStyleSheet("QPushButton{background-color:rgb(178,206,254);"
                           "border:0px solid gray;}"); //边界宽度，样式，颜色

     QIcon icon2;
      icon2.addFile(":/img/notice.png");//添加图形，将加载进来的资源进行保存
      ui->noticePushButton->setIcon(icon2);
      ui->noticePushButton->setIconSize(QSize(21,21));
      ui->noticePushButton->setStyleSheet("QPushButton{background-color:rgb(178,206,254);"
                            "border:0px solid gray;}"); //边界宽度，样式，颜色

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
    ui->nickNameLabel->setText("备注: 无");
    ui->groupLabel->setText("分组: 无");
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

//点击文本发送按钮
void MainWindow::on_sendPushButton_clicked()
{
    //发出广播 消息类型 发送给谁
    sendChatMsg(ChatMsg,clickName);
}

//发UDP广播
void MainWindow::sendChatMsg(ChatMsgType msgType, QString rmtName)
{

    QByteArray qba;
    QDataStream write(&qba, QIODevice::WriteOnly);
    QString locHostIp = getLocHostIp();
    QString locChatMsg = getLocChatMsg();
    write << msgType << myName<<rmtName;  //1、在发送的信息中，写入 消息类型+发送者用户名+好友名
    qDebug()<<"UDP广播发出"<<"文件类型："<<msgType
           <<"发送者"<<myName
           <<"接受者"<<rmtName;
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
        //2、写入发送端的Ip、文件名
        write << locHostIp << myFileName;
        break;
    case RefFile:
        write << locHostIp << rmtName;
        break;
    }
    myUdpSocket->writeDatagram(qba, qba.length(), QHostAddress::Broadcast, myUdpPort);  //完成消息处理后，发出广播
}

//接受UDP广播
void MainWindow::recvAndProcessChatMsg()
{
    while (myUdpSocket->hasPendingDatagrams()) //判断是否读到消息
    {
        qDebug()<<"接收到UDP广播";
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
            qDebug()<<"UDP内容为消息";
            read >> udpmyname >>udpclickname>> hostip >> chatmsg;
            //显示聊天内容
            if(isContacts)//消息为私聊
            {
               if((myName==udpmyname&&clickName==udpclickname)||
                        (myName==udpclickname&&clickName==udpmyname))
                {
                    userTextBrower->append("[" +udpmyname + "]" + curtime);
                    userTextBrower->append(chatmsg);
                    userTextBrower->update();
                    chatHistory(clickName);
                }
            }
            else//消息为群聊
            {
                if(isBelongGroup(udpclickname)&&clickName==udpclickname)
                {
                    userTextBrower->append("[" +udpmyname + "]" + curtime);
                    userTextBrower->append(chatmsg);
                    userTextBrower->update();
                    chatHistory(clickName);
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
            //发送者用户名+好友名、发送端的Ip、文件名
            read >> udpmyname >> rname >>hostip >>fname;
            qDebug()<<"UDP内容为文件"
                   <<"发送者"<<udpmyname
                    <<"接收者"<<rname
                    <<"当前用户"<<myName;
            if (myName == rname)
            {recvFileName(udpmyname, hostip, rname, fname);}
            break;
        case RefFile:
            read >> udpmyname >> rname >>hostip >>fname;
            if (myName == rname) myfsrv->cntRefused();
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

//判断群成员是否属于群组
bool MainWindow::isBelongGroup(QString udpclickname)
{
    getGroupMebs(udpclickname);
    bool ret = groupMebs.contains(myName);
    if(ret)
        return true; //属于该群组的成员
    else
        return  false;

}

//文件传输按钮
void MainWindow::on_transPushButton_clicked()
{
    //创建TCP服务器，作为发送端

    myfsrv = new FileSrvDlg(this);
    connect(myfsrv, SIGNAL(sendFileName(QString)), this, SLOT(getSfileName(QString)));
    myfsrv->show();
//    //每次点击必须初始化
//    myfsrv->initServer();

}

//获取文件名 全局变量myFileName 并发送udp
void MainWindow::getSfileName(QString fname)
{
    myFileName = fname;
    sendChatMsg(SfileName, clickName);
}

//判断接收文件
void MainWindow::recvFileName(QString name, QString hostip, QString rmtname, QString filename)
{
    if (myName == rmtname)
    {
        int result = QMessageBox::information(this, tr("收到文件"), tr("好友 %1 给您发文件：\r\n%2，是否接收？").arg(name).arg(filename), QMessageBox::Yes, QMessageBox::No);
        if (result == QMessageBox::Yes)
        {
            //传入UDP文件名，设置文件路径
            QString fname = QFileDialog::getSaveFileName(0, tr("保 存"), filename);
            if (!fname.isEmpty())
            {
                FileCntDlg *fcnt = new FileCntDlg(this);
                //新建保存文件流
                fcnt->getLocPath(fname);
                //传入UDP接收到的IP地址，并建立连接
                fcnt->getSrvAddr(QHostAddress(hostip));
                fcnt->show();
            }
        } else {
            sendChatMsg(RefFile, name); //TODO:拒绝处理文件
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
        ItemData.sUserName = usrInfo[i][10];
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

//点击完善个人信息
void MainWindow::on_perfectInfoPushButton_clicked()
{
    perfectWindow = new perfectPersonalData();
    connect(perfectWindow, SIGNAL(sendData(QStringList)), this, SLOT(receiveData(QStringList)));
    perfectWindow->setWindowTitle("完善个人信息");
    //传输用户数据
    perfectWindow->getUersData(usrInfo[0]);
    //窗口显示
    perfectWindow->show();
}

//接收从修改个人信息传输的值
void MainWindow::receiveData(QStringList data)
{
    QPixmap pix;
    QImage image(data[2]);//filename，图片的路径名字
    ui->userHead->setPixmap(pix.fromImage(image));// ui->pix就是label的控件名字
    ui->userHead->setScaledContents(true);
    ui->userHead->show();
    ui->label->setText(data[0]);
    if(data[1] == "1")
        ui->sexLabel->setText("性别: 男");
    else if(data[1] == "2")
        ui->sexLabel->setText("性别: 女");
    else
        ui->sexLabel->setText("性别: 未知");
    ui->birthdayLabel->setText("生日: "+data[3].mid(0, 10));
    ui->EmailLabel->setText("邮箱: "+data[4]);
    ui->PhoneLabel->setText("联系方式: "+data[5]);
    ui->introLabel->setText(data[6]);
}
//更改ListView中头像的有无消息的显示（头像上是否有红点显示）
/*
参数说明：
myNickName：当前用户的昵称
sendNickName:发送方的昵称，对应usrInfo[i][1] (注：不是好友的备注)；可以是好友的名称，也可以是群的名称
RedPoint：true表示把头像从无红点变为有红点
                    false表示吧头像从有红点变为无红点
*/
void MainWindow::changeListViewPix(QString myNickName,QString sendNickName,bool RedPoint){
    if(isContacts){//选中联系人
       //遍历usrInfo更改头像
       for (int i=1; i<usrInfo.size(); ++i) {
          if(usrInfo[i][1]==sendNickName){//找到相应的发送人位置
              if(usrInfo[i][3]=="2"){//根据性别更改头像
                  if(RedPoint)  usrInfo[i][7] = ":/img/girl_a.png";
                  else  usrInfo[i][7] = ":/img/girl.png";
              }else{
                  if(RedPoint)  usrInfo[i][7] = ":/img/boy_a.png";
                  else  usrInfo[i][7] = ":/img/boy.png";
              }
          }
       }
       //重新绑定ListView
       m_pModel = new QStandardItemModel;
       for (int i=1; i<usrInfo.size(); ++i) {
           QStandardItem *pItem = new QStandardItem;
           UserItemData ItemData;
           ItemData.sUserName = usrInfo[i][10];
           ItemData.userSignalTrue = usrInfo[i][2];
           ItemData.sHeadPic = usrInfo[i][7];
           pItem->setData(QVariant::fromValue(ItemData), Qt::UserRole+1);
           m_pModel->appendRow(pItem);
       }
       UserItemDelegate* pUserItemDelegate = new UserItemDelegate;
       ui->listView->setItemDelegate(pUserItemDelegate);
       ui->listView->setModel(m_pModel);
   }else{//选中群聊
       //遍历usrGroupInfo
        //遍历usrInfo更改头像
        for (int i=1; i<usrGroupInfo.size(); ++i) {
           if(usrGroupInfo[i][0]==sendNickName){//找到相应的发送群位置
                if(RedPoint)  usrGroupInfo[i][2] = ":/img/group3_a.png";
                else usrGroupInfo[i][2] = ":/img/group3.png";
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
}
//右上角铃铛有无红点图片改变
/*
参数说明：
RedPoint：true表示把铃铛从无红点变为有红点
                    false表示吧铃铛从有红点变为无红点
*/
void MainWindow::changeNoticePix(bool RedPoint){
    if(RedPoint){
        QIcon icon2;
         icon2.addFile(":/img/notice_a.png");//添加图形，将加载进来的资源进行保存
         ui->noticePushButton->setIcon(icon2);
         ui->noticePushButton->setIconSize(QSize(21,21));
         ui->noticePushButton->setStyleSheet("QPushButton{background-color:rgb(178,206,254);"
                               "border:0px solid gray;}"); //边界宽度，样式，颜色
    }else{
        QIcon icon2;
         icon2.addFile(":/img/notice.png");//添加图形，将加载进来的资源进行保存
         ui->noticePushButton->setIcon(icon2);
         ui->noticePushButton->setIconSize(QSize(21,21));
         ui->noticePushButton->setStyleSheet("QPushButton{background-color:rgb(178,206,254);"
                               "border:0px solid gray;}"); //边界宽度，样式，颜色
    }
}
//同意添加好友跟新或写入数据库
/*参数说明：
int uid, 当前用户的ID 对应usrInfo[0][0](也是QString类型)--->QList<QStringList>
int friendId, 好友的ID（别人的）
QString nickname：当前用户给好友的备注
*/
void MainWindow::agreeFriend(QString uid,QString friendId,QString nickname){
    QString updateSql = "update Friends set isFriend=true where F_FirendID = "+friendId+" and F_UserID = "+uid;
    Sqlite *db = new Sqlite("sqlite/simpleChat.db");
    bool successUpdate = db->db_query(updateSql);
    if(!successUpdate){
        qDebug()<<"更新数据库失败！";
        return;
    }
    QString insertSql ="insert into Friends values("+friendId+","+uid+",'"+nickname+"',"+uid+",true,null)";
    bool successInsert = db->db_query(insertSql);
    if(!successInsert){
        qDebug()<<"插入数据库失败！";
        return;
    }
}
void MainWindow::on_addPushButton_clicked()
{
    addWindow = new addNews();
    addWindow->setWindowTitle("添加好友/群");
    addWindow->sendData(usrInfo); //直接调用public函数将本页面中lineEdit的数据传递过去
    //窗口显示
    addWindow->show();
}
