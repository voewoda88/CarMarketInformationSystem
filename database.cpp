#include "database.h"

DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

DataBase::~DataBase()
{

}

void DataBase::connectToDataBase()
{
    /* Перед подключением к базе данных производим проверку на её существование.
     * В зависимости от результата производим открытие базы данных или её восстановление
     * */
    if(!QFile("D:/QtProjects/autorinok/" DATABASE_NAME).exists())
    {
        this->restoreDataBase();
    }
    else
    {
        this->openDataBase();
    }
}

bool DataBase::restoreDataBase()
{
    // Если база данных открылась ...
    if(this->openDataBase()){
        // Производим восстановление базы данных
        return (this->createTable()) ? true : false;
    } else {
        qDebug() << "Не удалось восстановить базу данных";
        return false;
    }
    return false;
}

bool DataBase::openDataBase()
{
    /* База данных открывается по заданному пути
     * и имени базы данных, если она существует
     * */
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName("D:/QtProjects/autorinok/" DATABASE_NAME);
    try
    {
        DataBaseOpen();
    }
    catch(DataBaseException ex)
    {
        qDebug() << ex.what();
        qDebug() << ex.GetErrorCode();
        return false;
    }
    return true;
}

bool DataBase::createTable()
{
    /* В данном случае используется формирование сырого SQL-запроса
     * с последующим его выполнением.
     * */
    QSqlQuery query;
    if(!query.exec( "CREATE TABLE " TABLE_USERS " ("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                            TABLE_LOGIN     " VARCHAR(30),"
                            TABLE_PASSWORD  " VARCHAR(30));"

                    ))
    {
        qDebug() << "DataBase: error of create " << TABLE_USERS;
        qDebug() << query.lastError().text();
        return false;
    }
    else if(!query.exec( "CREATE TABLE " TABLE_ADMINS " ("
                         "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                         TABLE_LOGIN     " VARCHAR(30),"
                         TABLE_PASSWORD  " VARCHAR(30));"

                 ))
    {
        qDebug() << "DataBase: error of create " << TABLE_ADMINS;
        qDebug() << query.lastError().text();
        return false;
    }
    else if(!query.exec( "CREATE TABLE " TABLE_ITEMS " ("
                         "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                         TABLE_LOGIN        " VARCHAR(30),"
                         ITEM_BRAND         " VARCHAR(30),"
                         ITEM_MODEL         " VARCHAR(30),"
                         ITEM_GENERATION    " VARCHAR(30),"
                         ITEM_YEAR          " INTEGER,"
                         ITEM_ENGINEVOLUME  " VARCHAR(30),"
                         ITEM_GEARBOXTYPE   " VARCHAR(30),"
                         ITEM_BODY          " VARCHAR(30),"
                         ITEM_ENGINETYPE    " VARCHAR(30),"
                         ITEM_DRIVEUNIT     " VARCHAR(30),"
                         ITEM_MILEAGE       " INTEGER,"
                         ITEM_PRICE         " INTEGER,"
                         ITEM_BOOKING       " VARCHAR(30));"
                 ))
    {
        qDebug() << "DataBase: error of create " << TABLE_ITEMS;
        qDebug() << query.lastError().text();
        return false;
    }
    else
        return true;
}



bool DataBase::inserIntoTable(QString login, QString password)
{
    /* Запрос SQL формируется из QVariantList,
     * в который передаются данные для вставки в таблицу.
     * */
    QSqlQuery query;
    /* В начале SQL запрос формируется с ключами,
     * которые потом связываются методом bindValue
     * для подстановки данных из QVariantList
     * */
    query.prepare("INSERT INTO " TABLE_USERS " ( " TABLE_LOGIN ", " TABLE_PASSWORD ")"
                  "VALUES (:FLogin, :SPassword)");
    query.bindValue(":FLogin",          login);
    query.bindValue(":SPassword",       password);

    // После чего выполняется запросом методом exec()
    if(!query.exec())
    {
        qDebug() << "error insert into " << TABLE_USERS;
        qDebug() << query.lastError().text();
        return false;
    }
    else
    {
        return true;
    }
}

List<user> DataBase::getUserFromTable()
{
    List<user> users;
    QSqlQuery query;

    if(!query.exec("SELECT * FROM users;"))
    {
        qDebug() << "DataBase: error ";
        qDebug() << query.lastError().text();
    }
    else
    {
        while(query.next())
        {
            user* tmp = new user();
            tmp->setId(query.value(0).toInt());
            tmp->setLogin(query.value(1).toString());
            tmp->setPassword(query.value(2).toString());
            users.AddEnd(*tmp);
            delete tmp;
        }
    }
    return users;
}

