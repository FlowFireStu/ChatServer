# 聊天软件服务端

## 简介

聊天软件服务端

![ChatServer](https://github.com/FlowFireStu/Picture/blob/main/ChatServer/ChatServer.png)

## 功能

目前支持功能；登录、注册、添加好友、在线消息转发、离线消息保存

## 相关配置

MySQL数据库默认地址localhost
> accountmanager文件配置
```c++
m_database = QSqlDatabase::addDatabase("QMYSQL", "account");
m_database.setHostName("localhost");
m_database.setUserName("root");
m_database.setPassword("password");
```
