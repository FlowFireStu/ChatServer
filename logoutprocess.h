#ifndef LOGOUTPROCESS_H
#define LOGOUTPROCESS_H

#include "abstractprocess.h"

class LogoutProcess: public AbstractProcess
{
public:
    using AbstractProcess::AbstractProcess;

    bool work(const QJsonObject& request);
};

#endif // LOGOUTPROCESS_H
