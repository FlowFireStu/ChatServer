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
    QString createTable("create table if not exists " + toId + "(message varchar(5000));");
    QString messageStr = QJsonDocument(message).toVariant().toString();
    QString writeMessage("insert into " + toId + "(message) values(\"" + messageStr + "\");");
    m_database.open();
    m_lock.lockForWrite();
    m_database.exec(createTable);
    m_database.exec(writeMessage);
    m_lock.unlock();
    m_database.close();
}

QJsonArray OfflineMessageManager::read(const QString &toId)
{
    QString existTable("show tables like \"" + toId + "\";");
    m_database.open();
    QSqlQuery query(m_database);
    m_lock.lockForRead();
    query.exec(existTable);
    m_lock.unlock();
    if (query.size() == 0)
    {
        m_database.close();
        return QJsonArray();
    }

    QString readMessage("select message from " + toId + ";");
    m_lock.lockForRead();
    query.exec(readMessage);
    m_lock.unlock();
    m_database.close();

    QJsonObject messageObject;
    QJsonArray messageArray;
    while (query.next())
    {
        messageObject = query.value(0).toJsonObject();
        messageArray.append(messageObject);
    }
    return messageArray;
}

void OfflineMessageManager::remove(const QString &toId)
{
    QString removeTable("drop table if exists " + toId + ";");
    m_database.open();
    m_lock.lockForWrite();
    m_database.exec(removeTable);
    m_lock.unlock();
    m_database.close();
}
