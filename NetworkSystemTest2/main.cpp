#include <QCoreApplication>

#include "MainApp.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MainApp mainApp;

    return a.exec();
}
