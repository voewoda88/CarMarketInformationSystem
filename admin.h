#ifndef ADMIN_H
#define ADMIN_H
#include <QString>

class admin
{
public:
    void setLogin(QString);
    void setPassword(QString);
    QString getLogin();
    QString getPassword();
    int getId();
    void setId(int id);

private:
    QString login;
    QString password;
    int id;
};

#endif // ADMIN_H
