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
    virtual QString dbDriverName() = 0;
    virtual bool create(QString databaseName = "") = 0;
    virtual bool open(QString databaseName,QMap<QString, QVariant> options ) = 0;
    virtual bool open(QString databaseName) = 0;
    virtual bool isServerType() = 0;
    virtual bool authConection() = 0;
    virtual QMap<QString, QString> defaultAuthOptions() = 0;
    virtual QString defaultConnectionOptions() = 0;
    virtual bool createCategory(int parent = 0) = 0;
    QString errorStr;
};


QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(DbManagerInterface,
                    "com.pussbb.QHDA.Plugin.DbManagerInterface/0.1");
QT_END_NAMESPACE
#endif
