#include "authwindow.h"
#include "ui_authwindow.h"
#include <QtDebug>
#include <QMessageBox>
#include <QValidator>
#include "list.h"

authwindow::authwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::authwindow)
{
    ui->setupUi(this);

    setFixedSize(510, 180);
    setWindowTitle("Вход");
    QRegularExpression st("[a-zA-Z0-9-]{0,30}");
    QRegularExpressionValidator* check = new QRegularExpressionValidator(st, this);
    ui->lineLogin->setValidator(check);
    ui->linePassword->setValidator(check);
}

authwindow::~authwindow()
{
    delete ui;
}

//функции
void authwindow::cleanLineEdit()
{
    ui->lineLogin->clear();
    ui->linePassword->clear();
}

bool authwindow::authUser(bool& window, user& thisUser)
{
    if(checkLineEdit() == true)
    {
        QMessageBox::warning(this, "Внимание","Вы не заполнили поле");
        cleanLineEdit();
        return false;
    }
    else
    {
        List<user> users;
        List<admin> admins;
        db.connectToDataBase();
        users = db.getUserFromTable();
        admins = db.getAdminFromTable();
        db.closeDataBase();

        Iterator<user> userIt(users);
        Iterator<admin> adminIt(admins);

        int countOfAdmins = admins.Count() - 1;
        int countOfUsers = users.Count() - 1;

        if(users.isEmpty() == true)
                {
                    QMessageBox::warning(this, "Внимание","Ни один пользователь не зарегистрирован");
                    cleanLineEdit();
                    return false;
                }
                while(adminIt.hasNext())
                {
                    if(ui->lineLogin->text() == admins[countOfAdmins].getLogin() && ui->linePassword->text() == admins[countOfAdmins].getPassword())
                    {
                        window = true;
                        return true;
                    }
                    adminIt.next();
                    countOfAdmins--;
                }
                while(userIt.hasNext())
                {
                    if(ui->lineLogin->text() == users[countOfUsers].getLogin() && ui->linePassword->text() == users[countOfUsers].getPassword())
                    {
                        thisUser = users[countOfUsers];
                        window = false;
                        return true;
                    }
                    userIt.next();
                    countOfUsers--;
                }
        QMessageBox::warning(this, "Внимание","Неправильно введены\nлогин или пароль");
        cleanLineEdit();
        admins.Clear();
        users.Clear();
        return false;
    }
}

bool authwindow::checkLineEdit()
{
    if(ui->lineLogin->text().isEmpty() == true || ui->linePassword->text().isEmpty() == true)
        return true;
    else
        return false;
}

//cлоты
void authwindow::on_buttonSignIn_clicked()
{
    emit login_button_clicked();
}


void authwindow::on_buttonRegistration_clicked()
{
    emit register_button_clicked();
}



