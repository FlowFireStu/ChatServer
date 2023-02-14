#ifndef ABSTRACTPROCESS_H
#define ABSTRACTPROCESS_H

#include <QAbstractSocket>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

class AbstractProcess
{
protected:
    QAbstractSocket *m_fromSocket;
    QJsonObject *m_head;
    QJsonObject *m_body;

public:
    AbstractProcess(QAbstractSocket* fromSocket);
    virtual ~AbstractProcess();

    virtual bool work(const QJsonObject& request) = 0;
    QAbstractSocket *fromSocket() const;
    QJsonObject* head() const;
    QJsonObject* body() const;
};

#endif // ABSTRACTPROCESS_H
