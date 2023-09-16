#include "checkint.h"

bool checkInt::inputYear(int num)
{
    try
    {
        checkYear(num);
    }
    catch(ArgumentException ex)
    {
        qDebug() << "Error message: " << ex.what();
        qDebug() << "Error code: " << ex.GetErrorCode();
        return false;
    }
    return true;
}

bool checkInt::inputMileage(int num)
{
    try
    {
        checkMileage(num);
    }
    catch(ArgumentException ex)
    {
        qDebug() << "Error message: " << ex.what();
        qDebug() << "Error code: " << ex.GetErrorCode();
        return false;
    }
    return true;
}

bool checkInt::inputPrice(int num)
{
    try
    {
        checkPrice(num);
    }
    catch(ArgumentException ex)
    {
        qDebug() << "Error message: " << ex.what();
        qDebug() << "Error code: " << ex.GetErrorCode();
        return false;
    }
    return true;
}

void checkInt::checkYear(int num)
{
    if(num == 0)
        throw ArgumentException("parameter is not integer.");
    if(num == INT_MAX)
        throw ArgumentException("parametr is overflow");
    if(num < 1900 || num > 2022)
        throw ArgumentException("parameter out of range.");
}

void checkInt::checkMileage(int num)
{
    if(num == 0)
        throw ArgumentException("parameter is not integer.");
    if(num == INT_MAX)
        throw ArgumentException("parametr is overflow");
    if(num < 1 || num > 1500000)
        throw ArgumentException("parameter out of range.");
}

void checkInt::checkPrice(int num)
{
    if(num == 0)
        throw ArgumentException("parameter is not integer.");
    if(num == INT_MAX)
        throw ArgumentException("parametr is overflow");
    if(num < 1 || num > 1000000)
        throw ArgumentException("parameter out of range.");
}
