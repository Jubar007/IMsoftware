#include "friendgroup.h"
#include "ui_friendgroup.h"
#include <QPainter>
#include "sqlite.h"
#include <QDebug>


friendGroup::friendGroup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::friendGroup)
{
    ui->setupUi(this);
    //提示文字
    ui->lineEdit->setPlaceholderText("请输入新的分组名称...");
}
//查找用户的分组
void friendGroup::getGroups(QString uid){
    Sqlite *db = new Sqlite("sqlite/simpleChat.db");
    QString sql ="select * from FriendGroups where FG_UserID="+uid;
    if(db->db_query(sql))
    {
        while(db->query.next()){
            //用户及用户的好友数据更新
            QStringList info;
            info.append(db->query.value("FG_ID").toString());//0
            info.append(db->query.value("FG_Name").toString());
            ui->comboBox->addItem(db->query.value("FG_Name").toString());
            info.append(db->query.value("FG_UserID").toString());
            grouplist.append(info);
        }
     }
     QString sqlCount ="select count(FG_ID) from FriendGroups";
     if(db->db_query(sqlCount))
     {
         while(db->query.next()){
             count = db->query.value("count(FG_ID)").toInt();
         }
      }
     qDebug()<<count;
}
//设置背景图片
void friendGroup::paintEvent(QPaintEvent *)
{
   QPainter painter(this);
   painter.setRenderHints(QPainter::SmoothPixmapTransform);
   painter.drawPixmap(rect(),QPixmap(":/img/perfectData.jpg"),QRect());
}
//接收传送过来的值
void friendGroup::getFriendData(QString uid,QString fid,QString fgname){
    this->uid = uid;
    this->fid = fid;
    this->fgname= fgname;
    getGroups(uid);
    ui->comboBox->setEditText(fgname);
}
friendGroup::~friendGroup()
{
    delete ui;
}

void friendGroup::on_addGPushButton_clicked()
{
    Sqlite *db = new Sqlite("sqlite/simpleChat.db");

    QString Fname = ui->lineEdit->text();
    count = count + 1;
    QString insertSql ="insert into FriendGroups values("+QString::number(count)+",'"+Fname+"',"+uid+")";
    QStringList info;
    info.append(QString::number(count));//0
    info.append(Fname);
    info.append(uid);
    grouplist.append(info);
    bool successInsert = db->db_query(insertSql);
    if(!successInsert){
        qDebug()<<"插入数据库失败！";
        return;
    }
     ui->comboBox->addItem(Fname);
}

void friendGroup::on_OKPushButton_clicked()
{
    QString gid;

    QString Fname = ui->comboBox->currentText();
    if(Fname=="")   return;
    for(int i = 0;i<grouplist.size();++i){
        if(Fname==grouplist[i][1]){
            gid = grouplist[i][0];
            break;
        }
    }
    QString updateSql = "update Friends set F_FriendGroupsID="+gid+" where F_FirendID = "+fid+" and F_UserID = "+uid;
    //qDebug()<<updateSql;
    Sqlite *db = new Sqlite("sqlite/simpleChat.db");
    bool successUpdate = db->db_query(updateSql);
    if(!successUpdate){
        qDebug()<<"更新数据库失败！";
        return;
    }
    sendData(Fname);
}
