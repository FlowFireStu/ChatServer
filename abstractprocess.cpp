#include "abstractprocess.h"

AbstractProcess::AbstractProcess(QAbstractSocket* fromSocket)
{
    m_fromSocket = fromSocket;
    m_head = nullptr;
    m_body = nullptr;
}

AbstractProcess::~AbstractProcess()
{

}

QAbstractSocket *AbstractProcess::fromSocket() const
{
    return m_fromSocket;
}

QJsonObject* AbstractProcess::head() const
{
    return m_head;
}

QJsonObject* AbstractProcess::body() const
{
    return m_body;
}
