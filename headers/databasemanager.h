#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include "extras/dbmanagerinterface.h"
#include "QDir"
#include "QtCore"
#include <QMessageBox>
class DataBaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DataBaseManager(QObject *parent = 0);
    DbManagerInterface *interface;
    QMap<QString , DbManagerInterface*> plugins;
signals:

public slots:
    bool loadPlugin(QString file = "");
    void showError();
    void setCurrentInterface(QString interfaceName);
private slots:
    void getPluginsList(QString path = "");
};

#endif // DATABASEMANAGER_H
