#include "onlinestatemanager.h"

OnlineStateManager* OnlineStateManager::m_manager = new OnlineStateManager();

OnlineStateManager::OnlineStateManager()
{
    m_onlineState = nullptr;
    init();
}

OnlineStateManager *OnlineStateManager::getInstance()
{
    return m_manager;
}

void OnlineStateManager::init()
{
    if (m_onlineState)
    {
        m_lock.lockForWrite();
        m_onlineState->clear();
        m_lock.unlock();
    }
    else
        m_onlineState = new QMap<QString, QAbstractSocket*>;
}

void OnlineStateManager::addAccount(const QString &id, QAbstractSocket *socket)
{
    m_lock.lockForWrite();
    m_onlineState->insert(id, socket);
    m_lock.unlock();
}

void OnlineStateManager::deleteAccount(const QString &id)
{
    m_lock.lockForWrite();
    m_onlineState->remove(id);
    m_lock.unlock();
}

bool OnlineStateManager::isOnline(const QString &id)
{
    m_lock.lockForRead();
    bool state = m_onlineState->contains(id);
    m_lock.unlock();
    return state;
}

QString OnlineStateManager::socketToId(QAbstractSocket *socket)
{

    m_lock.lockForRead();
    QString id = m_onlineState->key(socket, "null");
    m_lock.unlock();
    return id;
}

QAbstractSocket *OnlineStateManager::findAccount(const QString &id)
{
    m_lock.lockForRead();
    QAbstractSocket* socket = m_onlineState->value(id, nullptr);
    m_lock.unlock();
    return socket;
}
