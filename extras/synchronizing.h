#ifndef SYNCINTERFACE_H
#define SYNCINTERFACE_H
#include <QString>
#include <QtGui>
class SyncInterface
{
public:
    virtual ~SyncInterface() {}
    virtual QString version() = 0;
    virtual QString name() = 0;
    virtual QVariantMap aboutInfo() = 0;
    QString errorStr;
};

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(SyncInterface,
                    "com.pussbb.QHDA.Plugin.SyncInterface/0.1");
QT_END_NAMESPACE
#endif // SYNCINTERFACE_H
