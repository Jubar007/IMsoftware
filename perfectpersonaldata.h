#ifndef PERFECTPERSONALDATA_H
#define PERFECTPERSONALDATA_H

#include <QWidget>

namespace Ui {
class perfectPersonalData;
}

class perfectPersonalData : public QWidget
{
    Q_OBJECT

public:
    explicit perfectPersonalData(QWidget *parent = nullptr);
    ~perfectPersonalData();
    void paintEvent(QPaintEvent *);
    QString userid;//当前用户ID
    QStringList manData;//存储用户更新的数据
public:
    void getUersData(QStringList data); //获取从主窗口传递过来的用户数据
private slots:
    void on_closePushButton_clicked();

    void on_savePushButton_clicked();

signals:
    void sendData(QStringList);   //用来传递数据的信号给主窗口
private:
    Ui::perfectPersonalData *ui;
};

#endif // PERFECTPERSONALDATA_H
