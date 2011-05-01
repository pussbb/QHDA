#ifndef DBMANAGERINTERFACE_H
#define DBMANAGERINTERFACE_H

#include <QString>

class DbManagerInterface
{
public:
    virtual ~DbManagerInterface() {}
    virtual QString version() = 0;
    virtual QString db_driver_name() = 0;
};


QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(DbManagerInterface,
                    "com.pussbb.QHDA.Plugin.DbManagerInterface/0.1");
QT_END_NAMESPACE
#endif
