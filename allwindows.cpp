#include "allwindows.h"
#include "QtDebug"
#include "user.h"

AllWindows::AllWindows()
{
    auth = new authwindow();
    reg = new registerwindow();
    userwin = new userwindow();

    connect(auth, SIGNAL(login_button_clicked()), this, SLOT(showMainWindow()));
    connect(auth, SIGNAL(register_button_clicked()), this, SLOT(showRegWindow()));
    connect(reg, SIGNAL(register_button_clicked()), this, SLOT(showAuthWindow()));
    connect(reg, SIGNAL(button_back_clicked()), this, SLOT(show()));
}

void AllWindows::showAuth()
{
    auth->show();
}

void AllWindows::show()
{
    reg->hide();
    auth->show();
}

void AllWindows::showRegWindow()
{
    auth->hide();
    reg->show();
    reg->cleanLineEdit();
}

void AllWindows::showAuthWindow()
{
    bool temp = reg->regUser();
    if(temp == true)
    {
        reg->hide();
        auth->show();
        auth->cleanLineEdit();
    }
}

void AllWindows::showMainWindow()
{
    bool window;
    user thisUser;
    bool temp = auth->authUser(window, thisUser);
    if(temp == true && window == true)
    {
        auth->hide();
        main.show();
    }
    else if(temp == true && window == false)
    {
        auth->hide();
        userwin->setThisUser(thisUser);
        userwin->show();
    }
}

