#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filesrvdlg.h"
#include "filecntdlg.h"
#include "useritemdelegate.h"
#include "UserListData.h"
#include "sqlite.h"
#include <QTextCodec>
#include<QSqlDatabase>
#include<QSqlError>
#include <QSqlQuery>
#include <QSqlDriver>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);    
    initMainWindow();
    QPixmap pix;
    QImage image(":/img/ChatBG.jpg");//filename，图片的路径名字
    ui->OriginalBg->setPixmap(pix.fromImage(image));// ui->pix就是label的控件名字
    ui->OriginalBg->setScaledContents(true);
    ui->OriginalBg->show();
}

void MainWindow:: getFriendsList(QString usrid){
    QTextCodec::setCodecForLocale (QTextCodec:: codecForLocale ()) ;
    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
                 db = QSqlDatabase::database("qt_sql_default_connection");
               else
                 db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("sqlite/simpleChat.db");
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
//单击获取选中item信息
void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    ui->OriginalBg->setVisible(false);//聊天背景不可见
    //获取选中的用户信息
    QVariant var = index.data(Qt::UserRole+1);
    UserItemData ItemData = var.value<UserItemData>();
    QString sUserName = ItemData.sUserName;
    QString headpics = ItemData.sHeadPic;
    ui->FriendNameLabel->setText(sUserName);
    ui->StateLabel->setText("在线");
    ui->FriendHead->setPixmap(QPixmap(headpics));
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::sendUserData(int data)
{
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
void MainWindow::initMainWindow()
{

}
