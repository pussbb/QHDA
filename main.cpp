#include <QtGui/QApplication>
#include "headers/qhda.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QHDA w;
    w.show();

    return a.exec();
}
