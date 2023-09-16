#ifndef CHECKINT_H
#define CHECKINT_H
#include <QString>
#include <QDebug>
#include "exception.h"
#include <QMessageBox>

class checkInt
{
public:
    checkInt(){};
    bool inputYear(int);
    bool inputMileage(int);
    bool inputPrice(int);
private:
    void checkYear(int);
    void checkMileage(int);
    void checkPrice(int);
};

#endif // CHECKINT_H
