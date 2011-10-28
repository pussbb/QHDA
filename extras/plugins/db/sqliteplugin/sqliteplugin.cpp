
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
    ///just for test was needed
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
        QSqlDatabase::removeDatabase(db.connectionName());
    }
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(databaseName+".book");
    if (!db.open()) {
        errorStr  =  db.lastError().text();
        return false;
    }
    createTableColumnsNames();
    return true;
}
void SqlitePlugin::createTableColumnsNames()
{
    QSqlQuery sql;
    sql.exec("pragma table_info(articles)");
    while(sql.next()) {
        articlesColumns.insert(sql.value(1).toString(),(QVariant)"");
    }
}

bool SqlitePlugin::open(QString databaseName,QMap<QString, QVariant> options )
{
    if(db.isOpen()) {
        db.close();
        QSqlDatabase::removeDatabase(db.connectionName());
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
        errorStr  =  db.lastError().text();
        return false;
    }
    createTableColumnsNames();
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

QVariantList SqlitePlugin::categoriesList(int parent,int limit,bool sync)
{
    QSqlQuery sql;
    QVariantList results;
    QString limitStr = "";
    QString query = "";
    if(limit > 0)
        limitStr = " LIMIT "+QString::number(limit);
    if(parent < 0 && sync == false)
        query = "SELECT * FROM bookcat ORDER BY id ASC" + limitStr +";";
    else if(!sync)
            query = "SELECT * FROM bookcat WHERE parent ="+QString::number(parent)+" ORDER BY id ASC" + limitStr +";";
         else
            query = "SELECT * FROM bookcat WHERE synch_state = 0 ORDER BY id ASC" + limitStr +";";

    sql.exec(query);
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

QVariantList SqlitePlugin::articlesList(int parent,int limit,bool sync)
{
    QSqlQuery sql;
    QVariantList results;
    QVariantMap columns = articlesColumns;
    QString limitStr = "";
    QString query = "";
    if(limit > 0)
        limitStr = " LIMIT "+QString::number(limit);

    if(parent < 0 && sync == false)
        query = "SELECT * FROM articles " + limitStr +";";
    else if(!sync)
            query = "SELECT * FROM articles WHERE catid ="+QString::number(parent)+" ORDER BY id ASC" + limitStr +";";
         else
            query = "SELECT * FROM articles WHERE synch_state = 0 ORDER BY id ASC" + limitStr +";";

    sql.exec(query);
    if(sql.lastError().isValid()) {
        errorStr = sql.lastError().text();
        return results;
    }

    int fieldId = 0;
    while(sql.next()) {
        foreach(QString column, columns.keys() ) {
           fieldId = sql.record().indexOf(column);
            columns.insert(column,sql.value(fieldId));
        }
        results.append(columns);
    }

    return results;
}
QVariantMap SqlitePlugin::getTableColumnNames(QString tableName)
{
    if(tableName == "articles")
        return articlesColumns;
    return QVariantMap();
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

bool SqlitePlugin::createArticle(QVariantMap article)
{
    QSqlQuery sql;
    sql.prepare("INSERT INTO articles (title,content, author, published,md5,catid,guid,synch_state)"
                  " VALUES (?,?,?,?,?,?,?,?)");
    sql.bindValue(0,article.value("title"));
    sql.bindValue(1,article.value("content"));
    sql.bindValue(2,article.value("author"));
    sql.bindValue(3,QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss"));
    sql.bindValue(4,article.value("md5"));
    sql.bindValue(5,article.value("catid"));
    sql.bindValue(6,article.value("guid"));
    sql.bindValue(7,article.value("synch_state",0));
   // qDebug()<<sql.boundValues();
    sql.exec();
    if(sql.lastError().isValid()) {
        errorStr = sql.lastError().text();
        return false;
    }
    return true;
}

QVariantMap SqlitePlugin::article(int id)
{
    QSqlQuery sql;
    QVariantMap article = articlesColumns;
    sql.exec("SELECT * FROM articles WHERE id = "+QString::number(id)+";");
    if(sql.lastError().isValid()) {
        errorStr = sql.lastError().text();
        return articlesColumns;
    }
    sql.next();
    int fieldId = 0;
    foreach(QString column, article.keys()) {
      fieldId = sql.record().indexOf(column);
      article.insert(column,sql.value(fieldId));
    }
    return article;
}

bool SqlitePlugin::updateArticle(QVariantMap article)
{
    QSqlQuery sql;
    sql.prepare("UPDATE articles SET title=? ,content=? , author=?, md5=?, catid=?, synch_state=?"
                  " WHERE id=?");
    sql.bindValue(0,article.value("title"));
    sql.bindValue(1,article.value("content"));
    sql.bindValue(2,article.value("author"));
    sql.bindValue(3,article.value("md5"));
    sql.bindValue(4,article.value("catid"));
    sql.bindValue(5,article.value("synch_state",0));
    sql.bindValue(6,article.value("id"));
    sql.exec();
    if(sql.lastError().isValid()) {
        errorStr = sql.lastError().text();
        return false;
    }
    return true;
}

QVariantList SqlitePlugin::search(QString search)
{
    QVariantList results;
    QSqlQuery sql("SELECT * FROM `articles` WHERE `content` like '%"+search+"%'");

    sql.exec();

    if(sql.lastError().isValid()) {
        errorStr = sql.lastError().text();
        return results;
    }
    QVariantMap columns = articlesColumns;
    int fieldId = 0;
    while(sql.next()) {
        foreach(QString column, columns.keys() ) {
           fieldId = sql.record().indexOf(column);
            columns.insert(column,sql.value(fieldId));
        }
        results.append(columns);
    }

    return results;
}

int SqlitePlugin::getCount(Tables table)
{
    switch(table){
        case Articles:{
            QSqlQuery sql("SELECT COUNT(*) FROM `articles`");
            sql.exec();
            if(!sql.next() || sql.lastError().isValid())
                errorStr = sql.lastError().text();
            else
                return sql.value(0).toInt();
            break;
        }
        case Category:{
                QSqlQuery sql("SELECT COUNT(*) FROM `bookcat`");
                sql.exec();
                if(!sql.next() || sql.lastError().isValid())
                    errorStr = sql.lastError().text();
                else
                    return sql.value(0).toInt();
                break;
        }
        default:
            return 0;
            break;
    }
    return 0;
}

QVariantMap SqlitePlugin::getCountAllTables()
{
    QVariantMap result;
    result.insert("articles",getCount(Articles));
    result.insert("bookcat",getCount(Category));
    return result;
}

int SqlitePlugin::getCountAll()
{
    return getCount(Articles) + getCount(Category);
}

void SqlitePlugin::setSynchState(Tables table,int id,bool state)
{
    QSqlQuery sql;
    int synch_state = 0;
    if(state)
        synch_state = 1;
    switch(table){
    case Articles:
        sql.exec("UPDATE `articles` SET  `synch_state` = "+QString::number(synch_state)+" WHERE id="+QString::number(id)+";") ;
        break;
    case Category:
        sql.exec("UPDATE `bookcat` SET  `synch_state` = "+QString::number(synch_state)+" WHERE id="+QString::number(id)+";") ;
        break;
    }
}

void SqlitePlugin::resetSyncState()
{
    QSqlQuery sql;
    sql.exec("UPDATE `articles` SET  `synch_state` = 0") ;
    sql.exec("UPDATE `bookcat` SET  `synch_state` = 0");

}
void SqlitePlugin::backupTables()
{
    QSqlQuery sql;
    sql.exec("DELETE FROM articles_backup;");
    sql.exec("DELETE FROM bookcat_backup;");
    sql.exec("INSERT INTO articles_backup SELECT * FROM articles; ");
    sql.exec("INSERT INTO bookcat_backup SELECT * FROM bookcat;");
}
bool SqlitePlugin::syncCategories(QVariantList categories)
{
    QSqlQuery q;
    QSqlQuery sql;
    sql.exec("BEGIN TRANSACTION");
    sql.exec("DELETE FROM bookcat;");
    q.prepare("INSERT INTO bookcat (id,name,parent) VALUES (?,?,?)");
    QVariantList ids;
    QVariantList names;
    QVariantList parents;
    for (int i = 0; i < categories.size(); ++i) {
        QVariantMap category = categories.at(i).toMap();
        ids << category.value("id");
        names << category.value("name");
        parents << category.value("parent");
     }
    q.addBindValue(ids);
    q.addBindValue(names);
    q.addBindValue(parents);

    if (!q.execBatch()){
          errorStr = q.lastError().text();
          return false;
    }
    sql.exec("COMMIT TRANSACTION");
    return true;
}
void SqlitePlugin::restoreFromBackup(Tables table)
{
    QSqlQuery sql;
    switch(table){
    case Articles:{
        break;
    }
    case Category:{
        sql.exec("DELETE FROM bookcat;");
        sql.exec("INSERT INTO bookcat SELECT * FROM bookcat_backup;");
        sql.exec("INSERT INTO articles SELECT * FROM articles_backup;");
    }
    }
}
bool SqlitePlugin::syncArticle(QVariantMap article)
{
    QSqlQuery sql("SELECT * FROM `articles` WHERE `guid` = '"+article.value("guid","").toString()+"'");
    sql.exec();
    if(sql.lastError().isValid()){
        errorStr = sql.lastError().text();
        return false;
    }
    article.insert("synch_state",1);
    article.insert("catid",article.value("cat_id"));
    if(sql.next()){
        return updateArticle(article);
    }
    else{
       return createArticle(article);
    }
    return false;
}

Q_EXPORT_PLUGIN2(sqliteplugin, SqlitePlugin)
