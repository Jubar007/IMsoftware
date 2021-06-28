#ifndef FRIENDGROUP_H
#define FRIENDGROUP_H

#include <QWidget>

namespace Ui {
class friendGroup;
}

class friendGroup : public QWidget
{
    Q_OBJECT

public:
    explicit friendGroup(QWidget *parent = nullptr);
    ~friendGroup();
    void paintEvent(QPaintEvent *);
    void getFriendData(QString,QString,QString);

    void getGroups(QString uid);

protected:
    QString uid;
    QString fid;
    QString fgname;
    int count;
    QList<QStringList> grouplist;
signals:
    void sendData(QString);   //用来传递数据的信号给主窗口
private slots:
    void on_addGPushButton_clicked();

    void on_OKPushButton_clicked();

private:
    Ui::friendGroup *ui;
};

#endif // FRIENDGROUP_H
