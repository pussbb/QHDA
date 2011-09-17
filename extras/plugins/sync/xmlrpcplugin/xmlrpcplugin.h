#ifndef XMLRPCPLUGIN_H
#define XMLRPCPLUGIN_H

#include <QObject>
#include "../../../synchronizing.h"
#include "../../../dbmanagerinterface.h"
#include "xmlrpcdialog.h"
#include "xmlrpc/client.h"
class XmlRpcPlugin : public QObject, SyncInterface
{
    Q_OBJECT
    Q_INTERFACES(SyncInterface)

public:
    QString version();
    QString name();
    QVariantMap aboutInfo();
    XmlRpcDialog *dialog;
    void start();
    void init(QSettings *bookSettings,DbManagerInterface *interface);
    bool isSupportDownload();
    bool isSupportUpload();
    QString errorStr;
    QNetworkProxy proxy;
    QString host;
    QString hostPath;
    QString hostPort;
    QString userName;
    QString userPassword;
private slots:
    void processReturnValue( int requestId, QVariant value );
    void processFault( int requestId, int errorCode, QString errorString );
private:
    DbManagerInterface *__db;
    QSettings *__bookSettings;
    xmlrpc::Client *client;
    int requestIdSum;
};
#endif
