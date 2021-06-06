#include "logindialog.h"
#include "ui_logindialog.h"
#include <QPainter>
#include <QDebug>
#include <QTextCodec>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QDir>
#include "mainwindow.h"
#include "sqlite.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    //去除窗口边框样式
    this->setWindowFlags(Qt::FramelessWindowHint);
    //登录按钮按下调用showChatWindow函数
    connect(ui->loginPushButton, &QPushButton::clicked, this, &LoginDialog::showChatWindow);
    //首次连接执行sql会失败，放在初始化处
    Sqlite *db = new Sqlite("sqlite/simpleChat.db");
    db->db_query("select U_ID,U_NickName,U_PassWord from User");
    //快速登录
    ui->usrLineEdit->setText("吴汶憶");
    ui->pwdLineEdit->setText("111");
}
//设置背景图片
void LoginDialog::paintEvent(QPaintEvent *)
{
   QPainter painter(this);
   painter.drawPixmap(rect(),QPixmap(":/img/bgLogin.jpg"),QRect());
}

LoginDialog::~LoginDialog()
{
    delete ui;
}
//处理用户登录操作
void LoginDialog::showChatWindow()
{
    QTextCodec::setCodecForLocale (QTextCodec:: codecForLocale ()) ; //设置中文显示
    Sqlite *db = new Sqlite("sqlite/simpleChat.db");
    QString uname=ui->usrLineEdit->text();
    QString password=ui->pwdLineEdit->text();
    QString match_password;
    if(db->db_query("select * from User"))
    {
          //qDebug()<<"读取成功";
                //定义登陆界面的两个文本框输入的内容

                if(uname==NULL&&password==NULL)
                {
                    //如果输入为空
                    QMessageBox::warning(this,QString(tr("Waring")),
                                             QString(tr("输入不能为空！请重新输入！")));
                    return;
                }
                bool seek = false;//是否找到用户名
                //qDebug()<<typeid(db->query).name();//打印查询结果类型QSqlQuery
                while(db->query.next())//一行一行遍历
                {
                    if(uname==db->query.value("U_NickName").toString()) {
                        seek = true;
                        //密码不正确
                        if(!(password == db->query.value("U_PassWord").toString())){
                            QMessageBox::warning(0, QObject::tr("提示"), "密码错误！请重新输入。");
                            ui->pwdLineEdit->clear();
                            ui->pwdLineEdit->setFocus();
                            return;
                        }
                        else{
                            usrsInfo.clear();//清除之前用户登录的数据
                            //添加当前用户信息
                            QStringList info;
                            info.append(db->query.value("U_ID").toString());
                            info.append(db->query.value("U_NickName").toString());
                            info.append(db->query.value("U_SignaTure").toString());
                            info.append(db->query.value("U_Sex").toString());
                            info.append(db->query.value("U_Birthday").toString());
                            info.append(db->query.value("U_Telephone").toString());
                            info.append(db->query.value("U_Email").toString());
                            info.append(db->query.value("U_HeadPortrait").toString());
                            info.append("在线");
                            usrsInfo.append(info);
                            break;//用户的用户名密码正确时，停止循环
                        }
                    }
                }
                if(!seek){
                    QMessageBox::warning(this, QObject::tr("提示"), "此用户不存在！请重新输入。");
                    ui->usrLineEdit->clear();
                    ui->pwdLineEdit->clear();
                    ui->usrLineEdit->setFocus();
                    return;
          }
          chatWindow = new MainWindow();
          chatWindow->setWindowTitle(ui->usrLineEdit->text());
          chatWindow->sendUserData(usrsInfo); //直接调用public函数将本页面中lineEdit的数据传递过去
          chatWindow->show();
    }
 }
