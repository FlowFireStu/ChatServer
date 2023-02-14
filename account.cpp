#include "account.h"

const QString &Account::id() const
{
    return m_id;
}

void Account::setId(QString newId)
{
    m_id = newId;
}

const QString &Account::password() const
{
    return m_password;
}

void Account::setPassword(const QString &newPassword)
{
    m_password = newPassword;
}

const QString &Account::name() const
{
    return m_name;
}

void Account::setName(const QString &newName)
{
    m_name = newName;
}

const QString &Account::gender() const
{
    return m_gender;
}

void Account::setGender(const QString &newGender)
{
    m_gender = newGender;
}

Account::Account()
{

}

Account::Account(QString id, QString password, QString nickname)
{
    m_id = id;
    m_password = password;
    m_name = nickname;
    m_gender = "男";
}
