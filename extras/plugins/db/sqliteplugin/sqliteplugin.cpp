
#include "sqliteplugin.h"


/*QString SqlitePlugin::echo(const QString &message)
{
    return message;
}
)*/
QString SqlitePlugin::version()
{
    return "0.0.1";
}
QString SqlitePlugin::db_driver_name()
{
    return "SQLITE";
}

bool SqlitePlugin::auth_conection()
{
    return true;
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
     return "QSQLITE_ENABLE_SHARED_CACHE";
 }

bool SqlitePlugin::create(QString file)
{
    if(file.isEmpty())
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

       db.setDatabaseName(file);
       if (!db.open()) {
           error_str  =  db.lastError().text();
           return false;
       }
       QString query=sqlres.readAll();
       QSqlQuery sql;
       QStringList querylist=query.split(";");
       for (int i = 0; i < querylist.size(); ++i)
           sql.exec(querylist.at(i));
       return true;
}

bool SqlitePlugin::open(QString connection)
{
    if(db.isOpen())
    {
        db.close();
        db.removeDatabase(db.connectionName());
        db.~QSqlDatabase();
    }
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(connection);
    if (!db.open()) {
        error_str  =  db.lastError().text();
        return false;
    }
    return true;
}
bool SqlitePlugin::open(QString connection,QMap<QString, QString> options )
{
Q_UNUSED(options);
    return true;
}

Q_EXPORT_PLUGIN2(sqliteplugin, SqlitePlugin);

