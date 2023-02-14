#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>

class Account
{
    QString m_id;
    QString m_password;
    QString m_name;
    QString m_gender;

public:
    Account();
    Account(QString id, QString password, QString nickname);
    const QString &id() const;
    void setId(QString newId);
    const QString &password() const;
    void setPassword(const QString &newPassword);
    const QString &name() const;
    void setName(const QString &newName);
    const QString &gender() const;
    void setGender(const QString &newGender);
};

#endif // ACCOUNT_H
