#include "workthread.h"
#include <QMessageBox>
#include <QDebug>
#include "abstractprocess.h"
#include "processfactory.h"
#include "onlinestatemanager.h"

WorkThread::WorkThread(QTcpSocket* socket, QObject *parent)
    : QThread{parent}
{
    m_socket = socket;
}

WorkThread::~WorkThread()
{
}

void WorkThread::run()
{
    connect(m_socket, &QTcpSocket::readyRead, this, &WorkThread::processRequest);
    connect(m_socket, &QTcpSocket::disconnected, this, [=](){
        logoutAccount();
        m_socket->close();
        m_socket->deleteLater();
        emit workFinished();
    });

    exec();
}

void WorkThread::processRequest()
{
    QByteArray request = m_socket->readAll();
    QJsonArray requestArray = QJsonDocument::fromJson(request).array();
    QJsonObject requestHead = requestArray[0].toObject();
    QJsonObject requestBody = requestArray[1].toObject();

    AbstractProcess* process = ProcessFactory(m_socket).createProcess(requestHead);
    bool needRes = process->work(requestBody);
    if (!needRes)
    {
        delete process;
        return;
    }

    QJsonObject* responseHead = process->head();
    QJsonObject* responseBody = process->body();
    QJsonArray responseArray;
    responseArray.append(*responseHead);
    responseArray.append(*responseBody);

    QByteArray response = QJsonDocument(responseArray).toJson();
    m_socket->write(response);
    delete process;
    delete responseHead;
    delete responseBody;
}

void WorkThread::logoutAccount()
{
    OnlineStateManager* manager = OnlineStateManager::getInstance();
    QString id = manager->socketToId(m_socket);
    if (id != QString("null"))
    {
        manager->deleteAccount(id);
    }
}
