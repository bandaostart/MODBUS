#include "mainwindow.h"
#include <QApplication>
#include "showwindow.h"
#include "showtext.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

//    ShowWindow w;
//    w.show();

//    ShowText w;
//    w.show();

    return a.exec();
}
