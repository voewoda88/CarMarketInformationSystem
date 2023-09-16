#include "additemwindow.h"
#include "ui_additemwindow.h"
#include <QString>


addItemWindow::addItemWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addItemWindow)
{
    ui->setupUi(this);
    setWindowTitle("Добавление");
    setFixedSize(370, 620);
    tmp = new items();

    QRegularExpression st("[a-zA-Z0-9-]{0,30}");
    QRegularExpression engineVolume("[0-9][.][0-9]");
    QRegularExpressionValidator* checkString = new QRegularExpressionValidator(st, this);
    QRegularExpressionValidator* checkEngineVolume = new QRegularExpressionValidator(engineVolume, this);
    ui->lineEditBrand->setValidator(checkString);
    ui->lineEditModel->setValidator(checkString);
    ui->lineEditGeneration->setValidator(checkString);
    ui->lineEditEngineVolume->setValidator(checkEngineVolume);


}

addItemWindow::~addItemWindow()
{
    delete ui;
}

void addItemWindow::on_pushButtonAdd_clicked()
{
    emit on_buttonAdd_clicked();
}

bool addItemWindow::addItem(QString login)
{
    if(checkLineEdit() == true && checkInteger() == true)
    {
        addItemInObject();
        db.connectToDataBase();
        db.insertItemsIntoTable(*tmp, login);
        db.closeDataBase();
        cleanLineEdit();
        hide();
        return true;
    }
    else
        return false;
}

void addItemWindow::addItemInObject()
{
    items item;
    item.setBrand(ui->lineEditBrand->text());
    tmp->setBrand(ui->lineEditBrand->text());
    tmp->setModel(ui->lineEditModel->text());
    tmp->setGeneration(ui->lineEditGeneration->text());
    tmp->setYear(ui->lineEditYear->text().toInt());
    tmp->setEngineVolume(ui->lineEditEngineVolume->text());
    tmp->setGearboxType(ui->comboBoxGearboxType->currentText());
    tmp->setBody(ui->comboBoxBody->currentText());
    tmp->setEngineType(ui->comboBoxEngineType->currentText());
    tmp->setDriveUnit(ui->comboBoxDriveUnit->currentText());
    tmp->setMileage(ui->lineEditMileage->text().toInt());
    tmp->setPrice(ui->lineEditPrice->text().toInt());
    tmp->setBooking();
}

bool addItemWindow::checkLineEdit()
{
    if(ui->lineEditBrand->text().isEmpty() == 1 || ui->lineEditModel->text().isEmpty() == 1 || ui->lineEditGeneration->text().isEmpty() == 1 ||
       ui->lineEditYear->text().isEmpty() == 1 || ui->lineEditEngineVolume->text().isEmpty() == 1 || ui->lineEditMileage->text().isEmpty() == 1 ||
       ui->lineEditPrice->text().isEmpty() == 1 || ui->comboBoxBody->currentText() == "Выберете тип:" || ui->comboBoxGearboxType->currentText() == "Выберете тип:" ||
       ui->comboBoxEngineType->currentText() == "Выберете тип:" || ui->comboBoxDriveUnit->currentText() == "Выберете тип:")
    {
         QMessageBox::warning(this, "Внимание","Вы не заполнили поле");
         return false;
    }
    else
        return true;

}

void addItemWindow::cleanLineEdit()
{
    ui->lineEditBrand->clear();
    ui->lineEditModel->clear();
    ui->lineEditEngineVolume->clear();
    ui->lineEditGeneration->clear();
    ui->lineEditMileage->clear();
    ui->lineEditYear->clear();
    ui->lineEditPrice->clear();
    ui->comboBoxBody->setCurrentText("Выберете тип:");
    ui->comboBoxGearboxType->setCurrentText("Выберете тип:");
    ui->comboBoxEngineType->setCurrentText("Выберете тип:");
    ui->comboBoxDriveUnit->setCurrentText("Выберете тип:");

}

bool addItemWindow::checkInteger()
{
    if(checkInt().inputYear(ui->lineEditYear->text().toInt()) == false)
    {
        QMessageBox::warning(this, "Внимание","Поле 'Год выпуска' заполнено не верно");
        return false;
    }
    if(checkInt().inputMileage(ui->lineEditMileage->text().toInt()) == false)
    {
        QMessageBox::warning(this, "Внимание","Поле 'Пробег' заполнено не верно");
        return false;
    }
    if(checkInt().inputPrice(ui->lineEditPrice->text().toInt()) == false)
    {
        QMessageBox::warning(this, "Внимание","Поле 'Цена' заполнено не верно");
        return false;
    }
    return true;
}
