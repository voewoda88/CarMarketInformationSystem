#ifndef DELETEWINDOW_H
#define DELETEWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include "database.h"
#include "editwindow.h"
#include "items.h"

namespace Ui {
class deleteWindow;
}

class deleteWindow : public QDialog
{
    Q_OBJECT

public:
    explicit deleteWindow(QWidget *parent = nullptr);
    ~deleteWindow();
    void setId(int);
    int getId();
    bool DeleteWindow();
    void usersRadioButtons();
    void adminsRadioButtons();

signals:
    void button_ok_clicked();
    void button_cancel_clicked();
    void update_table();

private slots:
    void on_buttonCancel_clicked();
    void on_buttonOk_clicked();
    void editItem();
    void updateTable();

private:
    void Delete();
    void showEditWindow();

private:
    Ui::deleteWindow *ui;
    DataBase db;
    EditWindow* editwindow;
    int id;
};

#endif // DELETEWINDOW_H
