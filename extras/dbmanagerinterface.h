#ifndef DBMANAGERINTERFACE_H
#define DBMANAGERINTERFACE_H

#include <QString>
#include <QMap>
#include <QVariant>
class DbManagerInterface
{
public:
    virtual ~DbManagerInterface() {}
    virtual QString version() = 0;
    virtual QString db_driver_name() = 0;
    virtual bool create(QString databaseName = "") = 0;
    virtual bool open(QString databaseName,QMap<QString, QVariant> options ) = 0;
    virtual bool open(QString databaseName) = 0;
    virtual bool is_server_type() = 0;
    virtual bool auth_conection() = 0;
    virtual QMap<QString, QString> default_auth_options() = 0;
    virtual QString default_connection_options() = 0;
    QString error_str;
};


QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(DbManagerInterface,
                    "com.pussbb.QHDA.Plugin.DbManagerInterface/0.1");
QT_END_NAMESPACE
#endif
