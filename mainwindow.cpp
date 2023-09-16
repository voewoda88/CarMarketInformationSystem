#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QStandardItemModel>
#include <QDebug>
//#include "searchwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(1140, 550);
    setWindowTitle("Меню");
    createFileMenu();
    additemwindow = new addItemWindow();
    delWindow = new deleteWindow();
    sWindow = new searchwindow();

    setupModel();
    createDesignTable();

    connect(additemwindow, SIGNAL(on_buttonAdd_clicked()), this, SLOT(addItem()));
    connect(this, SIGNAL(TableView_doubleClicked()), this, SLOT(showDeleteWindow()));
    connect(delWindow, SIGNAL(button_ok_clicked()), this, SLOT(DeleteWindow()));
    connect(delWindow, SIGNAL(update_table()), this, SLOT(setupModel()));
    connect(ui->tableView->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(sectionClicked(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createFileMenu()
{
   QAction* quit = new QAction("&Выход");
   QAction* New = new QAction("&Новый");
   QAction* Add = new QAction("&Добавить");
   QAction* Delete = new QAction("&Удалить таблицу");
   QAction* Search = new QAction("&Поиск");

   Add->setShortcut(tr("CTRL+R"));
   quit->setShortcut(tr("CTRL+Q"));
   Delete->setShortcut(tr("CTRL+D"));
   Search->setShortcut(tr("CTRL+B"));

   QMenu* file;
   QMenu* Edit;
   file = menuBar()->addMenu("&Главная");
   Edit = menuBar()->addMenu("&Редактирование");

   file->addAction(New);
   file->addSeparator();
   file->addAction(quit);

   Edit->addAction(Add);
   Edit->addSeparator();
   Edit->addAction(Search);
   Edit->addSeparator();
   Edit->addAction(Delete);


   connect(quit, &QAction::triggered, qApp, &QApplication::quit);
   connect(Add, SIGNAL(triggered()), this, SLOT(showAddItemWindow()));
   connect(Delete, SIGNAL(triggered()), this, SLOT(deleteTable()));
   connect(Search, SIGNAL(triggered()), this, SLOT(showSearchWindow()));
}

void MainWindow::setupModel()
{
    db.connectToDataBase();

    model = new QSqlTableModel();
    model->setTable("items");
    model->select();
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();

    db.closeDataBase();

}

void MainWindow::showAddItemWindow()
{
    additemwindow->show();
}

void MainWindow::DeleteWindow()
{
    if(delWindow->DeleteWindow() == true)
    {
        setupModel();
    }
}

void MainWindow::addItem()
{
    if(additemwindow->addItem("admin") == true)
    {
        setupModel();
    }
}

void MainWindow::createDesignTable()
{
    // Разрешаем выделение строк
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        // Устанавливаем режим выделения лишь одно строки в таблице
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        // Устанавливаем размер колонок по содержимому
    ui->tableView->resizeColumnsToContents();
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->setColumnHidden(0, true);
}

void MainWindow::showDeleteWindow()
{
    if(delWindow->isVisible() == false)
    {
        delWindow->setId(id);
        delWindow->adminsRadioButtons();
        delWindow->show();
    }
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    QModelIndex ind = model->index(index.row(), 0, QModelIndex());
    id = index.model()->data(ind, 0).toInt();
    emit TableView_doubleClicked();
}

void MainWindow::sectionClicked(int index)
{
    db.connectToDataBase();
    if(db.sortColumns(index))
    {
        setupModel();
    }
    db.closeDataBase();
}

void MainWindow::deleteTable()
{
    db.connectToDataBase();
    if(db.deleteTableItems())
        setupModel();
    db.deleteTableItems();
}

void MainWindow::showSearchWindow()
{
    sWindow->cleanLineEdit();
    sWindow->show();
}
