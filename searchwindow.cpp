#include "searchwindow.h"
#include "ui_searchwindow.h"
#include "list.h"
//#include "list.cpp"
#include "items.h"
#include <QMessageBox>

searchwindow::searchwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::searchwindow)
{

    ui->setupUi(this);
    setWindowTitle("Поиск");
    setFixedSize(365, 145);

    result = new resultwindow();

    connect(this, SIGNAL(current_text_changed()), this, SLOT(setValidator()));
    connect(this, SIGNAL(button_search_clicked()), this, SLOT(showWindowResult()));
}

searchwindow::~searchwindow()
{
    delete ui;
}

void searchwindow::on_comboBoxSearch_currentTextChanged(const QString &arg1)
{
    emit current_text_changed();
}

void searchwindow::setValidator()
{
    if(ui->comboBoxSearch->currentText() == "Модель" || ui->comboBoxSearch->currentText() == "Марка" || ui->comboBoxSearch->currentText() == "Поколение" ||
       ui->comboBoxSearch->currentText() == "Тип КПП" || ui->comboBoxSearch->currentText() == "Кузов" || ui->comboBoxSearch->currentText() == "Тип двигателя" ||
       ui->comboBoxSearch->currentText() == "Привод")
    {
        QRegularExpression st("[А-яa-zA-Z0-9()-]{0,30}");
        QRegularExpressionValidator* checkString = new QRegularExpressionValidator(st, this);
        ui->lineEditSearch->setValidator(checkString);
    }
    else if(ui->comboBoxSearch->currentText() == "Объем двигателя")
    {
        QRegularExpression engineVolume("[0-9][.][0-9]");
        QRegularExpressionValidator* checkEngineVolume = new QRegularExpressionValidator(engineVolume, this);
        ui->lineEditSearch->setValidator(checkEngineVolume);
    }
    else
    {
        QRegularExpression myint("[0-9]{0,30}");
        QRegularExpressionValidator* checkMyInt = new QRegularExpressionValidator(myint, this);
        ui->lineEditSearch->setValidator(checkMyInt);
    }
}

void searchwindow::on_pushButton_clicked()
{
    emit button_search_clicked();
}

void searchwindow::showWindowResult()
{
    db.connectToDataBase();
    List<items> item = db.getItemsFromTable(ui->comboBoxSearch->currentText(), ui->lineEditSearch->text());
    db.closeDataBase();
    if(item.isEmpty() == true)
    {
        QMessageBox::warning(this, "Внимание","Объявления не найдены");
        cleanLineEdit();
    }
    else
    {
        hide();
        result->createUi();
        result->setElementsOfTable(item);
        result->show();
    }
}

void searchwindow::cleanLineEdit()
{
    ui->lineEditSearch->clear();
    ui->comboBoxSearch->setCurrentText("Критерий:");
}
