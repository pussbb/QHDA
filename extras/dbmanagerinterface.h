#ifndef DBMANAGERINTERFACE_H
#define DBMANAGERINTERFACE_H

#include <QString>
#include <QMap>
class DbManagerInterface
{
public:
    virtual ~DbManagerInterface() {}
    virtual QString version() = 0;
    virtual QString db_driver_name() = 0;
    virtual bool create(QString file = "") = 0;
    virtual bool open(QString databasename,QMap<QString, QString> options ) = 0;
    virtual bool open(QString databasename) = 0;
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
