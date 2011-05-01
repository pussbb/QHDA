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
signals:

public slots:

private slots:

};

#endif // DATABASEMANAGER_H
