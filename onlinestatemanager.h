#ifndef ONLINESTATEMANAGER_H
#define ONLINESTATEMANAGER_H

#include <QMap>
#include <QTcpSocket>
#include <QReadWriteLock>

class OnlineStateManager
{
private:
    static OnlineStateManager* m_manager;
    QMap<QString, QAbstractSocket*>* m_onlineState;
    QReadWriteLock m_lock;

    OnlineStateManager();
public:
    OnlineStateManager(const OnlineStateManager&) = delete;
    OnlineStateManager& operator=(const OnlineStateManager&) = delete;
    static OnlineStateManager* getInstance();

    void init();
    void addAccount(const QString& id, QAbstractSocket* socket);
    void deleteAccount(const QString& id);
    bool isOnline(const QString& id);
    QString socketToId(QAbstractSocket* socket);
    QAbstractSocket* findAccount(const QString& id);
};

#endif // ONLINESTATEMANAGER_H
