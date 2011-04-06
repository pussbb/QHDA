#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("K_Alexworld");
    QCoreApplication::setOrganizationDomain("krabik.co.ua");
    QCoreApplication::setApplicationName("Help World");
    QCoreApplication::setApplicationVersion("0.0.0.5");
    MainWindow w;
    w.showMaximized();
    w.show();
    return a.exec();
}
