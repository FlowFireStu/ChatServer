#include "accountmanager.h"
#include <QMessageBox>

AccountManager* AccountManager::m_accountManager = new AccountManager();

AccountManager *AccountManager::getInstance()
{
    return m_accountManager;
}

AccountManager::AccountManager()
{
    init();
}

void AccountManager::init()
{
    m_database = QSqlDatabase::addDatabase("QMYSQL", "account");
    m_database.setHostName("localhost");
    m_database.setUserName("root");
    m_database.setPassword("password");

    if (!m_database.open())
    {
        QMessageBox::critical(nullptr, "错误", "数据库打开失败");
        return;
    }
    m_lock.lockForWrite();
    m_database.exec("create database if not exists account;");
    m_lock.unlock();
    m_database.close();

    m_database.setDatabaseName("account");
    if (!m_database.open())
    {
        QMessageBox::critical(nullptr, "错误", "数据库打开失败");
        return;
    }
    QString createTableComd("create table if not exists accounttable("
                            "id varchar(20) primary key,"
                            "password varchar(20),"
                            "nickname varchar(20),"
                            "gender varchar(5));");
    m_lock.lockForWrite();
    m_database.exec(createTableComd);
    m_lock.unlock();
    m_database.close();
}

QString AccountManager::addAccount(const Account &newAccount)
{
    QString addAccount("insert into accounttable values("
                    + newAccount.id() + ", \""
                    + newAccount.password() + "\", \""
                    + newAccount.name() + "\", \""
                    + newAccount.gender() + "\");");
    QString addFriendTable("create table if not exists "
                               + newAccount.id() +
                               "friendlist(id varchar(20) primary key);");
    m_database.open();
    m_lock.lockForWrite();
    m_database.exec(addAccount);
    m_database.exec(addFriendTable);
    m_lock.unlock();
    m_database.close();
    return newAccount.id();
}

bool AccountManager::existAccount(const QString &id)
{
    QString command("select * from accounttable where id = \"" + id + "\";");
    m_database.open();
    QSqlQuery query(m_database);
    m_lock.lockForRead();
    query.exec(command);
    m_lock.unlock();
    m_database.close();
    return query.size();
}

Account AccountManager::findAccount(const QString &id)
{
    QString command("select * from accounttable where id = \"" + id + "\";");
    m_database.open();
    QSqlQuery query(m_database);
    m_lock.lockForRead();
    query.exec(command);
    m_lock.unlock();
    m_database.close();

    Account tempAccount;
    query.next();
    tempAccount.setId(query.value(0).toString());
    tempAccount.setPassword(query.value(1).toString());
    tempAccount.setName(query.value(2).toString());
    tempAccount.setGender(query.value(3).toString());
    return tempAccount;
}

void AccountManager::addFriend(const QString &selfId, const QString &friendId)
{
    QString command("select * from " + selfId + "friendlist where id = \"" + friendId + "\";");
    m_database.open();
    QSqlQuery query(m_database);
    m_lock.lockForRead();
    query.exec(command);
    m_lock.unlock();

    if (query.size() != 0)
    {
        m_database.close();
        return;
    }

    command.clear();
    command = "insert into " + selfId + "friendlist(id) values(\"" + friendId + "\");";
    m_lock.lockForWrite();
    query.exec(command);
    m_lock.unlock();

    command.clear();
    command = "insert into " + friendId + "friendlist(id) values(\"" + selfId + "\");";
    m_lock.lockForWrite();
    query.exec(command);
    m_lock.unlock();

    m_database.close();
}

void AccountManager::deleteFriend(const QString &selfId, const QString &friendId)
{
    QString command("delete from " + selfId + "friendlist where id = \"" + friendId + "\");");
    m_database.open();
    QSqlQuery query(m_database);
    m_lock.lockForWrite();
    query.exec(command);
    m_lock.unlock();

    command.clear();
    command = "delete from " + friendId + "friendlist where id = \"" + selfId + "\");";
    m_lock.lockForWrite();
    query.exec(command);
    m_lock.unlock();

    m_database.close();
}

QList<QString> AccountManager::listFriend(const QString &id)
{
    QList<QString> list;

    QString command("select id from " + id + "friendlist;");
    m_database.open();
    QSqlQuery query(m_database);
    m_lock.lockForRead();
    query.exec(command);
    m_lock.unlock();
    m_database.close();

    while (query.next())
    {
        list << query.value(0).toString();
    }
    return list;
}
