#include "addnews.h"
#include "ui_addnews.h"
#include "sqlite.h"
#include <QDebug>
#include <QPainter>

addNews::addNews(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addNews)
{
    ui->setupUi(this);
    //提示文字
    ui->SearchLineEdit->setPlaceholderText("用户昵称/群名称");
    ui->verifyTextEdit->setPlaceholderText("我是...");
}
//设置背景图片
void addNews::paintEvent(QPaintEvent *)
{
   QPainter painter(this);
   painter.setRenderHints(QPainter::SmoothPixmapTransform);
   painter.drawPixmap(rect(),QPixmap(":/img/perfectData.jpg"),QRect());
}
addNews::~addNews()
{
    delete ui;
}
//接收主界面的传值
void addNews::sendData(QList<QStringList> data)
{
    myInfo = data;
}

//点击搜索按钮
void addNews::on_searchPushButton_clicked()
{
    QString name=ui->SearchLineEdit->text();
    Sqlite *db = new Sqlite("sqlite/simpleChat.db");
    QString sql = "select * from User where U_NickName='"+name+"'";
    //qDebug()<<sql;
    uid="";
    if(db->db_query(sql))
    {
        setFixedSize(379,348);
        while(db->query.next())//一行一行遍历
        {
        QPixmap pix;
        QImage image(db->query.value("U_HeadPortrait").toString());
        ui->headLabel->setPixmap(pix.fromImage(image));
        ui->headLabel->setScaledContents(true);
        ui->headLabel->show();

        ui->nameLabel->setText(db->query.value("U_NickName").toString());
        ui->signalLabel->setText(db->query.value("U_SignaTure").toString());

        ui->remarkLineEdit->setText(db->query.value("U_NickName").toString());
        uid = db->query.value("U_ID").toString();
    }
      }
    else{
        qDebug()<<"没有找到相关人/群";
    }
}

void addNews::on_sendPushButton_clicked()
{
    if(uid== "")
        return;
    //查找自己是不是有这个好友
    for (int i=1; i<myInfo.size(); ++i) {
        if(myInfo[i][0]==uid)
            return;
    }
    //插入数据库
    QString reason = ui->verifyTextEdit->toPlainText();
    QString toNick=ui->remarkLineEdit->text();
    QString sql = "INSERT INTO Friends VALUES("+uid+","+myInfo[0][0]+",'"+toNick+"',"+myInfo[0][0]+",False,'"+reason+"')";

    qDebug()<<sql;
    Sqlite *db = new Sqlite("sqlite/simpleChat.db");
    bool success = db->db_query(sql);
    if(!success){
        qDebug()<<"插入数据库失败！";
        return;
    }else{
        ui->sendPushButton->setEnabled(false);//发送申请按钮不可用
    }
}
