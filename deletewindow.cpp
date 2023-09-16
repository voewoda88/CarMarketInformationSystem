#include "deletewindow.h"
#include "ui_deletewindow.h"

deleteWindow::deleteWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deleteWindow)
{
    ui->setupUi(this);
    setFixedSize(310, 105);
    setWindowTitle("Редактирование");
    editwindow = new EditWindow();

    connect(editwindow, SIGNAL(button_edit_clicked()), this, SLOT(editItem()));
    connect(editwindow, SIGNAL(update_table()), this, SLOT(updateTable()));
}

deleteWindow::~deleteWindow()
{
    delete ui;
}

void deleteWindow::setId(int id)
{
    this->id = id;
}

int deleteWindow::getId()
{
    return id;
}

void deleteWindow::on_buttonCancel_clicked()
{
    hide();
}


void deleteWindow::on_buttonOk_clicked()
{
    emit button_ok_clicked();
}

bool deleteWindow::DeleteWindow()
{
        if(ui->radioButtonDelete->isChecked() == true)
        {
            Delete();
            hide();
            return true;
        }
        else if(ui->radioButtonEdit->isChecked() == true)
        {
            hide();
            editwindow->setId(id);
            showEditWindow();
            return true;
        }
        else if(ui->radioButtonBooking->isChecked() == true)
        {
            items item;
            db.connectToDataBase();
            db.getItemFromTable(&item, id);
            if(item.getBooking() == "Не забронировано")
            {
                hide();
                db.updateBooking(id);
                db.closeDataBase();
                return true;
            }
            else
            {
                QMessageBox::warning(this, "Внимание","Авто уже забронировано");
                return false;
            }
        }
        else
        {
            QMessageBox::warning(this, "Внимание","Вы не выбрали ни один из пунктов");
            return false;
        }
}

void deleteWindow::Delete()
{
    db.connectToDataBase();
    db.deleteItem(id);
    db.closeDataBase();
}

void deleteWindow::showEditWindow()
{
    editwindow->setParameters();
    editwindow->show();
}

void deleteWindow::editItem()
{
    editwindow->editItem();
}

void deleteWindow::updateTable()
{
    emit update_table();
}

void deleteWindow::usersRadioButtons()
{
   ui->radioButtonEdit->setVisible(false);
   ui->radioButtonDelete->setVisible(false);
   ui->radioButtonBooking->setVisible(true);
}

void deleteWindow::adminsRadioButtons()
{
   ui->radioButtonBooking->setVisible(false);
   ui->radioButtonEdit->setVisible(true);
   ui->radioButtonDelete->setVisible(true);
}
