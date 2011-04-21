#include <QtGui/QApplication>
#include "headers/qhda.h"
/// #include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("_pussbb");
    QCoreApplication::setOrganizationDomain("krabik.co.ua");
    QCoreApplication::setApplicationName("QHDA");
    QApplication::setApplicationName("QHDA");
    QApplication::setApplicationVersion("0.1.1.5");
  //   QPixmap pixmap("/data/333.png");
 //   QSplashScreen splash(pixmap);
//splash.show();splash.showMessage("Loaded modules");sleep(5);
//a.processEvents();splash.showMessage("Established connections");
    QHDA w;
    w.show();
///splash.finish(&w);
    return a.exec();
}
