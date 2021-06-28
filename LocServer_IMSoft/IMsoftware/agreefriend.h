#ifndef AGREEFRIEND_H
#define AGREEFRIEND_H

#include <QWidget>
#include <QStandardItemModel>

namespace Ui {
class agreeFriend;
}

class agreeFriend : public QWidget
{
    Q_OBJECT

public:
    explicit agreeFriend(QWidget *parent = nullptr);
    ~agreeFriend();
    void paintEvent(QPaintEvent *);
    void getFriendData(QList<QStringList> data,QString id); //在子窗口创建public函数用来获取传递的数据

protected:
    QList<QStringList> newFriendInfo;
    QString uid;
    int s;

private slots:
    void on_listView_clicked(const QModelIndex &index);

    void on_agreePushButton_clicked();

signals:
    void sendData(QString);   //用来传递数据的信号给主窗口
private:
    Ui::agreeFriend *ui;
    QStandardItemModel *m_pModel;
};

#endif // AGREEFRIEND_H
