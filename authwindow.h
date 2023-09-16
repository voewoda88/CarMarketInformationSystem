#ifndef AUTHWINDOW_H
#define AUTHWINDOW_H

#include <QDialog>
#include "user.h"
#include "admin.h"
#include "database.h"

namespace Ui {
class authwindow;
}

class authwindow : public QDialog
{
    Q_OBJECT

public:
    explicit authwindow(QWidget *parent = nullptr);
    ~authwindow();
    void cleanLineEdit();
    bool authUser(bool& window, user& thisUser);
    bool checkLineEdit();

signals:
    void login_button_clicked();
    void register_button_clicked();

private slots:
    void on_buttonSignIn_clicked();
    void on_buttonRegistration_clicked();

private:
    Ui::authwindow *ui;
    DataBase db;
};

#endif // AUTHWINDOW_H
