#include "agreefriend.h"
#include "ui_agreefriend.h"
#include "useritemdelegate.h"
#include "UserListData.h"
#include <QPainter>
#include "sqlite.h"

agreeFriend::agreeFriend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::agreeFriend)
{
    ui->setupUi(this);
}
//设置背景图片
void agreeFriend::paintEvent(QPaintEvent *)
{
   QPainter painter(this);
   painter.setRenderHints(QPainter::SmoothPixmapTransform);
   painter.drawPixmap(rect(),QPixmap(":/img/perfectData.jpg"),QRect());
}
//获取主界面传递过来的数据
void agreeFriend::getFriendData(QList<QStringList> data,QString id){
    newFriendInfo = data;
    uid = id;
    //绑定ListView
    m_pModel = new QStandardItemModel;
    for (int i=0; i<newFriendInfo.size(); ++i) {
        QStandardItem *pItem = new QStandardItem;
        UserItemData ItemData;
        ItemData.sUserName = newFriendInfo[i][0];
        ItemData.userSignalTrue = newFriendInfo[i][2];
        ItemData.sHeadPic = newFriendInfo[i][1];
        pItem->setData(QVariant::fromValue(ItemData), Qt::UserRole+1);
        m_pModel->appendRow(pItem);
    }
    UserItemDelegate* pUserItemDelegate = new UserItemDelegate;
    ui->listView->setItemDelegate(pUserItemDelegate);
    ui->listView->setModel(m_pModel);
}

agreeFriend::~agreeFriend()
{
    delete ui;
}
//单击ListView中的一行
void agreeFriend::on_listView_clicked(const QModelIndex &index)
{
    setFixedSize(530,300);//改变窗口大小
    s = index.row();
    QPixmap pix1;
    QImage image1(newFriendInfo[s][1]);//filename，图片的路径名字
    ui->head->setPixmap(pix1.fromImage(image1));// ui->pix就是label的控件名字
    ui->head->setScaledContents(true);
    ui->head->show();
    ui->nickName->setText(newFriendInfo[s][0]);
    ui->intro->setText(newFriendInfo[s][3]);
    if(newFriendInfo[s][2]!="")
        ui->nickLineEdit->setText(newFriendInfo[s][2]);
    else
        ui->nickLineEdit->setText(newFriendInfo[s][0]);
}

void agreeFriend::on_agreePushButton_clicked()
{
    QString updateSql = "update Friends set isFriend=true where F_FirendID = "+uid+" and F_UserID = "+newFriendInfo[s][4];
    //qDebug()<<updateSql;
    Sqlite *db = new Sqlite("sqlite/simpleChat.db");
    bool successUpdate = db->db_query(updateSql);
    if(!successUpdate){
        qDebug()<<"更新数据库失败！";
        return;
    }
    QString Fname = ui->nickLineEdit->text();
    QString insertSql ="insert into Friends values("+newFriendInfo[s][4]+","+uid+",'"+Fname+"',"+uid+",true,null)";
    bool successInsert = db->db_query(insertSql);
    if(!successInsert){
        qDebug()<<"插入数据库失败！";
        return;
    }
   //按钮不可用
    ui->agreePushButton->setEnabled(false);
    ui->disagreePushButton->setEnabled(false);
    emit sendData(uid);

    this->close();

}
