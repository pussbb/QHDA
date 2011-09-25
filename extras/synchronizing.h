#ifndef SYNCINTERFACE_H
#define SYNCINTERFACE_H
#include <QString>

#include <QtNetwork/QNetworkProxy>
#include <QtCore>
#include "dbmanagerinterface.h"
class SyncInterface
{
public:
    enum SyncType {Upload,Download};
    virtual ~SyncInterface() {};
    Q_DECLARE_FLAGS(SyncTypes, SyncType);
    virtual QString version() = 0;
    virtual QString name() = 0;
    virtual QVariantMap aboutInfo() = 0;
    virtual void init(QString userName,QString apiKey) = 0;
    virtual bool isSupportDownload() = 0 ;
    virtual bool isSupportUpload() = 0 ;
    virtual void start(QSettings *bookSettings,DbManagerInterface *interface,SyncTypes syncType) = 0;
    virtual void setProxy(QNetworkProxy proxy) =0;
    virtual void setUserAgent(QString agent) = 0;
    virtual void setHost(QString host,int port,QString path) =0;
    virtual void authAccess(QString userName,QString userPassword) = 0 ;
    QString errorStr;
};
Q_DECLARE_OPERATORS_FOR_FLAGS(SyncInterface::SyncTypes);
QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(SyncInterface,
                    "com.pussbb.QHDA.Plugin.SyncInterface/0.1");
QT_END_NAMESPACE
#endif // SYNCINTERFACE_H
