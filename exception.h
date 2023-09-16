#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <QString>
#include <QDebug>

class Exception
{
public:
    Exception(QString message)
    {
        this->message = message;
    }

    QString what()
    {
        return message;
    }

    QString GetErrorCode()
    {
        return errorCode;
    }

    void SetErrorCode(QString errorCode)
    {
        this->errorCode = errorCode;
    }

private:
    QString errorCode;
    QString message;
};

class ArgumentException : public Exception
{
private:
    QString errorCode = "C0001";
public:
    ArgumentException(QString msg) : Exception(msg)
    {
        Exception::SetErrorCode(errorCode);
    }

};

class DataBaseException : public Exception
{
private:
    QString errorCode = "C0002";
public:
    DataBaseException(QString msg) : Exception(msg)
    {
        Exception::SetErrorCode(errorCode);
    }

};

class MemoryException : public Exception
{
private:
    QString errorCode = "C0003";
public:
    MemoryException(QString msg) : Exception(msg)
    {
        Exception::SetErrorCode(errorCode);
    }

};

class IndexException : public Exception
{
private:
    QString errorCode = "C0004";
public:
    IndexException(QString msg) : Exception(msg)
    {
        Exception::SetErrorCode(errorCode);
    }

};

class EmptyListException : public Exception
{
private:
    QString errorCode = "C0005";
public:
    EmptyListException(QString msg) : Exception(msg)
    {
        Exception::SetErrorCode(errorCode);
    }

};


#endif  // EXCEPTION_H
