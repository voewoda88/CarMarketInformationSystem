#ifndef RESULTWINDOW_H
#define RESULTWINDOW_H

#include <QDialog>
#include <QStringList>
#include "items.h"
#include "list.h"
#include <QTableWidgetItem>

namespace Ui {
class resultwindow;
}

class resultwindow : public QDialog
{
    Q_OBJECT

public:
    explicit resultwindow(QWidget *parent = nullptr);
    ~resultwindow();
    void setItems(List<items>);
    void setElementsOfTable(List<items>& item);
    void createUi();

signals:
    void TableView_doubleClicked();

private slots:
    void on_pushButtonOk_clicked();

private:
    Ui::resultwindow *ui;
    List<items> item;
    int id;
};

#endif // RESULTWINDOW_H
