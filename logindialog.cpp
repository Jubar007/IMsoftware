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
    ui->usrLineEdit->setVisible(true);
    ui->pwdLineEdit->setVisible(true);
    ui->loginPushButton->setVisible(true);

    ui->s_usrLineEdit->setVisible(false);
    ui->s_EmailLineEdit->setVisible(false);
    ui->s_phoneLineEdit->setVisible(false);
    ui->s_pwdLineEdit->setVisible(false);
    ui->signPushButton->setVisible(false);
    ui->s_noiticeLabel->setVisible(false);

    //提示文字
    ui->usrLineEdit->setPlaceholderText("输入用户名...");
    ui->pwdLineEdit->setPlaceholderText("输入密码...");
    ui->s_usrLineEdit->setPlaceholderText("设置用户名...");
    ui->s_EmailLineEdit->setPlaceholderText("输入邮箱...");
    ui->s_phoneLineEdit->setPlaceholderText("输入联系方式...");
    ui->s_pwdLineEdit->setPlaceholderText("设置密码...");
    //快速登录
    //ui->usrLineEdit->setText("吴汶憶");
    //ui->pwdLineEdit->setText("111");
}
//设置背景图片
void LoginDialog::paintEvent(QPaintEvent *)
{
   QPainter painter(this);
   painter.setRenderHints(QPainter::SmoothPixmapTransform);
   painter.drawPixmap(rect(),QPixmap(":/img/loginBg.jpg"),QRect());
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
//点击登录界面
void LoginDialog::on_selectLoginButton_clicked()
{
    //绘制背景图
    QPixmap pix;
    QImage image(":/img/loginBg.jpg");
    ui->bgLabel->setPixmap(pix.fromImage(image));
    ui->bgLabel->setScaledContents(true);
    ui->bgLabel->show();
    //控件可见性设置
    ui->usrLineEdit->setVisible(true);
    ui->pwdLineEdit->setVisible(true);
    ui->loginPushButton->setVisible(true);

    ui->s_usrLineEdit->setVisible(false);
    ui->s_EmailLineEdit->setVisible(false);
    ui->s_phoneLineEdit->setVisible(false);
    ui->s_pwdLineEdit->setVisible(false);
    ui->s_noiticeLabel->setVisible(false);
    ui->signPushButton->setVisible(false);
    //提示文字
    ui->usrLineEdit->setPlaceholderText("输入用户名...");
    ui->pwdLineEdit->setPlaceholderText("输入密码...");
}
//用户选择注册界面
void LoginDialog::on_selectSignButton_clicked()
{
    //绘制背景图
    QPixmap pix;
    QImage image(":/img/signInBg.jpg");
    ui->bgLabel->setPixmap(pix.fromImage(image));
    ui->bgLabel->setScaledContents(true);
    ui->bgLabel->show();
    //控件可见性设置
    ui->usrLineEdit->setVisible(false);
    ui->pwdLineEdit->setVisible(false);
    ui->loginPushButton->setVisible(false);

    ui->s_usrLineEdit->setVisible(true);
    ui->s_EmailLineEdit->setVisible(true);
    ui->s_phoneLineEdit->setVisible(true);
    ui->s_pwdLineEdit->setVisible(true);
    ui->s_noiticeLabel->setVisible(true);
    ui->signPushButton->setVisible(true);
    //提示文字
    ui->s_usrLineEdit->setPlaceholderText("设置用户名...");
    ui->s_EmailLineEdit->setPlaceholderText("输入邮箱...");
    ui->s_phoneLineEdit->setPlaceholderText("输入联系方式...");
    ui->s_pwdLineEdit->setPlaceholderText("设置密码...");
    ui->s_noiticeLabel ->setStyleSheet("color:red;");
}
//点击注册按钮
void LoginDialog::on_signPushButton_clicked()
{
    QString usrname=ui->s_usrLineEdit->text();
    QString email=ui->s_EmailLineEdit->text();
    QString phone = ui->s_phoneLineEdit->text();
    QString pwd = ui->s_pwdLineEdit->text();
    if(queryphone(phone)){
        ui->s_noiticeLabel ->setText("该联系方式已存在！");
        return;
    }
    QString sql = "INSERT INTO User VALUES("+phone+",'"+usrname+"','"+pwd+"','无',3,null,'"+phone+"','"+email+"',':/img/boy.png',0)";
    qDebug()<<sql;
    Sqlite *db = new Sqlite("sqlite/simpleChat.db");
    bool success = db->db_query(sql);
    if(!success){
        qDebug()<<"插入数据库失败！";
        return;
    }
    ui->usrLineEdit->setText(usrname);
}

//登录的电话检测
bool LoginDialog::queryphone(QString phone){
    Sqlite *db = new Sqlite("sqlite/simpleChat.db");
    //判断数据库中是否存在所输入号码
    QString sql = "select * from User  where U_Telephone='"+phone+"'";
    db->db_query(sql);
    if(db->query.next())
        return true;
    else
        return false;
}
