#ifndef ALLWINDOWS_H
#define ALLWINDOWS_H

#include <QObject>
#include "authwindow.h"
#include "registerwindow.h"
#include "mainwindow.h"
#include "userwindow.h"

class AllWindows : public QObject
{
    Q_OBJECT
public:
    AllWindows();
    void showAuth();

private slots:
    void showAuthWindow();
    void showRegWindow();
    void showMainWindow();
    void show();

private:
    MainWindow main;
    registerwindow* reg;
    authwindow* auth;
    userwindow* userwin;
};

#endif // ALLWINDOWS_H
