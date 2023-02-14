#include "loginprocess.h"
#include "accountmanager.h"
#include "onlinestatemanager.h"

bool LoginProcess::work(const QJsonObject &request)
{
    AccountManager* manager = AccountManager::getInstance();
    m_head = new QJsonObject;
    m_body = new QJsonObject;
    m_head->insert("type", "response");
    m_head->insert("responseType", "LoginAccount");

    QString id = request.value("id").toString();
    if (!manager->existAccount(id))
    {
        m_head->insert("success", false);
        m_body->insert("content", "账号不存在");
        return true;
    }

    QString password = request.value("password").toString();
    Account account = manager->findAccount(id);
    if (password != account.password())
    {
        m_head->insert("success", false);
        m_body->insert("content", "密码错误");
        return true;
    }

    OnlineStateManager::getInstance()->addAccount(id, m_fromSocket);
    QList<QString> friendList = manager->listFriend(id);
    int friendCount = friendList.size();
    QJsonArray friendArray;
    for (int i = 0; i < friendCount; i++)
    {
        QString friendId = friendList.at(i);
        Account friendAccount = manager->findAccount(friendId);
        QJsonObject friendObject;
        friendObject.insert("id", friendAccount.id());
        friendObject.insert("name", friendAccount.name());
        friendObject.insert("gender", friendAccount.gender());
        friendArray.append(friendObject);
    }

    m_head->insert("success", true);
    m_body->insert("id", id);
    m_body->insert("name", account.name());
    m_body->insert("friend", friendArray);
    return true;
}
