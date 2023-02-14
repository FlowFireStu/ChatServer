#include "processfactory.h"
#include "createaccountprocess.h"
#include "loginprocess.h"
#include "logoutprocess.h"
#include "sendmessageprocess.h"
#include "getofflinemessageprocess.h"
#include "addfriendprocess.h"
#include <QDebug>

ProcessFactory::ProcessFactory(QAbstractSocket* fromSocket)
{
    m_fromSocket = fromSocket;
}

AbstractProcess *ProcessFactory::createProcess(const QJsonObject& type)
{
    QString firstType = type.value("type").toString();
    if (firstType == "request")
    {
        QString requestType = type.value("requestType").toString();
        return createRequestProcess(requestType);
    }
    return nullptr;
}

AbstractProcess* ProcessFactory::createRequestProcess(const QString &requestType)
{

    if (requestType == "CreateAccount") {
        return new CreateAccountProcess(m_fromSocket);
    }
    else if (requestType == "LoginAccount") {
        return new LoginProcess(m_fromSocket);
    }
    else if (requestType == "LogoutAccount") {
        return new LogoutProcess(m_fromSocket);
    }
    else if (requestType == "AddFriend") {
        return new AddFriendProcess(m_fromSocket);
    }
    else if (requestType == "SendMessage") {
        return new SendMessageProcess(m_fromSocket);
    }
    else if (requestType == "GetOfflineMessage") {
        return new GetOfflineMessageProcess(m_fromSocket);
    }
    return nullptr;
}
