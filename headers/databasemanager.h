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
    QMessageBox msgBox;
signals:

public slots:
    bool loadPlugin(QString file = "");
    void showError();
    void setCurrentInterface(QString interfaceName);
    bool saveArticle(QVariantMap article);
private slots:
    void getPluginsList(QString path = "");
    bool newArticle(QVariantMap article);
    bool updateArticle(QVariantMap article);
};

#endif // DATABASEMANAGER_H
