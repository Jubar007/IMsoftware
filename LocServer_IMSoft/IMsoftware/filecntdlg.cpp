#include "filecntdlg.h"
#include "ui_filecntdlg.h"
#include <QMessageBox>


FileCntDlg::FileCntDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileCntDlg)
{
    ui->setupUi(this);
    myCntSocket = new QTcpSocket(this);
    mySrvPort = 5555;
    connect(myCntSocket, SIGNAL(readyRead()), this, SLOT(readChatMsg()));
    connect(myCntSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(TCPCntError(QAbstractSocket::SocketError)));
    myFileNameSize = 0;
    myTotalBytes = 0;
    myRcvedBytes = 0;
}

FileCntDlg::~FileCntDlg()
{
    delete ui;
}

void FileCntDlg::getLocPath(QString lpath)
{
    myLocPathFile = new QFile(lpath);
}

void FileCntDlg::getSrvAddr(QHostAddress saddr)
{
    mySrvAddr = saddr;
    createConnToSrv();
}

void FileCntDlg::createConnToSrv()
{
    myBlockSize = 0;
    myCntSocket->abort();
    myCntSocket->connectToHost(mySrvAddr, mySrvPort);
    mytime.start();
}

void FileCntDlg::readChatMsg()
{
    int error= myCntSocket->error();
    QDataStream in(myCntSocket);
    in.setVersion(QDataStream::Qt_5_9);
    float usedTime = mytime.elapsed();
    if (myRcvedBytes <= sizeof(qint64)*2)
    {
        if ((myCntSocket->bytesAvailable() >= sizeof(qint64)*2) && (myFileNameSize == 0))
        {
            //写入文件头  实际大小+文件大小
            in >> myTotalBytes >> myFileNameSize;
            myRcvedBytes += sizeof(qint64)*2;
        }
        if ((myCntSocket->bytesAvailable() >= myFileNameSize) && (myFileNameSize != 0))
        {
            //写入文件头  文件名
            in >> myFileName;
            myRcvedBytes += myFileNameSize;
            myLocPathFile->open(QFile::WriteOnly);
            ui->rfileNameLineEdit->setText(myFileName);
        } else {
            return;
        }
    }
    if (myRcvedBytes < myTotalBytes)
    {
        myRcvedBytes += myCntSocket->bytesAvailable();
        //读取文件内容
        myInputBlock = myCntSocket->readAll();

        myLocPathFile->write(myInputBlock);
        myInputBlock.resize(0);
    }
    ui->recvProgressBar->setMaximum(myTotalBytes);
    ui->recvProgressBar->setValue(myRcvedBytes);
    double transpeed = myRcvedBytes / usedTime;
    ui->rfileSizeLineEdit->setText(tr("%1").arg(myTotalBytes / (1024 * 1024)) + " MB");
    ui->recvSizeLineEdit->setText(tr("%1").arg(myRcvedBytes / (1024 * 1024)) + " MB");
    ui->rateLabel->setText(tr("%1").arg(transpeed * 1000 / (1024 * 1024), 0, 'f', 2) + " MB/秒");

    if (myRcvedBytes == myTotalBytes)
    {
        myLocPathFile->close();
        myCntSocket->close();
        ui->rateLabel->setText("接收完毕！");
    }

}

void FileCntDlg::on_cntClosePushButton_clicked()
{
    myCntSocket->abort();
    myLocPathFile->close();
    close();
}

void FileCntDlg::closeEvent(QCloseEvent *)
{
    on_cntClosePushButton_clicked();
}

//检查TCP连接错误
void FileCntDlg::TCPCntError(QAbstractSocket::SocketError)
{
    int error = myCntSocket->error();
       switch(error)
       {
           case QAbstractSocket::RemoteHostClosedError://客户端断开
           {
               QString hostAddress=myCntSocket->QAbstractSocket::peerAddress().toString();
               QMessageBox::information(this, "错误", "远程IP："+hostAddress
                                                      + "\n已断开连接");

                on_cntClosePushButton_clicked();
               break;
           }
           default:
           {
               error = -1;
               QMessageBox::information(this, "show", myCntSocket->errorString());
               break;
           }
       }
 }