List<admin> DataBase::getAdminFromTable()
{
    List<admin> admins;
    QSqlQuery query;
    if(!query.exec("SELECT * FROM admins;"))
    {
        qDebug() << "DataBase: error of create ";
        qDebug() << query.lastError().text();
    }
    else
    {
        while(query.next())
        {
            admin* tmp = new admin();
            tmp->setId(query.value(0).toInt());
            tmp->setLogin(query.value(1).toString());
            tmp->setPassword(query.value(2).toString());
            admins.AddEnd(*tmp);
            delete tmp;
        }
    }
    return admins;
}

bool DataBase::checkRegWindow(QString login)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM admins WHERE login = :FLogin;");
    query.bindValue(":FLogin",          login);

    if(!query.exec())
    {
        qDebug() << "DataBase: error ";
        qDebug() << query.lastError().text();
        return false;
    }
    else
    {
        while(query.next())
        {
            if(query.value(1).toString() == login)
                return false;
        }

        query.prepare("SELECT * FROM users WHERE login = :FLogin;");
        query.bindValue(":FLogin",          login);

        if(!query.exec())
        {
            qDebug() << "DataBase: error ";
            qDebug() << query.lastError().text();
            return false;
        }
        else
        {
            while(query.next())
            {
                if(query.value(1).toString() == login)
                    return false;
            }
        }
    }
    return true;
}

bool DataBase::insertItemsIntoTable(items item, QString login)
{
    QSqlQuery query;
    /* В начале SQL запрос формируется с ключами,
     * которые потом связываются методом bindValue
     * для подстановки данных из QVariantList
     * */
    query.prepare("INSERT INTO " TABLE_ITEMS " ( " TABLE_LOGIN ", "  ITEM_BRAND ", " ITEM_MODEL ", " ITEM_GENERATION ", " ITEM_YEAR ", " ITEM_ENGINEVOLUME ", " ITEM_GEARBOXTYPE ", " ITEM_BODY ", " ITEM_ENGINETYPE ", " ITEM_DRIVEUNIT ", " ITEM_MILEAGE ", " ITEM_PRICE ", " ITEM_BOOKING ")"
                  "VALUES (:PLogin, :FBrand, :SModel, :QGeneration, :WYear, :REndinevolume, :TGearboxtype, :YBody, :UEnginetype, :IDriveunit, :OMileage, :HPrice, :KBooking)");
    query.bindValue(":PLogin",          login);
    query.bindValue(":FBrand",          item.getBrand());
    query.bindValue(":SModel",          item.getModel());
    query.bindValue(":QGeneration",     item.getGeneration());
    query.bindValue(":WYear",           item.getYear());
    query.bindValue(":REndinevolume",   item.getEngineVolume());
    query.bindValue(":TGearboxtype",    item.getGearboxType());
    query.bindValue(":YBody",           item.getBody());
    query.bindValue(":UEnginetype",     item.getEngineType());
    query.bindValue(":IDriveunit",      item.getDriveUnit());
    query.bindValue(":OMileage",        item.getMileage());
    query.bindValue(":HPrice",          item.getPrice());
    query.bindValue(":KBooking",        item.getBooking());

    // После чего выполняется запросом методом exec()
    if(!query.exec())
    {
        qDebug() << "error insert into " << TABLE_ITEMS;
        qDebug() << query.lastError().text();
        return false;
    }
    else
    {
        return true;
    }
}

bool DataBase::deleteItem(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM items WHERE id = :Fid;");
    query.bindValue(":Fid", id);
    if(!query.exec())
    {
        qDebug() << "DataBase: error of delete ";
        qDebug() << query.lastError().text();
        return false;
    }
    else
        return true;

}

List<items> DataBase::getItemsFromTable(QString currentText, QString text)
{
    List<items> temp;
    QSqlQuery query = createSearchQuary(currentText, text );

    if(!query.exec())
    {
        qDebug() << "DataBase: error of get items";
        qDebug() << query.lastError().text();
    }
    else
    {
        while(query.next())
        {
            items* tmp = new items();
            tmp->setId(query.value(0).toInt());
            tmp->setLogin(query.value(1).toString());
            tmp->setBrand(query.value(2).toString());
            tmp->setModel(query.value(3).toString());
            tmp->setGeneration(query.value(4).toString());
            tmp->setYear(query.value(5).toInt());
            tmp->setEngineVolume(query.value(6).toString());
            tmp->setGearboxType(query.value(7).toString());
            tmp->setBody(query.value(8).toString());
            tmp->setEngineType(query.value(9).toString());
            tmp->setDriveUnit(query.value(10).toString());
            tmp->setMileage(query.value(11).toInt());
            tmp->setPrice(query.value(12).toInt());
            tmp->setBooking(query.value(13).toString());
            temp.AddEnd(*tmp);
            delete tmp;
        }
    }

    return temp;
}

