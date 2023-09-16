#ifndef ADDITEMWINDOW_H
#define ADDITEMWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include "items.h"
#include "database.h"
#include "checkint.h"

namespace Ui {
class addItemWindow;
}

class addItemWindow : public QDialog
{
    Q_OBJECT

public:
    explicit addItemWindow(QWidget *parent = nullptr);
    ~addItemWindow();
    void addItemInObject();
    bool checkLineEdit();
    bool addItem(QString login);
    void cleanLineEdit();
    bool checkInteger();

signals:
    void on_buttonAdd_clicked();

private slots:
    void on_pushButtonAdd_clicked();

private:
    Ui::addItemWindow *ui;
    DataBase db;
    items* tmp;
};

#endif // ADDITEMWINDOW_H
