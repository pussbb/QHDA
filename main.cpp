#include <QtGui/QApplication>
#include "headers/qhda.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("_pussbb");
    QCoreApplication::setOrganizationDomain("krabik.co.ua");
    QCoreApplication::setApplicationName("QHDA");
    QApplication::setApplicationName("QHDA");
    QApplication::setApplicationVersion("0.1.1.5");
    QHDA w;
    w.show();

    return a.exec();
}
