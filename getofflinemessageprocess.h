#ifndef GETOFFLINEMESSAGEPROCESS_H
#define GETOFFLINEMESSAGEPROCESS_H

#include "abstractprocess.h"

class GetOfflineMessageProcess: public AbstractProcess
{
public:
    using AbstractProcess::AbstractProcess;

    bool work(const QJsonObject& request);
};


#endif // GETOFFLINEMESSAGEPROCESS_H
