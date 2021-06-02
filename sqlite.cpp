#include "sqlite.h"

Sqlite::Sqlite(QString m_file_name)
  {

      db_file_name=m_file_name;
      db=QSqlDatabase::addDatabase("QSQLITE");
      query=new QSqlQuery(db);
      db.setDatabaseName(db_file_name);
      if(!db.open())
      {
          qDebug()<<"database open error.";
          error = db.lastError();
      }
  }
int Sqlite::db_query(QString m_query_sql)
 {
     query->prepare(m_query_sql);
    return query->exec();
 }
/*
  *
  * create_table函数：创建数据库表
  * table_name:表名
  * table_data:表项 名->属性
  *
  */

     bool Sqlite::create_table(QString table_name,QMap<QString,QString> table_data)
{
     QSqlQuery query;
     QString sql="create table "+table_name+" (";
     for(QMap<QString,QString>::const_iterator i=table_data.constBegin();i!=table_data.constEnd();i++)
     {
         sql+=i.key()+' '+i.value();
         if(i!=table_data.constEnd())
             sql+=',';
     }
     sql.chop(1);
     sql+=")";
     qDebug()<<sql;
     query.prepare(sql);
     return query.exec();
}

/*
  * 向数据库中增加数据
  */

    int Sqlite::add(QString table_name, QMap<QString, QString> data)
{
     QString sql="insert into "+table_name+  "(";
     QString values=" values(";
     for(QMap<QString,QString>::const_iterator i=data.constBegin();i!=data.constEnd();i++)
     {
         sql+=i.key()+", ";
         values+=i.value()+", ";
     }
     sql.chop(2);
     values.chop(2);
     sql+=")";
     values+=")";
     sql+=values;
     qDebug()<<sql;
     query->prepare(sql);
     return query->exec();
}

/*
  * 向数据库发送一条语句
  */

/*
  * 删除一条记录
  */

   int Sqlite::del(QString table_name, QMap<QString, QString> where)
{
     QString sql="delete ";
     sql+=table_name;
     sql+=" where ";
     for(QMap<QString,QString>::const_iterator i=where.constBegin();i!=where.constEnd();i++)
     {
         sql+=i.key()+"=";
         sql+="'"+i.value()+"' ";
     }
     sql.chop(2);
     query->prepare(sql);
     return query->exec();
}

/*
  * 修改数据库记录
  */
  int Sqlite::updata(QString table_name, QMap<QString, QString> where, QMap<QString, QString> data)
{
     QString sql="updata "+table_name+" set";
     for(QMap<QString,QString>::const_iterator i=where.constBegin();i!=where.constEnd();i++)
     {
         sql+=i.key()+"=";
         sql+=i.value()+" ";
     }
     sql+="where ";
     for(QMap<QString,QString>::const_iterator i=where.constBegin();i!=where.constEnd();i++)
     {
         sql+=i.key()+"=";
         sql+=i.value()+" ";
     }
     return query->exec();
}

/*
  * 查找所有记录
  */

   int Sqlite::find(QString table_name,QList<QString> key,QList<QList<QString>> *row)
   {
     QString sql="select ";
     int len=key.size();
     for(int i=0;i<len;i++)
     {
         sql+=key.at(i);
         sql+=",";
     }
     sql.chop(1);
     sql+=" from "+table_name;
     //qDebug()<<sql;
     query->prepare(sql);
     if(query->exec())
     {
         while (query->next()) {
             QList<QString> j;
             for(int i=0;i<len;i++)
             {
                 j.append(query->value(i).toString());
             }
             row->append(j);
         }
         return 1;
     }
     else return 0;
}

 int Sqlite::find(QString table_name, QList<QString> key, QMap<QString, QString> where, QList<QList<QString> > *row)
{
     QString sql="select ";
     int len=key.size();
     for(int i=0;i<len;i++)
     {
         sql+=key.at(i);
         sql+=",";
     }
     sql.chop(1);
     sql+=" from "+table_name;
     sql+=" where ";
     for(QMap<QString,QString>::const_iterator i=where.constBegin();i!=where.constEnd();i++)
     {
         sql+=i.key()+"="+i.value()+",";
     }
     sql.chop(1);
     //qDebug()<<sql;
     query->prepare(sql);
     if(query->exec())
     {
         while (query->next()) {
             QList<QString> j;
             for(int i=0;i<len;i++)
             {
                 j.append(query->value(i).toString());
             }
             row->append(j);
         }
         return 1;
     }
     else return 0;
}

/*
  * 获取错误信息
  */

QString Sqlite::getError()
{
     return error.text();
}



Sqlite::~Sqlite()
{
     db.close();
}
