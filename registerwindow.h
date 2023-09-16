#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QDialog>
#include <QString>
#include <QList>
#include <QValidator>
#include <QMessageBox>
#include "admin.h"
#include "user.h"
#include "database.h"

namespace Ui {
class registerwindow;
}

class registerwindow : public QDialog
{
    Q_OBJECT

public:
    explicit registerwindow(QWidget *parent = nullptr);
    ~registerwindow();
    bool regUser();
    void cleanLineEdit();
    bool checkLineEdit();

signals:
    void register_button_clicked();
    void button_back_clicked();

private slots:
    void on_buttonRegistration_clicked();

    void on_buttonBack_clicked();

private:
    Ui::registerwindow *ui;
    QString confirmPassword;
    QList<admin> admins;
    QList<user> users;
    DataBase db;
};

#endif // REGISTERWINDOW_H
