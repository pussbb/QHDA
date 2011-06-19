
#include "sqliteplugin.h"

QString SqlitePlugin::version()
{
    return "0.0.1";
}
QString SqlitePlugin::dbDriverName()
{
    return "SQLITE3";
}

bool SqlitePlugin::authConection()
{
    return false;
}
bool SqlitePlugin::isServerType()
{
    return false;
}

QMap<QString, QString> SqlitePlugin::defaultAuthOptions()
{
    QMap<QString, QString> map;
    map.insert("host","localhost");
    map.insert("port","3306");
    map.insert("username","root");
    map.insert("password","root");
    return map;
}
 QString SqlitePlugin::defaultConnectionOptions()
 {
     return "";
 }

bool SqlitePlugin::create(QString databaseName)
{
    if(databaseName.isEmpty())
    {
        errorStr  = tr("Could not cretate database.");
        return false;
    }
    QFile sqlres(":/sqlite/sql/db.sql");
       if (!sqlres.open(QIODevice::ReadOnly))
       {
           errorStr  = tr("Could read sql file.");
           return false;
       }
       if(db.isOpen())
           db.close();
       db = QSqlDatabase::addDatabase("QSQLITE");

       db.setDatabaseName(databaseName+".book");
       if (!db.open()) {
           errorStr  =  db.lastError().text();
           return false;
       }
       QString query=sqlres.readAll();
       QSqlQuery sql;
       QStringList querylist=query.split(";;");
       for (int i = 0; i < querylist.size(); ++i) {qDebug()<<querylist.at(i);
           sql.exec(querylist.at(i));
           if(sql.lastError().isValid()) {
               errorStr  =  sql.lastError().text();
               return false;
            }
       }
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
        errorStr  =  db.lastError().text();
        return false;
    }
    return true;
}
bool SqlitePlugin::open(QString databaseName,QMap<QString, QVariant> options )
{
    if(db.isOpen()) {
        db.close();
        db.removeDatabase(db.connectionName());
        db.~QSqlDatabase();
    }
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(databaseName+".book");
qDebug()<<databaseName;
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
        errorStr  =  db.lastError().text();
        return false;
    }
    return true;
}

bool SqlitePlugin::createCategory(QString categoryName,int parent)
{
    QSqlQuery sql;
    sql.exec("INSERT INTO bookcat (name,parent) VALUES('"+
            categoryName +"',"+QString::number(parent)+");");
    if(sql.lastError().isValid()) {
        errorStr = sql.lastError().text();
        return false;
    }
    else{
        return true;
    }

}

QVariantList SqlitePlugin::categoriesList(int parent)
{
    QSqlQuery sql;
    QVariantList results;
    if(parent < 0)
        sql.exec("SELECT * FROM bookcat ORDER BY id ASC;");
    else
        sql.exec("SELECT * FROM bookcat WHERE parent ="+QString::number(parent)+" ORDER BY id ASC;");
    if(sql.lastError().isValid()) {
        errorStr = sql.lastError().text();
        return results;
    }
    while(sql.next()) {
        QVariantMap attr;
        attr.insert("id",sql.value(0));
        attr.insert("parent",sql.value(2));
        attr.insert("name",sql.value(1));
        results.append(attr);
    }
    return results;
}

QVariantList SqlitePlugin::articlesList(int parent)
{
    QSqlQuery sql;
    QVariantList results;
    if(parent < 0)
        sql.exec("SELECT * FROM bookcat;");
    else
        sql.exec("SELECT * FROM bookcat WHERE parent ="+QString::number(parent)+";");
    if(sql.lastError().isValid()) {
        errorStr = sql.lastError().text();
        return results;
    }
    return results;
}
bool SqlitePlugin::deleteCategory(int id)
{
    QSqlQuery sql;
    sql.exec("DELETE FROM bookcat WHERE bookcat.id="+QString::number(id)+
             " OR bookcat.parent="+QString::number(id)+" ;");
    if(sql.lastError().isValid()) {
        errorStr = sql.lastError().text();
        return false;
    }
    return true;
}

bool SqlitePlugin::deleteArticle(int id)
{
    QSqlQuery sql;
    sql.exec("DELETE FROM articles WHERE articles.id = "+QString::number(id)+" ;");
    if(sql.lastError().isValid()) {
        errorStr = sql.lastError().text();
        return false;
    }
    return true;
}

Q_EXPORT_PLUGIN2(sqliteplugin, SqlitePlugin);
