#include "changeremark.h"
#include "ui_changeremark.h"
#include <QPainter>
#include "sqlite.h"
#include <QDebug>

changeRemark::changeRemark(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::changeRemark)
{
    ui->setupUi(this);
}
//设置背景图片
void changeRemark::paintEvent(QPaintEvent *)
{
   QPainter painter(this);
   painter.setRenderHints(QPainter::SmoothPixmapTransform);
   painter.drawPixmap(rect(),QPixmap(":/img/perfectData.jpg"),QRect());
}
//接收传送过来的值
void changeRemark::getFriendData(QString uid,QString fid,QString fname){
    this->uid = uid;
    this->fid = fid;
    this->fname = fname;
    ui->lineEdit->setText(fname);
}

changeRemark::~changeRemark()
{
    delete ui;
}
//修改好友的备注
void changeRemark::on_OKPushButton_clicked()
{
    if( ui->lineEdit->text()=="") return;//备注不能为空
    QString f_name = ui->lineEdit->text();
    QString updateSql = "update Friends set F_Name='"+f_name+"' where F_FirendID = "+fid+" and F_UserID = "+uid;
    Sqlite *db = new Sqlite("sqlite/simpleChat.db");
    bool successUpdate = db->db_query(updateSql);
    if(!successUpdate){
        qDebug()<<"更新数据库失败！";
        return;
    }
    emit sendData(f_name);
    this->close();
}
