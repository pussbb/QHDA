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
    void start(QSettings *bookSettings,DbManagerInterface *interface,SyncTypes syncType);
    void init(QString userName,QString apiKey);
    bool isSupportDownload();
    bool isSupportUpload();
    void setUserAgent(QString agent);
    QString errorStr;
    void setProxy(QNetworkProxy proxy);
    void setHost(QString host,int port,QString path);
    void authAccess(QString userName,QString userPassword);
private slots:
    void processReturnValue( int requestId, QVariant value );
    void processFault( int requestId, int errorCode, QString errorString );
    void uploadBook(QSettings *bookSettings);
    void proccedUploadElements();
    void proccedDownloadElements();
    void downloadBook(QSettings *bookSettings);
private:
    DbManagerInterface *__db;
    xmlrpc::Client *client;
    int bookId;
    int catId;
    int articleId;
    int serverBookId;
    int catStatus;
    int _currentType;
    QString _userName;
    QString _apiKey;
    int category_id;
    QHash<QString, int> categories;

};
#endif
