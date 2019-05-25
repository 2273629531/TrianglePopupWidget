#include "mainwindow.h"
#include <QApplication>
#include "trianglepopupwidget.h"
#include <qlabel.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w1;
    w1.show();



    return a.exec();
}
