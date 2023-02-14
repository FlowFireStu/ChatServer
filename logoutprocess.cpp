#include "logoutprocess.h"
#include "onlinestatemanager.h"

bool LogoutProcess::work(const QJsonObject &request)
{
    QString id = request.value("id").toString();
    OnlineStateManager::getInstance()->deleteAccount(id);

    return false;
}
