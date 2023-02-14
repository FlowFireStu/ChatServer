#include "getofflinemessageprocess.h"
#include "offlinemessagemanager.h"

bool GetOfflineMessageProcess::work(const QJsonObject &request)
{
    QString id = request.value("id").toString();
    OfflineMessageManager* manager = OfflineMessageManager::getInstance();
    QJsonArray messageArray = manager->read(id);

    m_head = new QJsonObject;
    m_body = new QJsonObject;
    m_head->insert("type", "response");
    m_head->insert("responseType", "GetOfflineMessage");
    m_head->insert("success", true);
    m_body->insert("offlineMessage", messageArray);

    return true;
}
