#ifndef EDITWINDOW_H
#define EDITWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include "items.h"
#include "database.h"
#include "checkint.h"

namespace Ui {
class EditWindow;
}

class EditWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EditWindow(QWidget *parent = nullptr);
    ~EditWindow();
    void editItem();
    void setId(int);
    void setParameters();

signals:
    void button_edit_clicked();
    void update_table();

private slots:
    void on_pushButtonEdit_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::EditWindow *ui;
    DataBase db;
    items item;
    int id;

    bool checkLineEdit();
    void setLineEditText();
    void addItemInObject();
    bool checkInteger();
};

#endif // EDITWINDOW_H
