#ifndef SQLITEPLUGIN_H
#define SQLITEPLUGIN_H

#include <QObject>
#include "../../../dbmanagerinterface.h"
#include <QtSql/QtSql>


class SqlitePlugin : public QObject, DbManagerInterface
{
    Q_OBJECT
    Q_INTERFACES(DbManagerInterface)

public:
    QString version();
    QString dbDriverName();
    bool create(QString databaseName = "");
    bool open(QString databaseName,QMap<QString, QVariant> options );
    bool open(QString databaseName );
    bool isServerType();
    bool authConection() ;
    QMap<QString, QString> defaultAuthOptions();
    QString defaultConnectionOptions();
    bool createCategory(QString categoryName, int parent = 0 );
    QVariantList categoriesList(int parent = -1);
    QVariantList articlesList(int parent = -1);
    bool deleteCategory(int id);
    bool deleteArticle(int id);
    bool createArticle(QVariantMap article);
    QVariantMap article(int id);
    QVariantMap articlesColumns;
    QVariantMap getTableColumnNames(QString tableName);
    bool updateArticle(QVariantMap article);
    QVariantList search(QString search);
    // functions for Synchronization
    ///enum synchType {Import,Export};
    int getCount(QString tableIndetifer);
    QVariantMap getCountAllTables();
    int getCountAll();
    bool setSynchState(QString tableIndetifer,int fieldId,synchType type,bool state);
    bool resetSyncState();
    // end of functions for Synchronization
private:
    QSqlDatabase db;
    void createTableColumnsNames();
};


#endif
