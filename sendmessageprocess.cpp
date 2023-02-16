#include "sendmessageprocess.h"
#include "onlinestatemanager.h"
#include "offlinemessagemanager.h"

bool SendMessageProcess::work(const QJsonObject &request)
{
    QString toId = request.value("toId").toString();
    OnlineStateManager* stateManager = OnlineStateManager::getInstance();
    if (stateManager->isOnline(toId))
    {
        QJsonObject head;
        head.insert("type", "request");
        head.insert("requestType", "Message");
        QJsonArray responseArray;
        responseArray.append(head);
        responseArray.append(request);

        QByteArray response = QJsonDocument(responseArray).toJson();
        stateManager->findAccount(toId)->write(response);
    }
    else
    {
        OfflineMessageManager* messageManager = OfflineMessageManager::getInstance();
        messageManager->write(toId, request);
    }

    return false;
}
