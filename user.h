#ifndef USER_H
#define USER_H
#include "QString"
#include <QList>

class user
{
public:
    void setLogin(QString);
    void setPassword(QString);
    QString getLogin();
    QString getPassword();
    int getId();
    void setId(int id);

private:
    int id;
    QString login;
    QString password;
};

#endif // USER_H
