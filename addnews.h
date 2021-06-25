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
<<<<<<< Updated upstream
=======
     void paintEvent(QPaintEvent *);
>>>>>>> Stashed changes

    void sendData(QList<QStringList> data); //在子窗口创建public函数用来获取传递的数据

private slots:
    void on_searchPushButton_clicked();

    void on_sendPushButton_clicked();

private:
    Ui::addNews *ui;
};

#endif // ADDNEWS_H
