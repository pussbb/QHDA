#include <QtGui/QApplication>
#include "qhda.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QHDA w;
    w.show();

    return a.exec();
}
