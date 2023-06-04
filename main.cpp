#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include "login.h"





int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Login l;
    l.show();


    return a.exec();


}
