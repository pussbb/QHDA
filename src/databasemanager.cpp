#include "headers/databasemanager.h"

DataBaseManager::DataBaseManager(QObject *parent) :
    QObject(parent)
{
    get_plugins_list();
}

bool DataBaseManager::load_plugin(QString file)
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

void DataBaseManager::get_plugins_list(QString path)
{
    if(path.isEmpty())
        path = qApp->applicationDirPath()+QDir::toNativeSeparators("/plugins/db/");
    QDir pluginsDir(path);
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();
        if (plugin) {
            interface = qobject_cast<DbManagerInterface *>(plugin);
            plugins.insert(interface->db_driver_name(),interface);
            qDebug()<< interface->auth_conection();
        }
    }
}
