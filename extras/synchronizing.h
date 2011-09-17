#ifndef SYNCINTERFACE_H
#define SYNCINTERFACE_H
#include <QString>

#include <QtNetwork/QNetworkProxy>
#include <QtCore>
#include "dbmanagerinterface.h"
class SyncInterface
{
public:
    virtual ~SyncInterface() {}
    virtual QString version() = 0;
    virtual QString name() = 0;
    virtual QVariantMap aboutInfo() = 0;
    virtual void init(QSettings *bookSettings,DbManagerInterface *interface) = 0;
    virtual bool isSupportDownload() = 0 ;
    virtual bool isSupportUpload() = 0 ;
    virtual void start() = 0;
    QString errorStr;
    QNetworkProxy proxy;
    QString host;
    QString hostPath;
    QString hostPort;
    QString userName;
    QString userPassword;
};

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(SyncInterface,
                    "com.pussbb.QHDA.Plugin.SyncInterface/0.1");
QT_END_NAMESPACE
#endif // SYNCINTERFACE_H
