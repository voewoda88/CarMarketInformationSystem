#include "admin.h"

void admin::setLogin(QString login)
{
    this->login = login;
}

void admin::setPassword(QString password)
{
    this->password = password;
}

QString admin::getLogin()
{
    return login;
}

QString admin::getPassword()
{
    return password;
}

int admin::getId()
{
   return id;
}

void admin::setId(int id)
{
    this->id = id;
}
