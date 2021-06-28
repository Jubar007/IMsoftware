#ifndef CHANGEREMARK_H
#define CHANGEREMARK_H

#include <QWidget>

namespace Ui {
class changeRemark;
}

class changeRemark : public QWidget
{
    Q_OBJECT

public:
    explicit changeRemark(QWidget *parent = nullptr);
    ~changeRemark();
    void paintEvent(QPaintEvent *);
    void getFriendData(QString,QString,QString);

protected:
    QString uid;
    QString fid;
    QString fname;

private slots:
    void on_OKPushButton_clicked();
signals:
    void sendData(QString);   //用来传递数据的信号给主窗口
private:
    Ui::changeRemark *ui;
};

#endif // CHANGEREMARK_H
