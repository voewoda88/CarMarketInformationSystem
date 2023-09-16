#include "user.h"

void user::setLogin(QString login)
{
    this->login = login;
}

void user::setPassword(QString password)
{
    this->password = password;
}

QString user::getLogin()
{
    return login;
}

QString user::getPassword()
{
    return password;
}

int user::getId()
{
   return id;
}

void user::setId(int id)
{
    this->id = id;
}
