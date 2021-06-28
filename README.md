# IMsoftware
软件开发流程课程设计
## 简介
基于Qt的局域网即时通讯
## 环境
  * Window10 Qt5.9
  * UdpSocket
  * TcpSocket
  * QSqlDatabase
  * QPainter

## 文档信息
addnews.cpp 添加好友  
agreefriend.cpp 同意添加好友  
changeremark.cpp 好友备注管理  
filecntdlg.cpp 文件传输接收端  
filesrvdlg.cpp  文件传输发送端  
friendgroup.cpp 群组管理  
logindialog.cpp 注册/登录管理  
mainwindow.cpp 聊天主窗口管理  
perfectpersonaldata.cpp 资料卡片管理  
sqlite.cpp 数据库管理  
  
## 功能及实现：
1. 界面交互：登录/注册窗口、聊天主窗口、文件传输窗口、添加好友窗口
2. 消息收发：定义消息类型，局域网UDP广播，用户ID过滤，实现P2P通信
3. 文件传输：判断是否同意传输，建立TCP连接
4. 用户信息管理：  
本地信息： 存储用户个人信息、资料卡片、好友列表  
服务器信息：存储所有用户信息、用户好友关系、群组关系
5. 数据库管理：
Sqlite数据库，c++调用sql语句管理  
数据库管理接口：增删改查、添加好友、更新好友列表、更新资料卡片
6. 消息提醒、聊天记录清理与下载

## 代码贡献
杨磊：消息收发、文件传输、本地服务器信息传递  
吴：
