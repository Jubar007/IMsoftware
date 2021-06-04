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

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    //去除窗口边框样式
    this->setWindowFlags(Qt::FramelessWindowHint);
    //登录按钮按下调用showChatWindow函数
    connect(ui->loginPushButton, &QPushButton::clicked, this, &LoginDialog::showChatWindow);
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

    //打印QT支持的数据库驱动("QSQLITE"静态数据库, "QODBC", "QODBC3", "QPSQL", "QPSQL7")
    qDebug()<<QSqlDatabase::drivers();
    QTextCodec::setCodecForLocale (QTextCodec:: codecForLocale ()) ; //设置中文显示
    //添加sqlite数据库
    QSqlDatabase db =QSqlDatabase::addDatabase("QSQLITE");
    //设置数据库
    db.setDatabaseName("D:\\02_work\\04_QT\\04_IMsoft\\MyWeiXin0531\\sqlite\\simpleChat.db");
    //打印当前目录
    QString curpath = QDir::currentPath();
    qDebug()<<curpath;
    //打开数据库
    if(!db.open()){//数据库打开失败
        qDebug()<<db.lastError().text();
        return;
    }//打开成功之后执行下面
    QSqlQuery query;
        //如果数据库打开成功，就创建一个关联的QSqlQuery对象，最后由QSqlQuery来执行插入数据工作。
        //特别注意：QSqlQuery对象的创建必须在db文件open成功以后才行，否则会出错。
        //查询用户名和密码
    QString uname=ui->usrLineEdit->text();
    QString password=ui->pwdLineEdit->text();
    QString match_password;
    if(query.exec("select U_ID,U_NickName,U_PassWord from User"))
    {
                //qDebug()<<"读取成功";
                //定义登陆界面的两个文本框输入的内容

                if(uname==nullptr&&password==nullptr)
                {
                    //如果输入为空
                    QMessageBox::warning(this,QString(tr("Waring")),
                                             QString(tr("输入不能为空！请重新输入！")));
                    return;
                }
                bool seek = false;//是否找到用户名
                while(query.next())//一行一行遍历
                {
                    //取出当前行的内容
                    //qDebug()<<query.value("U_NickName").toString()<<query.value("U_PassWord").toString();
                    if(uname==query.value("U_NickName").toString()) {
                        seek = true;
                        //密码不正确
                        if(!(password == query.value("U_PassWord").toString())){
                            QMessageBox::warning(nullptr, QObject::tr("提示"), "密码错误！请重新输入。");
                            ui->pwdLineEdit->clear();
                            ui->pwdLineEdit->setFocus();
                            return;
                        }
                        else{
                            usrid = query.value("U_ID").toInt();
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
          chatWindow = new MainWindow(0);
          // TODO: chatWindow p2p聊天
          chatWindow->setWindowTitle(ui->usrLineEdit->text());
          chatWindow->sendUserData(usrid); //直接调用public函数将本页面中lineEdit的数据传递过去
          chatWindow->show();
          db.close();
          return;
    }
 }

