#ifndef ADDNEWS_H
#define ADDNEWS_H

#include <QWidget>

namespace Ui {
class addNews;
}

class addNews : public QWidget
{
    Q_OBJECT

    QList<QStringList> myInfo;
    QString uid;
public:
    explicit addNews(QWidget *parent = nullptr);
    ~addNews();

    void sendData(QList<QStringList> data); //在子窗口创建public函数用来获取传递的数据

private slots:
    void on_searchPushButton_clicked();

    void on_sendPushButton_clicked();

private:
    Ui::addNews *ui;
signals:
    void sendFriAdd(QString);
};

#endif // ADDNEWS_H
