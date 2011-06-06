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
    bool createCategory(int parent = 0 );

private:
    QSqlDatabase db;

};


#endif
