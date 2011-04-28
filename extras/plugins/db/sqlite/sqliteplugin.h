
#ifndef SQLITEPLUGIN_H
#define SQLITEPLUGIN_H

#include <QObject>
#include "sqliteplugin.h"
#include "../../../dbmanagerinterface.h"


class SqlitePlugin : public QObject, DbManagerInterface
{
    Q_OBJECT
    Q_INTERFACES(DbManagerInterface)

public:
    QString echo(const QString &message);
};


#endif
