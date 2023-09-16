#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include "database.h"
#include <QDialog>
#include "resultwindow.h"

namespace Ui {
class searchwindow;
}

class searchwindow : public QDialog
{
    Q_OBJECT

public:
    explicit searchwindow(QWidget *parent = nullptr);
    ~searchwindow();
    void cleanLineEdit();

signals:
    void current_text_changed();
    void button_search_clicked();

private slots:
    void on_comboBoxSearch_currentTextChanged(const QString &arg1);
    void setValidator();
    void showWindowResult();
    void on_pushButton_clicked();

private:
    Ui::searchwindow *ui;
    DataBase db;
    resultwindow* result;
};

#endif // SEARCHWINDOW_H
