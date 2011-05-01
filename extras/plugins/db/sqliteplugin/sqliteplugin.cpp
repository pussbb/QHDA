#include <QtGui>
#include "sqliteplugin.h"


/*QString SqlitePlugin::echo(const QString &message)
{
    return message;
}
)*/
QString SqlitePlugin::version()
{
    return "0.0.1";
}
QString SqlitePlugin::db_driver_name()
{
    return "sqlite";
}

Q_EXPORT_PLUGIN2(sqliteplugin, SqlitePlugin);

