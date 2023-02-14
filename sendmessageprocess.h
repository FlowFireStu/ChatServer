#ifndef SENDMESSAGEPROCESS_H
#define SENDMESSAGEPROCESS_H

#include "abstractprocess.h"

class SendMessageProcess: public AbstractProcess
{
public:
    using AbstractProcess::AbstractProcess;

    bool work(const QJsonObject& request);
};

#endif // MESSAGEPROCESS_H
