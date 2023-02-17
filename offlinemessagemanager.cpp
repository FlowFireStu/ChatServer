#include "offlinemessagemanager.h"
#include <QMessageBox>

OfflineMessageManager* OfflineMessageManager::m_manager = new OfflineMessageManager;

OfflineMessageManager::OfflineMessageManager()
{
}

OfflineMessageManager *OfflineMessageManager::getInstance()
{
    return m_manager;
}

void OfflineMessageManager::init()
{
    m_database = QSqlDatabase::addDatabase("QMYSQL", "offlinemessage");
    m_database.setHostName("localhost");
    m_database.setUserName("root");
    m_database.setPassword("password");

    if (!m_database.open())
    {
        QMessageBox::critical(nullptr, "错误", "数据库打开失败");
        return;
    }
    m_lock.lockForWrite();
    m_database.exec("create database if not exists offlinemessage;");
    m_lock.unlock();
    m_database.close();

    m_database.setDatabaseName("offlinemessage");
}

void OfflineMessageManager::write(const QString &toId, const QJsonObject &message)
{
    m_database.open();
    QSqlQuery query(m_database);

    QString createTable("create table if not exists messageTo" + toId +
                        "(time varchar(20),"
                        "fromId varchar(20),"
                        "toId varchar(20),"
                        "content varchar(1000));");
    m_lock.lockForWrite();
    m_database.exec(createTable);
    m_lock.unlock();

    query.prepare("insert into messageTo" + toId + " values(:time, :fromId, :toId, :content);");
    query.bindValue(":time", message.value("time").toString());
    query.bindValue(":fromId", message.value("fromId").toString());
    query.bindValue(":toId", message.value("toId").toString());
    query.bindValue(":content", message.value("content").toString());
    m_lock.lockForWrite();
    query.exec();
    m_lock.unlock();

    m_database.close();
}

QJsonArray OfflineMessageManager::read(const QString &toId)
{
    m_database.open();
    QSqlQuery query(m_database);

    QString existTable("show tables like messageTo" + toId + ";");
    m_lock.lockForRead();
    query.exec(existTable);
    m_lock.unlock();

    if (query.size() == 0)
    {
        m_database.close();
        return QJsonArray();
    }

    QString readMessage("select * from messageTo" + toId + ";");
    m_lock.lockForRead();
    query.exec(readMessage);
    m_lock.unlock();

    QJsonObject messageBody;
    QJsonArray messageArray;
    while (query.next())
    {
        messageBody.insert("time", query.value(0).toString());
        messageBody.insert("fromId", query.value(1).toString());
        messageBody.insert("toId", query.value(2).toString());
        messageBody.insert("content", query.value(3).toString());
        messageArray.append(messageBody);
    }

    m_database.close();
    return messageArray;
}

void OfflineMessageManager::remove(const QString &toId)
{
    m_database.open();
    m_lock.lockForWrite();
    m_database.exec("drop table if exists messageTo" + toId + ";");
    m_lock.unlock();
    m_database.close();
}
