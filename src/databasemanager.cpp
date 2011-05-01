#include "headers/databasemanager.h"

DataBaseManager::DataBaseManager(QObject *parent) :
    QObject(parent)
{
    QDir pluginsDir("/opt/qt_projects/QHDA/bin/");
    #if defined(Q_OS_WIN)
        if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
            pluginsDir.cdUp();
    #elif defined(Q_OS_MAC)
        if (pluginsDir.dirName() == "MacOS") {
            pluginsDir.cdUp();
            pluginsDir.cdUp();
            pluginsDir.cdUp();
        }
    #endif
    pluginsDir.cd("plugins");
    pluginsDir.cd("db");
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();
        if (plugin) {
            interface = qobject_cast<DbManagerInterface *>(plugin);

        }
    }
    qDebug()<< interface;

    try {
        qDebug()<<interface->version();
    } catch (QtConcurrent::Exception &e) {

    }
}
