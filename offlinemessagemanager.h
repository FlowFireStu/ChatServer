#ifndef OFFLINEMESSAGEMANAGER_H
#define OFFLINEMESSAGEMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QReadWriteLock>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

class OfflineMessageManager
{
private:
    static OfflineMessageManager* m_manager;
    QSqlDatabase m_database;
    QReadWriteLock m_lock;

    OfflineMessageManager();
public:
    OfflineMessageManager(const OfflineMessageManager&) = delete;
    OfflineMessageManager& operator=(const OfflineMessageManager&) = delete;
    static OfflineMessageManager* getInstance();

    void init();
    void write(const QString& toId, const QJsonObject& message);
    QJsonArray read(const QString& toId);
    void remove(const QString& toId);
};

#endif // OFFLINEMESSAGEMANAGER_H
