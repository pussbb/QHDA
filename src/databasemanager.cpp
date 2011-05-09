#include "headers/databasemanager.h"

DataBaseManager::DataBaseManager(QObject *parent) :
    QObject(parent)
{
    getPluginsList();
}

bool DataBaseManager::loadPlugin(QString file)
{
    if(file.isEmpty())
        return false;
     QPluginLoader pluginLoader(file);
     QObject *plugin = pluginLoader.instance();
     if (plugin) {
         interface = qobject_cast<DbManagerInterface *>(plugin);
         return true;
     }
     else
         return false;
}

void DataBaseManager::getPluginsList(QString path)
{
    if(path.isEmpty())
        path = qApp->applicationDirPath()+QDir::toNativeSeparators("/plugins/db/");
    QDir pluginsDir(path);
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();
        if (plugin) {
            interface = qobject_cast<DbManagerInterface *>(plugin);
            plugins.insert(interface->dbDriverName(),interface);
            qDebug()<< interface->authConection();
        }
    }
}
