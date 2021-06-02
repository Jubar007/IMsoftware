#ifndef SQLITE_H
#define SQLITE_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QMap>
#include <QInternal>
#include <QString>
#include <QDebug>

class Sqlite
{
    QSqlDatabase db;
    QString db_file_name;   //数据库文件名
    QSqlError error;
    QSqlQuery *query;
    QSqlRecord rec;
public:
    Sqlite(QString m_file_name);
    ~Sqlite();
    bool create_table(QString table_name,QMap<QString,QString> table_data);   //新建表
    int db_query(QString m_query_sql); //发送数据库语句
    int add(QString table_name,QMap<QString,QString> data); //增加数据
    int del(QString table_name,QMap<QString,QString> where); //删除一条记录
    int updata(QString table_name,QMap<QString,QString> where,QMap<QString,QString> data);  //更新数据
    int find(QString table_name,QList<QString> key,QMap<QString,QString> where,QList<QList<QString>> *row);    //查找
    int find(QString table_name,QList<QString> key,QList<QList<QString>> *row);    //查找所有
    QString getError();
};

#endif // SQLITE_H
