#include "registerwindow.h"
#include "ui_registerwindow.h"

registerwindow::registerwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerwindow)
{
    ui->setupUi(this);
    setFixedSize(520, 230);
    setWindowTitle("Регистрация");

    QRegularExpression st("[a-zA-Z0-9]{0,30}");
    QRegularExpressionValidator* check = new QRegularExpressionValidator(st, this);
    ui->lineLogin->setValidator(check);
    ui->linePassword->setValidator(check);
    ui->lineConfirmPassword->setValidator(check);
}

registerwindow::~registerwindow()
{
    delete ui;
}

//функции
bool registerwindow::regUser()
{
    confirmPassword = ui->lineConfirmPassword->text();
    if(checkLineEdit() == true)
    {
        QMessageBox::warning(this, "Внимание","Вы не заполнили ни одно поле");
        return false;
    }
    else if(ui->lineLogin->text() == ui->linePassword->text())
    {
        QMessageBox::warning(this, "Внимание","Логин не может совпадать с паролем");
        cleanLineEdit();
        return false;
    }
    else if(confirmPassword != ui->linePassword->text())
    {
         QMessageBox::warning(this, "Внимание","Пароль не был подтвержден");
         cleanLineEdit();
         return false;
    }
    else
    {
        db.connectToDataBase();
        if (db.checkRegWindow(ui->lineLogin->text()) == false)
        {
            QMessageBox::warning(this, "Внимание","Пользователь с таким именем\n уже существует");
            cleanLineEdit();
            return false;
        }

        db.inserIntoTable(ui->lineLogin->text(), ui->linePassword->text());
        db.closeDataBase();
        return true;
    }
}

bool registerwindow::checkLineEdit()
{
    if(ui->lineLogin->text().isEmpty() == true || ui->linePassword->text().isEmpty() == true || ui->lineConfirmPassword->text().isEmpty() == true)
        return true;
    else
        return false;
}

void registerwindow::cleanLineEdit()
{
    ui->lineLogin->clear();
    ui->linePassword->clear();
    ui->lineConfirmPassword->clear();
}
//слоты
void registerwindow::on_buttonRegistration_clicked()
{
    emit register_button_clicked();
}

void registerwindow::on_buttonBack_clicked()
{
    emit button_back_clicked();
}

