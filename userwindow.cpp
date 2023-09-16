#include "userwindow.h"
#include "ui_userwindow.h"
#include <QMainWindow>

userwindow::userwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userwindow)
{
    ui->setupUi(this);

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

userwindow::~userwindow()
{
    delete ui;
}

void userwindow::createFileMenu()
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

   QMenuBar* menuBar = new QMenuBar(this);
//   file = menuBar()->addMenu("&File");
//   Edit = menuBar()->addMenu("&Edit");
   file = menuBar->addMenu("&Главная");
   Edit = menuBar->addMenu("&Редактирование");

   file->addAction(New);
   file->addSeparator();
   file->addAction(quit);

   Edit->addAction(Add);
   Edit->addSeparator();
   Edit->addAction(Search);


   connect(quit, &QAction::triggered, qApp, &QApplication::quit);
   connect(Add, SIGNAL(triggered()), this, SLOT(showAddItemWindow()));
   connect(Search, SIGNAL(triggered()), this, SLOT(showSearchWindow()));
}

void userwindow::setupModel()
{
    db.connectToDataBase();

    model = new QSqlTableModel();
    model->setTable("items");
    model->select();
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();

    db.closeDataBase();

}

void userwindow::showAddItemWindow()
{
    additemwindow->show();
}

void userwindow::DeleteWindow()
{
    if(delWindow->DeleteWindow() == true)
    {
        setupModel();
    }
}

void userwindow::addItem()
{
    if(additemwindow->addItem(thisUser.getLogin()) == true)
    {
        setupModel();
    }
}

void userwindow::createDesignTable()
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

void userwindow::showDeleteWindow()
{
    if(delWindow->isVisible() == false)
    {
        delWindow->setId(id);
        QString login;
        db.connectToDataBase();
        db.getLoginFromTable(login, id);
        db.closeDataBase();
        if(thisUser.getLogin() != login)
            delWindow->usersRadioButtons();
        else
            delWindow->adminsRadioButtons();
        delWindow->show();
    }
}

void userwindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    QModelIndex ind = model->index(index.row(), 0, QModelIndex());
    id = index.model()->data(ind, 0).toInt();
    emit TableView_doubleClicked();
}

void userwindow::sectionClicked(int index)
{
    db.connectToDataBase();
    if(db.sortColumns(index))
    {
        setupModel();
    }
    db.closeDataBase();
}


void userwindow::showSearchWindow()
{
    sWindow->show();
}

void userwindow::setThisUser(user thisUser)
{
    this->thisUser = thisUser;
}
