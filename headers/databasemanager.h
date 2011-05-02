#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include "extras/dbmanagerinterface.h"
#include "QDir"
#include "QtCore"
class DataBaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DataBaseManager(QObject *parent = 0);
    DbManagerInterface *interface;
    QMap<QString , DbManagerInterface*> plugins;
signals:

public slots:
    bool load_plugin(QString file = "");
private slots:
    void get_plugins_list(QString path = "");
};

#endif // DATABASEMANAGER_H
