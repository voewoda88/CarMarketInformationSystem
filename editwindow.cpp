#include "editwindow.h"
#include "ui_editwindow.h"

EditWindow::EditWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditWindow)
{
    ui->setupUi(this);
    setWindowTitle("Редактирование");
    setFixedSize(370, 630);

    QRegularExpression st("[a-zA-Z0-9-]{0,30}");
    QRegularExpression engineVolume("[0-9][.][0-9]");
    QRegularExpressionValidator* checkString = new QRegularExpressionValidator(st, this);
    QRegularExpressionValidator* checkEngineVolume = new QRegularExpressionValidator(engineVolume, this);
    ui->lineEditBrand->setValidator(checkString);
    ui->lineEditModel->setValidator(checkString);
    ui->lineEditGeneration->setValidator(checkString);
    ui->lineEditEngineVolume->setValidator(checkEngineVolume);
}

EditWindow::~EditWindow()
{
    delete ui;
}

void EditWindow::editItem()
{
    if(checkLineEdit() == true && checkInteger() == true)
    {
        db.connectToDataBase();
        addItemInObject();
        db.updateItem(item);
        db.closeDataBase();
        hide();
        emit update_table();
    }
}

void EditWindow::setId(int id)
{
    this->id = id;
}

void EditWindow::setParameters()
{
    db.connectToDataBase();
    db.getItemFromTable(&item, id);
    db.closeDataBase();
    setLineEditText();
}

void EditWindow::on_pushButtonEdit_clicked()
{
    emit button_edit_clicked();
}

bool EditWindow::checkLineEdit()
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

void EditWindow::setLineEditText()
{
    ui->lineEditBrand->setText(item.getBrand());
    ui->lineEditModel->setText(item.getModel());
    ui->lineEditGeneration->setText(item.getGeneration());
    ui->lineEditYear->setText(QString::number(item.getYear()));
    ui->lineEditEngineVolume->setText(item.getEngineVolume());
    ui->lineEditMileage->setText(QString::number(item.getMileage()));
    ui->lineEditPrice->setText(QString::number(item.getPrice()));
    ui->comboBoxBody->setCurrentText(item.getBody());
    ui->comboBoxGearboxType->setCurrentText(item.getGearboxType());
    ui->comboBoxEngineType->setCurrentText(item.getEngineType());
    ui->comboBoxDriveUnit->setCurrentText(item.getDriveUnit());
}

void EditWindow::addItemInObject()
{
    item.setBrand(ui->lineEditBrand->text());
    item.setModel(ui->lineEditModel->text());
    item.setGeneration(ui->lineEditGeneration->text());
    item.setYear(ui->lineEditYear->text().toInt());
    item.setEngineVolume(ui->lineEditEngineVolume->text());
    item.setGearboxType(ui->comboBoxGearboxType->currentText());
    item.setBody(ui->comboBoxBody->currentText());
    item.setEngineType(ui->comboBoxEngineType->currentText());
    item.setDriveUnit(ui->comboBoxDriveUnit->currentText());
    item.setMileage(ui->lineEditMileage->text().toInt());
    item.setPrice(ui->lineEditPrice->text().toInt());
}

void EditWindow::on_pushButtonCancel_clicked()
{
    hide();
}

bool EditWindow::checkInteger()
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
