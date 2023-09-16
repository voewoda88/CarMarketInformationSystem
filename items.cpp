#include "items.h"

int items::getId()
{
    return id;
}

QString items::getLogin()
{
    return login;
}

QString items::getBrand()
{
    return brand;
}

QString items::getModel()
{
    return model;
}

QString items::getGeneration()
{
    return generation;
}

int items::getYear()
{
    return year;
}

QString items::getEngineVolume()
{
    return engineVolume;
}

QString items::getGearboxType()
{
    return gearboxType;
}

QString items::getBody()
{
    return body;
}

QString items::getEngineType()
{
    return engineType;
}

QString items::getDriveUnit()
{
    return driveUnit;
}

int items::getMileage()
{
    return mileage;
}

int items::getPrice()
{
    return price;
}

QString items::getBooking()
{
    return booking;
}

void items::setId(int id)
{
    this->id = id;
}

void items::setLogin(QString login)
{
    this->login = login;
}

void items::setBrand(QString brand)
{
    this->brand = brand;
}

void items::setModel(QString model)
{
    this->model = model;
}

void items::setGeneration(QString generation)
{
    this->generation = generation;
}

void items::setYear(int year)
{
    this->year = year;
}

void items::setEngineVolume(QString engineVolume)
{
    this->engineVolume = engineVolume;
}

void items::setGearboxType(QString gearboxType)
{
    this->gearboxType = gearboxType;
}

void items::setBody(QString body)
{
    this->body = body;
}

void items::setEngineType(QString engineType)
{
    this->engineType = engineType;
}

void items::setDriveUnit(QString driveUnit)
{
    this->driveUnit = driveUnit;
}

void items::setMileage(int mileage)
{
    this->mileage = mileage;
}

void items::setPrice(int price)
{
    this->price = price;
}

void items::setBooking(QString booking)
{
    this->booking = booking;
}
