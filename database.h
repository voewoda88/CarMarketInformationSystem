#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>
#include <QList>
#include "admin.h"
#include "user.h"
#include "items.h"
#include "exception.h"
#include "list.h"
#include "list.cpp"

#define TABLE_USERS                "users"
#define TABLE_ADMINS               "admins"
#define TABLE_ITEMS                "items"
#define DATABASE_HOSTNAME          "DataBase"
#define DATABASE_NAME              "tables.db"

#define TABLE_LOGIN                "Login"
#define TABLE_PASSWORD             "Password"

#define ITEM_BRAND                 "Марка"
#define ITEM_MODEL                 "Модель"
#define ITEM_GENERATION            "Поколение"
#define ITEM_YEAR                  "Годвыпуска"
#define ITEM_ENGINEVOLUME          "ОбъемДвигателя"
#define ITEM_GEARBOXTYPE           "ТипКПП"
#define ITEM_BODY                  "Кузов"
#define ITEM_ENGINETYPE            "ТипДвигателя"
#define ITEM_DRIVEUNIT             "Привод"
#define ITEM_MILEAGE               "Пробег"
#define ITEM_PRICE                 "Цена"
#define ITEM_BOOKING               "Бронь"


class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = 0);
    ~DataBase();

    void connectToDataBase();
    bool inserIntoTable(QString login, QString password);
    void closeDataBase();
    List<user> getUserFromTable();
    List<admin> getAdminFromTable();
    bool checkRegWindow(QString);
    List<items> getItemsFromTable(QString, QString);
    bool insertItemsIntoTable(items item, QString);
    bool deleteItem(int id);
    bool getItemFromTable(items*, int);
    bool updateItem(items);
    bool updateBooking(int);
    bool sortColumns(int);
    bool deleteTableItems();
    bool getLoginFromTable(QString&, int);

private:
    bool openDataBase();
    bool restoreDataBase();
    bool createTable();
    void DataBaseOpen();
    QSqlQuery createQuary(int);
    QSqlQuery createSearchQuary(QString currentText, QString text);

private:
    QSqlDatabase db;
};

#endif // DATABASE_H
