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
    //打印当前目录
    qDebug()<<QCoreApplication::applicationDirPath();
    Sqlite *db = new Sqlite("/Users/yanglei/04_QT/04_serverIM/serverLoc/sqlite/simpleChat.db");
    db->db_query("select U_ID,U_NickName,U_PassWord from User");
    ui->usrLineEdit->setVisible(true);
    ui->pwdLineEdit->setVisible(true);
    ui->loginPushButton->setVisible(true);
    //快速登录
    ui->usrLineEdit->setText("吴汶憶");
    ui->pwdLineEdit->setText("111");
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

    //初始化登陆窗口UDP
    logUdpSocket = new QUdpSocket(this);

    //UDP监听端口绑定
    myUdpPort = 5000;
    //允许多机器同IP，同端口| 失败重连
    logUdpSocket->bind(myUdpPort, QUdpSocket::ShareAddress|QUdpSocket::ReuseAddressHint);
    connect(logUdpSocket, SIGNAL(readyRead()), this, SLOT(logCntRcv()));
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
//登陆客户端UDP发送
void LoginDialog::logCntSend(ChatMsgType msgType,QString usrName,QString passWord,QStringList info)
{
    QByteArray qba;
    QDataStream write(&qba, QIODevice::WriteOnly);
    write << msgType ;
    switch (msgType)
    {
    case signIn:
    {
        write<<usrName<<passWord<<info;
    }
        break;
    case logIn:
    {
        write<<usrName<<passWord;
        qDebug()<<"登陆界面发送"<<usrName<<passWord;
    }
        break;
    }
    //UDP数据发送，发送至本机IP，端口5000
    logUdpSocket->writeDatagram(qba, qba.length(), QHostAddress::LocalHost, 1234);  //完成消息处理后，发出广播
}
//登陆客户端UDP接收
void LoginDialog::logCntRcv()
{
    qDebug()<<"客户端，已经收udp";
    QByteArray qba;
    qba.resize(logUdpSocket->pendingDatagramSize());
    logUdpSocket->readDatagram(qba.data(), qba.size());
    QDataStream read(&qba, QIODevice::ReadOnly);
    QString usrName,passWord;
    QList<QStringList> udpUsrList;
    int msgType;
    read >> msgType; //第一个数据就是  消息类型
    switch (msgType)
    {
    case verLogin:
        //确认登录后，获取到个人及好友信息
        read>>usrName>>passWord>>udpUsrList;
        qDebug()<<"udp客户端收到验证"<<usrName<<passWord;
        if(usrName==ui->usrLineEdit->text()&&passWord==ui->pwdLineEdit->text())//服务器传回用户名
        {
            qDebug()<<"准备显示主界面";
            qDebug()<<udpUsrList;
            showChatWindow(udpUsrList);//TODO:原函数需要更改，部分移植服务器
        }
        break;
    case logInerro:
        read>>usrName>>passWord;
        if(usrName==ui->usrLineEdit->text()&&passWord==ui->pwdLineEdit->text())
        {
            QMessageBox::warning(0, tr("警告"), tr("用户名或密码错误！"), QMessageBox::Ok);
        }
        break;
    }

}
//服务器确认登陆操作，弹出主界面
void LoginDialog::showChatWindow(QList<QStringList> udpUsrList)
{
    chatWindow = new MainWindow();
    qDebug()<<"主界面1";
    chatWindow->setWindowTitle(ui->usrLineEdit->text());
    qDebug()<<"主界面2";
    chatWindow->sendUserData(udpUsrList); //直接调用public函数将本页面中lineEdit的数据传递过去
    qDebug()<<"主界面3";
    chatWindow->show();

}
//选择登录界面
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
//选择注册界面
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
    QStringList info;
    info.append(email);
    info.append(phone);
    logCntSend(signIn,usrname,pwd,info);

    ui->usrLineEdit->setText(usrname);
}
//点击登录按钮
void LoginDialog::on_loginPushButton_clicked()
{
    QString uname=ui->usrLineEdit->text();
    QString password=ui->pwdLineEdit->text();
    qDebug()<<"点击登录,调用udp"<<uname<<password;
    logCntSend(logIn,uname,password);

}
//登录的电话检测
bool LoginDialog::queryphone(QString phone){
    Sqlite *db = new Sqlite("/sqlite/simpleChat.db");
    //判断数据库中是否存在所输入号码
    QString sql = "select * from User  where U_Telephone='"+phone+"'";
    db->db_query(sql);
    if(db->query.next())
        return true;
    else
        return false;
}
