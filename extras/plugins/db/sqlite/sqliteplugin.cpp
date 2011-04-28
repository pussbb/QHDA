#include <QtGui>
#include "sqliteplugin.h"


QString SqlitePlugin::echo(const QString &message)
{
    return message;
}

Q_EXPORT_PLUGIN2(sqliteplugin, SqlitePlugin);

