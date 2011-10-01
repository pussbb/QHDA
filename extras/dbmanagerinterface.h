#ifndef DBMANAGERINTERFACE_H
#define DBMANAGERINTERFACE_H

#include <QString>
#include <QMap>
#include <QVariant>
class DbManagerInterface
{
public:
    virtual ~DbManagerInterface() {}
    enum Table{Articles, Category};
    Q_DECLARE_FLAGS(Tables, Table)
    virtual QString version() = 0;
    virtual QString dbDriverName() = 0;
    virtual bool create(QString databaseName = "") = 0;
    virtual bool open(QString databaseName,QMap<QString, QVariant> options ) = 0;
    virtual bool open(QString databaseName) = 0;
    virtual bool isServerType() = 0;
    virtual bool authConection() = 0;
    virtual QMap<QString, QString> defaultAuthOptions() = 0;
    virtual QString defaultConnectionOptions() = 0;
    virtual bool createCategory(QString categoryName, int parent = 0 ) = 0;
    virtual QVariantList categoriesList(int parent = -1,int limit = 0,bool sync = false) = 0;
    virtual QVariantList articlesList(int parent = -1,int limit = 0,bool sync = false) = 0;
    virtual bool deleteCategory(int id) = 0;
    virtual bool deleteArticle(int id) = 0;
    virtual QVariantMap article(int id) = 0;
    virtual bool createArticle(QVariantMap article) = 0;
    virtual bool updateArticle(QVariantMap article) = 0;
    virtual QVariantMap getTableColumnNames(QString tableName) = 0;
    virtual QVariantList search(QString search) = 0;
    // functions for Synchronization
    virtual bool syncCategories(QVariantList categories) = 0;
    virtual bool syncArticle(QVariantMap article) = 0;
    virtual void backupTables() = 0;
    ///virtual void clean
    virtual int getCount(Tables table) = 0;
    virtual void restoreFromBackup(Tables table) = 0;
    virtual QVariantMap getCountAllTables() = 0;
    virtual int getCountAll() = 0;
    virtual void setSynchState(Tables table,int id,bool state) = 0;
    virtual void resetSyncState() = 0;
    // end of functions for Synchronization
    QString errorStr;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(DbManagerInterface::Tables)
QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(DbManagerInterface,
                    "com.pussbb.QHDA.Plugin.DbManagerInterface/0.1");
QT_END_NAMESPACE
#endif
