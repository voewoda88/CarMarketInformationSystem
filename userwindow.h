#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QDialog>
#include <QString>
#include <QList>
#include <QSqlTableModel>
#include <QMenu>
#include <QCheckBox>
#include <QStandardItemModel>
#include <QDebug>
#include <QMenuBar>
#include "additemwindow.h"
#include "database.h"
#include "items.h"
#include "deletewindow.h"
#include "searchwindow.h"
#include "user.h"

namespace Ui {
class userwindow;
}

class userwindow : public QDialog
{
    Q_OBJECT

public:
    explicit userwindow(QWidget *parent = nullptr);
    ~userwindow();
    void setThisUser(user thisUser);

private slots:
    void showAddItemWindow();
    void addItem();
    void DeleteWindow();
    void showDeleteWindow();

    void on_tableView_doubleClicked(const QModelIndex &index);
    void setupModel();
    void sectionClicked(int);
    void showSearchWindow();

signals:
    void TableView_doubleClicked();

private:
    Ui::userwindow *ui;
    addItemWindow* additemwindow;
    DataBase db;
    QList <items> item;
    QSqlTableModel *model;
    deleteWindow* delWindow;
    searchwindow* sWindow;
    int id;
    user thisUser;

private:
    void createFileMenu();
    void createDesignTable();
};

#endif // USERWINDOW_H
