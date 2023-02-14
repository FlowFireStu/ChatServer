#include "createaccountprocess.h"
#include <QRandomGenerator>
#include "accountmanager.h"
#include <QDebug>

bool CreateAccountProcess::work(const QJsonObject &request)
{
    AccountManager* manager = AccountManager::getInstance();
    int id = 10000 + QRandomGenerator::global()->bounded(0, 9999);
    while (manager->existAccount(QString::number(id)))
        id = 10000 + QRandomGenerator::global()->bounded(0, 9999);

    QString password = request.value("password").toString();
    QString nickname = request.value("nickname").toString();
    Account newAccount(QString::number(id), password, nickname);
    manager->addAccount(newAccount);

    m_head = new QJsonObject;
    m_head->insert("type", "response");
    m_head->insert("responseType", "CreateAccount");
    m_head->insert("success", true);
    m_body = new QJsonObject;
    m_body->insert("id", QString::number(id));

    return true;
}
