#include "resultwindow.h"
#include "ui_resultwindow.h"
#include <QModelIndex>

resultwindow::resultwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::resultwindow)
{
    ui->setupUi(this);
}

resultwindow::~resultwindow()
{
    delete ui;
}

void resultwindow::setElementsOfTable(List<items>& item)
{
    for(int i = 0; i < item.Count(); i++)
    {
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(item[i].getId())));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(item[i].getLogin()));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(item[i].getBrand()));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(item[i].getModel()));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(item[i].getGeneration()));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString::number(item[i].getYear())));
        ui->tableWidget->setItem(i, 6, new QTableWidgetItem(item[i].getEngineVolume()));
        ui->tableWidget->setItem(i, 7, new QTableWidgetItem(item[i].getGearboxType()));
        ui->tableWidget->setItem(i, 8, new QTableWidgetItem(item[i].getBody()));
        ui->tableWidget->setItem(i, 9, new QTableWidgetItem(item[i].getEngineType()));
        ui->tableWidget->setItem(i, 10, new QTableWidgetItem(item[i].getDriveUnit()));
        ui->tableWidget->setItem(i, 11, new QTableWidgetItem(QString::number(item[i].getMileage())));
        ui->tableWidget->setItem(i, 12, new QTableWidgetItem(QString::number(item[i].getPrice())));
        ui->tableWidget->setItem(i, 13, new QTableWidgetItem(item[i].getBooking()));
    }

     ui->tableWidget->resizeColumnsToContents();
}

void resultwindow::createUi()
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(14); // Указываем число колонок
    ui->tableWidget->setShowGrid(true); // Включаем сетку
       // Разрешаем выделение только одного элемента
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
       // Разрешаем выделение построчно
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
       // Устанавливаем заголовки колонок
     ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QStringList list;
    list << "id" << "Логин" << "Марка" << "Модель" << "Поколение" << "Год выпуска" << "Объем двигателя" << "Тип КПП" << "Кузов" << "Тип двигателя" << "Привод" << "Пробег" << "Цена" << "Бронь";
    ui->tableWidget->setHorizontalHeaderLabels(list);
       // Растягиваем последнюю колонку на всё доступное пространство
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
       // Скрываем колонку под номером 0
    ui->tableWidget->hideColumn(0);
}


void resultwindow::on_pushButtonOk_clicked()
{
    hide();
}

