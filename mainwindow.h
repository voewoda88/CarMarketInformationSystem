#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QList>
#include <QSqlTableModel>
#include "additemwindow.h"
#include "database.h"
#include "items.h"
#include "deletewindow.h"
#include "searchwindow.h"
#include "user.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showAddItemWindow();
    void addItem();
    void DeleteWindow();
    void showDeleteWindow();

    void on_tableView_doubleClicked(const QModelIndex &index);
    void setupModel();
    void sectionClicked(int);
    void deleteTable();
    void showSearchWindow();

signals:
    void TableView_doubleClicked();

private:
    Ui::MainWindow *ui;
    addItemWindow* additemwindow;
    DataBase db;
    QList <items> item;
    QSqlTableModel *model;
    deleteWindow* delWindow;
    searchwindow* sWindow;
    int id;

private:
    void createFileMenu();
    void createDesignTable();
};
#endif // MAINWINDOW_H
