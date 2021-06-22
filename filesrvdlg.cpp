#include "filesrvdlg.h"
#include "ui_filesrvdlg.h"

FileSrvDlg::FileSrvDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileSrvDlg)
{
    ui->setupUi(this);
    myTcpSrv = new QTcpServer(this);
    mySrvPort = 5555; //统一设置端口

    //建立监听连接  当有新TCP创建，即出发文件传输
    connect(myTcpSrv, SIGNAL(newConnection()), this, SLOT(sndChatMsg()));

    //TCP连接建立标志
    connect(this,&FileSrvDlg::TCPCntflag,[=]()
    {
        flag= true;
    });
    initServer();

}

void FileSrvDlg::initServer()
{
    //传输相关属性定义
    myTotalBytes = 0;
    mySendBytes = 0;
    myBytesTobeSend = 0;
    myPayloadSize = 64 * 1024;
    ui->label->setText(tr("请选择要传送的文件"));
    ui->sendProgressBar->reset();
    ui->sfileNameLineEdit->clear();
    ui->sendSizeLineEdit->clear();
    ui->sfileSizeLineEdit->clear();
    ui->openFilePushButton->setEnabled(true);
    ui->sendFilePushButton->setEnabled(false);

    //参数设置OK，关闭服务器
    myTcpSrv->close();

}

FileSrvDlg::~FileSrvDlg()
{
    delete ui;
}

//TCP发送文件头： 文件名+文件大小
void FileSrvDlg::sndChatMsg()
{
    emit this->TCPCntflag();
    ui->sendFilePushButton->setEnabled(false);
    mySrvSocket = myTcpSrv->nextPendingConnection();
    connect(mySrvSocket, SIGNAL(error(QAbstractSocket::SocketError)),
                this, SLOT(TCPCntError(QAbstractSocket::SocketError)));
    connect(mySrvSocket, SIGNAL(bytesWritten(qint64)),
            this, SLOT(refreshProgress(qint64)));
    ui->label->setText(tr("开始传送文件 ！"));
    myLocPathFile = new QFile(myPathFile);  //全局文件路径
    if(!myLocPathFile->open((QFile::ReadOnly))){
        QMessageBox::warning(this, tr("应用程序"), tr("无法读取文件 %1:\n%2")
                             .arg(myFileName).arg(myLocPathFile->errorString()));
        return;
    }
    myTotalBytes = myLocPathFile->size(); //文件的字节数
    QDataStream sendOut(&myOutputBlock, QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_5_9);
    mytime.start();  // 开始计时

    //保存文件名至临时curfile
    QString curFile = myPathFile.right(myPathFile.size()
                                       - myPathFile.lastIndexOf('/') - 1);
    sendOut << qint64(0) << qint64(0) << curFile;

    //TCP传输的内容实际大小：文件头+文件内容
    myTotalBytes += myOutputBlock.size();
    sendOut.device()->seek(0);
    sendOut << myTotalBytes << qint64((myOutputBlock.size() - sizeof(qint64) * 2));
    myBytesTobeSend = myTotalBytes - mySrvSocket->write(myOutputBlock);
    myOutputBlock.resize(0);
}

//TCP更新进度条，并发送文件内容
void FileSrvDlg::refreshProgress(qint64 bynum)
{
    qApp->processEvents();
    mySendBytes += (int)bynum;
    if (myBytesTobeSend > 0)
    {
        myOutputBlock = myLocPathFile->read(qMin(myBytesTobeSend, myPayloadSize));
        myBytesTobeSend -= (int)mySrvSocket->write(myOutputBlock);
        myOutputBlock.resize(0);
    } else {
        myLocPathFile->close();
    }
    ui->sendProgressBar->setMaximum(myTotalBytes);
    ui->sendProgressBar->setValue(mySendBytes);
    ui->sfileSizeLineEdit->setText(tr("%1").arg(myTotalBytes / (1024 * 1024)) + " MB");
    ui->sendSizeLineEdit->setText(tr("%1").arg(mySendBytes / (1024 * 1024)) + " MB");
    if(mySendBytes == myTotalBytes)
    {
        myLocPathFile->close();
        myTcpSrv->close();
        ui->label->setText(tr("传送完成"));
        QMessageBox::information(0, QObject::tr("完毕"), "文件传输完成！");
    }
}

//打开文件按钮，获取文件名 全局变量myFileName  全局变量文件路径myPathFile
void FileSrvDlg::on_openFilePushButton_clicked()
{
    myPathFile = QFileDialog::getOpenFileName(this);
    if(!myPathFile.isEmpty())
    {
        myFileName = myPathFile.right(myPathFile.size() - myPathFile.lastIndexOf('/') - 1);
        ui->sfileNameLineEdit->setText(tr("%1").arg(myFileName));
        ui->sendFilePushButton->setEnabled(true);
        ui->openFilePushButton->setEnabled(false);
    }
}

//文件发送按钮
void FileSrvDlg::on_sendFilePushButton_clicked()
{
    if(!myTcpSrv->listen(QHostAddress::Any, mySrvPort))//开始监听
    {
        QMessageBox::warning(0, QObject::tr("异常"), "打开TCP端口出错,请检查网络连接！");
        close();
        return;
    }
    ui->label->setText(tr("等待对方接收... ..."));
    emit sendFileName(myFileName);
}

//服务器窗口停止按钮
void FileSrvDlg::on_srvClosePushButton_clicked()
{
    if(flag){
        if(myTcpSrv->isListening())
        {
            myTcpSrv->close();
            myLocPathFile->close();
            mySrvSocket->abort();
        }
        this->close();
        this->setAttribute(Qt::WA_DeleteOnClose, true);
    }
    else {
        if(myTcpSrv->isListening())
        {

            myTcpSrv->close();
        }
        this->close();
        this->setAttribute(Qt::WA_DeleteOnClose, true);
    }


}

void FileSrvDlg::cntRefused()
{
    myTcpSrv->close();
    QMessageBox::warning(0, QObject::tr("提示"), "对方拒绝接收！");
    myLocPathFile->close();
    this->close();
    this->setAttribute(Qt::WA_DeleteOnClose, true);
}

void FileSrvDlg::closeEvent(QCloseEvent *)
{
    on_srvClosePushButton_clicked();
}

void FileSrvDlg::TCPCntError(QAbstractSocket::SocketError)
{
    int error = mySrvSocket->error();
    qDebug()<<mySendBytes<<myTotalBytes;
    if(mySendBytes != myTotalBytes)
    {
        switch(error)
        {
            case QAbstractSocket::RemoteHostClosedError://客户端断开
            {
                QString hostAddress=mySrvSocket->QAbstractSocket::peerAddress().toString();
                QMessageBox::information(this, "错误", "远程IP："+hostAddress
                                                       + "\n已断开连接");

                on_srvClosePushButton_clicked();
                break;
            }
            default:
            {
                error = -1;
                //QMessageBox::information(this, "错误", mySrvSocket->errorString());
                QMessageBox::information(this, "错误", "TCP连接断开");
                break;
            }
        }
    }

 }
