#include "allwindows.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AllWindows w;

    w.showAuth();
    return a.exec();
}
