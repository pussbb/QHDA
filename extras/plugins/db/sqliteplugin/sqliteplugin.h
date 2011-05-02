
#ifndef SQLITEPLUGIN_H
#define SQLITEPLUGIN_H

#include <QObject>
#include "sqliteplugin.h"
#include "../../../dbmanagerinterface.h"
#include <QtSql/QtSql>


class SqlitePlugin : public QObject, DbManagerInterface
{
    Q_OBJECT
    Q_INTERFACES(DbManagerInterface)

public:
    QString version();
    QString db_driver_name();
    bool create(QString file = "");
    bool open(QString connection,QMap<QString, QString> options );
    bool open(QString connection );
    bool auth_conection() ;
    QMap<QString, QString> default_auth_options();
    QString default_connection_options();
private:
    QSqlDatabase db;

};


#endif
