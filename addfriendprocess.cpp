#include "addfriendprocess.h"
#include "accountmanager.h"

bool AddFriendProcess::work(const QJsonObject &request)
{
    AccountManager* manager = AccountManager::getInstance();
    QString selfId = request.value("selfId").toString();
    QString friendId = request.value("friendId").toString();
    m_head = new QJsonObject;
    m_body = new QJsonObject;
    m_head->insert("type", "response");
    m_head->insert("responseType", "AddFriend");

    if (!manager->existAccount(friendId))
    {
        m_head->insert("success", false);
        m_body->insert("content", "账号不存在");
    }
    else
    {
        manager->addFriend(selfId, friendId);
        Account friendAccount = manager->findAccount(friendId);
        m_head->insert("success", true);
        m_body->insert("id", friendId);
        m_body->insert("name", friendAccount.name());
        m_body->insert("gender", friendAccount.gender());
    }

    return true;
}
