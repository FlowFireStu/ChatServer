#ifndef PROCESSFACTORY_H
#define PROCESSFACTORY_H

#include "abstractprocess.h"

class ProcessFactory
{
    QAbstractSocket* m_fromSocket;
public:
    ProcessFactory(QAbstractSocket* fromSocket);

    AbstractProcess* createProcess(const QJsonObject& type);
private:
    AbstractProcess* createRequestProcess(const QString& requestType);
    AbstractProcess* createResponseProcess(const QString& requestType);
};

#endif // PROCESSFACTORY_H
