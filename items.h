#ifndef ITEMS_H
#define ITEMS_H
#include <QString>


class items
{
public:

    int getId();
    QString getLogin();
    QString getBrand();
    QString getModel();
    QString getGeneration();
    int getYear();
    QString getEngineVolume();
    QString getGearboxType();
    QString getBody();
    QString getEngineType();
    QString getDriveUnit();
    int getMileage();
    int getPrice();
    QString getBooking();
    void setId(int);
    void setLogin(QString);
    void setBrand(QString);
    void setModel(QString);
    void setGeneration(QString);
    void setYear(int);
    void setEngineVolume(QString);
    void setGearboxType(QString);
    void setBody(QString);
    void setEngineType(QString);
    void setDriveUnit(QString);
    void setMileage(int);
    void setPrice(int);
    void setBooking(QString booking = "Не забронировано");

private:
    int id;
    QString login;
    QString brand;
    QString model;
    QString generation;
    int year;
    QString engineVolume;
    QString gearboxType;
    QString body;
    QString engineType;
    QString driveUnit;
    int mileage;
    int price;
    QString booking;
};

#endif // ITEMS_H