QSqlQuery DataBase::createSearchQuary(QString currentText, QString text)
{
    QSqlQuery query;
    if(currentText == ITEM_BRAND)
    {
        query.prepare("SELECT * FROM items WHERE " ITEM_BRAND " = ?;");
        query.addBindValue(text);
        return query;
    }
    if(currentText == ITEM_MODEL)
    {
        query.prepare("SELECT * FROM items WHERE " ITEM_MODEL " = ?;");
        query.addBindValue(text);
        return query;
    }
    if(currentText == ITEM_GENERATION)
    {
        query.prepare("SELECT * FROM items WHERE " ITEM_GENERATION " = ?;");
        query.addBindValue(text);
        return query;
    }
    if(currentText == "Год выпуска")
    {
        query.prepare("SELECT * FROM items WHERE " ITEM_YEAR " = ?;");
        query.addBindValue(text);
        return query;
    }
    if(currentText == "Объем двигателя")
    {
        query.prepare("SELECT * FROM items WHERE " ITEM_ENGINEVOLUME " = ?;");
        query.addBindValue(text);
        return query;
    }
    if(currentText == "Тип КПП")
    {
        query.prepare("SELECT * FROM items WHERE " ITEM_GEARBOXTYPE " = ?;");
        query.addBindValue(text);
        return query;
    }
    if(currentText == ITEM_BODY)
    {
        query.prepare("SELECT * FROM items WHERE " ITEM_BODY " = ?;");
        query.addBindValue(text);
        return query;
    }
    if(currentText == "Тип двигателя")
    {
        query.prepare("SELECT * FROM items WHERE " ITEM_ENGINETYPE " = ?;");
        query.addBindValue(text);
        return query;
    }
    if(currentText == ITEM_DRIVEUNIT)
    {
        query.prepare("SELECT * FROM items WHERE " ITEM_DRIVEUNIT " = ?;");
        query.addBindValue(text);
        return query;
    }
    if(currentText == ITEM_MILEAGE)
    {
        query.prepare("SELECT * FROM items WHERE " ITEM_MILEAGE " = ?;");
        query.addBindValue(text);
        return query;
    }
    if(currentText == ITEM_PRICE)
    {
        query.prepare("SELECT * FROM items WHERE " ITEM_PRICE " = ?;");
        query.addBindValue(text);
        return query;
    }
}

bool DataBase::getItemFromTable(items* tmp, int id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM items WHERE id = :Fid;");
    query.bindValue(":Fid", id);

    if(!query.exec())
    {
        qDebug() << "DataBase: error of get item";
        qDebug() << query.lastError().text();
        return false;
    }
    else
    {
        while(query.next())
        {
            tmp->setId(query.value(0).toInt());
            tmp->setBrand(query.value(2).toString());
            tmp->setModel(query.value(3).toString());
            tmp->setGeneration(query.value(4).toString());
            tmp->setYear(query.value(5).toInt());
            tmp->setEngineVolume(query.value(6).toString());
            tmp->setGearboxType(query.value(7).toString());
            tmp->setBody(query.value(8).toString());
            tmp->setEngineType(query.value(9).toString());
            tmp->setDriveUnit(query.value(10).toString());
            tmp->setMileage(query.value(11).toInt());
            tmp->setPrice(query.value(12).toInt());
            tmp->setBooking(query.value(13).toString());
        }
    }
    return true;
}

bool DataBase::getLoginFromTable(QString& login, int id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM items WHERE id = :Fid;");
    query.bindValue(":Fid", id);

    if(!query.exec())
    {
        qDebug() << "DataBase: error of get item";
        qDebug() << query.lastError().text();
        return false;
    }
    else
    {
        while(query.next())
        {
            login = query.value(1).toString();
        }
    }
    return true;
}

bool DataBase::updateBooking(int id)
{
    QSqlQuery query;
    query.prepare("UPDATE items SET Бронь = 'Забронировано' WHERE id = ?;");
    query.addBindValue(id);

    if(!query.exec())
    {
        qDebug() << "DataBase: error of update booking";
        qDebug() << query.lastError().text();
        return false;
    }
    else
        return true;
}

