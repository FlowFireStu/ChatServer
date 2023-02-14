#ifndef LOGINPROCESS_H
#define LOGINPROCESS_H

#include "abstractprocess.h"

class LoginProcess: public AbstractProcess
{
public:
    using AbstractProcess::AbstractProcess;

    bool work(const QJsonObject& request);
};

#endif // LOGINPROCESS_H
