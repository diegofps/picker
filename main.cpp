#include "mainwindow.h"

#include <QApplication>
#include <wup/wup.hpp>

WUP_STATICS;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
