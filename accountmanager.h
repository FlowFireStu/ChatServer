#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QReadWriteLock>
#include "account.h"

class AccountManager
{
private:
    static AccountManager* m_accountManager;
    QSqlDatabase m_database;
    QReadWriteLock m_lock;

    AccountManager();

public:
    AccountManager(const AccountManager&) = delete;
    AccountManager& operator=(const AccountManager&) = delete;
    static AccountManager* getInstance();

    void init();
    QString addAccount(const Account &newAccount);
    bool existAccount(const QString &id);
    Account findAccount(const QString &id);
    void addFriend(const QString &selfId, const QString &friendId);
    void deleteFriend(const QString &selfId, const QString &friendId);
    QList<QString> listFriend(const QString& id);
};

#endif // ACCOUNTMANAGER_H
