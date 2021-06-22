#include "perfectpersonaldata.h"
#include "ui_perfectpersonaldata.h"
#include <QPainter>
#include <QDebug>
#include "sqlite.h"

perfectPersonalData::perfectPersonalData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::perfectPersonalData)
{
    ui->setupUi(this);

}
//设置背景图片
void perfectPersonalData::paintEvent(QPaintEvent *)
{
   QPainter painter(this);
   painter.setRenderHints(QPainter::SmoothPixmapTransform);
   painter.drawPixmap(rect(),QPixmap(":/img/perfectData.jpg"),QRect());
}
//接收从主界面的传值并绑定在控件上
void perfectPersonalData::getUersData(QStringList data){
    userid = data[0];
    ui->NicknameLineEdit->setText(data[1]);
    if(data[3]=="1")
        ui->sexComboBox->setEditText("男");
    else if(data[3]=="2")
        ui->sexComboBox->setEditText("女");
    else
        ui->sexComboBox->setEditText("未知");
    QDateTime dt = QDateTime::fromString(data[4].mid(0,19), "yyyy-MM-dd hh:mm:ss");
    //qDebug()<<data[4].mid(0,19);
    //qDebug()<<dt.toString("yyyy-MM-dd hh:mm:ss");
    ui->birthDateTimeEdit->setDateTime(dt);
    ui->EmailLneEdit->setText(data[6]);
    ui->phoneLineEdit->setText(data[5]);
    ui->synopsisTextEdit->setText(data[2]);
}
perfectPersonalData::~perfectPersonalData()
{
    delete ui;
}

//关闭按钮
void perfectPersonalData::on_closePushButton_clicked()
{
    this->close();
}
//保存按钮
void perfectPersonalData::on_savePushButton_clicked()
{
    //获取用户输入的信息
    QString nickname = ui->NicknameLineEdit->text();
    QString sexIndex = QString::number(ui->sexComboBox->currentIndex()+1);
   //qDebug()<<sexIndex;
   QString sex = ui->sexComboBox->currentText();
    QString head=":/img/boy.png";
    if(sex=="女") head=":/img/girl.png";
    QDateTime dt = ui->birthDateTimeEdit->dateTime();
    QString dtStr = dt.toString("yyyy-MM-dd hh:mm:ss");
    QString email = ui->EmailLneEdit->text();
    QString phone = ui->phoneLineEdit->text();
    QString syno = ui->synopsisTextEdit->toPlainText();
    //数据库更新
    QString sql = "update User set U_NickName='"+nickname+"',U_SignaTure='"+syno+"',U_Sex="+sexIndex+",U_Birthday='"+dtStr+"',U_Telephone='"+phone+"',U_Email='"+email+"',U_HeadPortrait='"+head+"' where U_ID="+userid;
    //qDebug()<<sql;
    Sqlite *db = new Sqlite("sqlite/simpleChat.db");
    bool success = db->db_query(sql);
    if(!success){
        qDebug()<<"更新数据库失败！";
        return;
    }
    manData.clear();
    manData.append(nickname);
    manData.append(sexIndex);
    manData.append(head);
    manData.append(dtStr);
    manData.append(email);
    manData.append(phone);
    manData.append(syno);
    emit sendData(manData);
}
