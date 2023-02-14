#ifndef ADDFRIENDPROCESS_H
#define ADDFRIENDPROCESS_H

#include "abstractprocess.h"

class AddFriendProcess: public AbstractProcess
{
public:
    using AbstractProcess::AbstractProcess;

    bool work(const QJsonObject& request);
};

#endif // ADDFRIENDPROCESS_H
