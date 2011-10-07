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

void DataBaseManager::showError() {
    QMessageBox::warning(0,  QObject::tr("Database engine error"),
                               interface->errorStr);

}

void DataBaseManager::setCurrentInterface(QString interfaceName)
{
    interface = plugins.value(interfaceName);
}

bool DataBaseManager::saveArticle(QVariantMap article)
{
    if(article.value("id",-1).toInt() <= 0)
       return newArticle(article);
    else
       return updateArticle(article);
}

bool DataBaseManager::newArticle(QVariantMap article)
{
    QByteArray hash = QCryptographicHash::hash(article.value("content")
                                               .toString()
                                               .toLocal8Bit(), QCryptographicHash::Md5);
    QSettings settings;
    article.insert("md5",hash.toHex());
    article.insert("guid",QUuid::createUuid().toString());
    article.insert("author",settings.value("Core/username","anonymous"));

    if(interface->createArticle(article))
        return true;
    else
        showError();
    return false;
}

bool DataBaseManager::updateArticle(QVariantMap article)
{
    QByteArray hash = QCryptographicHash::hash(article.value("content")
                                               .toString()
                                               .toLocal8Bit(), QCryptographicHash::Md5);
    QSettings settings;
    article.insert("md5",hash.toHex());
    article.insert("author",settings.value("Core/username","anonymous"));

    if(interface->updateArticle(article))
        return true;
    else
        showError();
    return true;
}
