#ifndef CREATEACCOUNTPROCESS_H
#define CREATEACCOUNTPROCESS_H

#include "abstractprocess.h"

class CreateAccountProcess: public AbstractProcess
{
public:
    using AbstractProcess::AbstractProcess;

    bool work(const QJsonObject& request);
};

#endif // CREATEACCOUNTPROCESS_H
