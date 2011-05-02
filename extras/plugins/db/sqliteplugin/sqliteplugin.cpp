
#include "sqliteplugin.h"

QString SqlitePlugin::version()
{
    return "0.0.1";
}
QString SqlitePlugin::db_driver_name()
{
    return "SQLITE3";
}

bool SqlitePlugin::auth_conection()
{
    return false;
}
bool SqlitePlugin::is_server_type()
{
    return false;
}

QMap<QString, QString> SqlitePlugin::default_auth_options()
{
    QMap<QString, QString> map;
    map.insert("host","localhost");
    map.insert("port","3306");
    map.insert("username","root");
    map.insert("password","root");
    return map;
}
 QString SqlitePlugin::default_connection_options()
 {
     return "";
 }

bool SqlitePlugin::create(QString databaseName)
{
    if(databaseName.isEmpty())
    {
        error_str  = tr("Could not cretate database.");
        return false;
    }
    QFile sqlres(":/sqlite/sql/db.sql");
       if (!sqlres.open(QIODevice::ReadOnly))
       {
           error_str  = tr("Could read sql file.");
           return false;
       }
       if(db.isOpen())
           db.close();
       db = QSqlDatabase::addDatabase("QSQLITE");

       db.setDatabaseName(databaseName+".book");
       if (!db.open()) {
           error_str  =  db.lastError().text();
           return false;
       }
       QString query=sqlres.readAll();
       QSqlQuery sql;
       QStringList querylist=query.split(";");
       for (int i = 0; i < querylist.size(); ++i)
           sql.exec(querylist.at(i));
       db.close();
       db.removeDatabase(db.defaultConnection);
       return true;
}

bool SqlitePlugin::open(QString databaseName)
{
    if(db.isOpen())
    {
        db.close();
        db.removeDatabase(db.connectionName());
        db.~QSqlDatabase();
    }
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(databaseName+".book");
    if (!db.open()) {
        error_str  =  db.lastError().text();
        return false;
    }
    return true;
}
bool SqlitePlugin::open(QString databaseName,QMap<QString, QVariant> options )
{
    if(db.isOpen())
    {
        db.close();
        db.removeDatabase(db.connectionName());
        db.~QSqlDatabase();
    }
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(databaseName+".book");

    if(options.value("host","") != "")
        db.setHostName(options.value("host").toString());
    if(options.value("port","") != "")
        db.setPort(options.value("port").toInt());
    if(options.value("username","") != "")
        db.setUserName(options.value("username").toString());
    if(options.value("password","") != "")
        db.setPassword(options.value("password").toString());
    if(options.value("connoptions","") != "")
        db.setConnectOptions(options.value("connoptions").toString());

    if (!db.open()) {
        error_str  =  db.lastError().text();
        return false;
    }
    return true;
}

Q_EXPORT_PLUGIN2(sqliteplugin, SqlitePlugin);