bool DataBase::updateItem(items item)
{
    QSqlQuery query;
    query.prepare("UPDATE items SET " ITEM_BRAND " = ?, " ITEM_MODEL " = ?, " ITEM_GENERATION " = ?, " ITEM_YEAR " = ?, " ITEM_ENGINEVOLUME " = ?, " ITEM_GEARBOXTYPE " = ?, " ITEM_BODY " = ?, " ITEM_ENGINETYPE " = ?, " ITEM_DRIVEUNIT " = ?, " ITEM_MILEAGE " = ?, " ITEM_PRICE " = ? WHERE id = ?;");
    query.addBindValue(item.getBrand());
    query.addBindValue(item.getModel());
    query.addBindValue(item.getGeneration());
    query.addBindValue(item.getYear());
    query.addBindValue(item.getEngineVolume());
    query.addBindValue(item.getGearboxType());
    query.addBindValue(item.getBody());
    query.addBindValue(item.getEngineType());
    query.addBindValue(item.getDriveUnit());
    query.addBindValue(item.getMileage());
    query.addBindValue(item.getPrice());
    query.addBindValue(item.getId());

    if(!query.exec())
    {
        qDebug() << "DataBase: error of update ";
        qDebug() << query.lastError().text();
        return false;
    }
    else
        return true;
}

bool DataBase::sortColumns(int index)
{
    QSqlQuery query;
    List<items> item;
    List<QString> login;
    query = createQuary(index);


    if(!query.exec())
    {
        qDebug() << "DataBase: error of sort column";
        qDebug() << query.lastError().text();
        return false;
    }
    else
    {
        while(query.next())
        {
            items tmp;
            login.AddEnd(query.value(1).toString());
            tmp.setId(query.value(0).toInt());
            tmp.setBrand(query.value(2).toString());
            tmp.setModel(query.value(3).toString());
            tmp.setGeneration(query.value(4).toString());
            tmp.setYear(query.value(5).toInt());
            tmp.setEngineVolume(query.value(6).toString());
            tmp.setGearboxType(query.value(7).toString());
            tmp.setBody(query.value(8).toString());
            tmp.setEngineType(query.value(9).toString());
            tmp.setDriveUnit(query.value(10).toString());
            tmp.setMileage(query.value(11).toInt());
            tmp.setPrice(query.value(12).toInt());
            tmp.setBooking(query.value(13).toString());
            item.AddEnd(tmp);
        }

        deleteTableItems();
        for(int i = 0; i < item.Count(); i++)
            insertItemsIntoTable(item[i], login[i]);

        item.Clear();
        return true;
    }

}

QSqlQuery DataBase::createQuary(int index)
{
    QSqlQuery query;
    switch(index)
    {
        case 1:
            query.prepare("SELECT * FROM " TABLE_ITEMS " ORDER BY " TABLE_LOGIN          ";");
            break;
        case 2:
            query.prepare("SELECT * FROM " TABLE_ITEMS " ORDER BY " ITEM_BRAND          ";");
            break;
        case 3:
            query.prepare("SELECT * FROM " TABLE_ITEMS " ORDER BY " ITEM_MODEL          ";");
            break;
        case 4:
            query.prepare("SELECT * FROM " TABLE_ITEMS " ORDER BY " ITEM_GENERATION     ";");
            break;
        case 5:
            query.prepare("SELECT * FROM " TABLE_ITEMS " ORDER BY " ITEM_YEAR           ";");
            break;
        case 6:
            query.prepare("SELECT * FROM " TABLE_ITEMS " ORDER BY " ITEM_ENGINEVOLUME   ";");
            break;
        case 7:
            query.prepare("SELECT * FROM " TABLE_ITEMS " ORDER BY " ITEM_GEARBOXTYPE    ";");
            break;
        case 8:
            query.prepare("SELECT * FROM " TABLE_ITEMS " ORDER BY " ITEM_BODY           ";");
            break;
        case 9:
            query.prepare("SELECT * FROM " TABLE_ITEMS " ORDER BY " ITEM_ENGINETYPE     ";");
            break;
        case 10:
            query.prepare("SELECT * FROM " TABLE_ITEMS " ORDER BY " ITEM_DRIVEUNIT      ";");
            break;
        case 11:
            query.prepare("SELECT * FROM " TABLE_ITEMS " ORDER BY " ITEM_MILEAGE        ";");
            break;
        case 12:
            query.prepare("SELECT * FROM " TABLE_ITEMS " ORDER BY " ITEM_PRICE          ";");
            break;
        case 13:
            query.prepare("SELECT * FROM " TABLE_ITEMS " ORDER BY " ITEM_BOOKING           ";");
            break;
    }

    return query;
}

bool DataBase::deleteTableItems()
{
    QSqlQuery query;
    query.prepare("DELETE FROM " TABLE_ITEMS);

    if(!query.exec())
    {
        qDebug() << "DataBase: error of delete table";
        qDebug() << query.lastError().text();
        return false;
    }
    else
        return true;
}

void DataBase::DataBaseOpen()
{
    if(!db.open())
        throw DataBaseException("DataBase not open");
}

void DataBase::closeDataBase()
{
    db.close();
}
