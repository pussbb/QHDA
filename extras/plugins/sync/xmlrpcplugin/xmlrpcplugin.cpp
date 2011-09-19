#include <xmlrpcplugin.h>
#include "QDebug"
QString XmlRpcPlugin::name()
{
    return "Xml-Rpc";
}
QString XmlRpcPlugin::version()
{
    return "0.0.0.2";
}

QVariantMap XmlRpcPlugin:: aboutInfo()
{
    QVariantMap result;
    return result;
}
void XmlRpcPlugin::start() {

///    client->setHost( "qhda",80,"/rpc" );
    int x = 5;
    int y =56;
    dialog->setOperationTitle(tr("fdsfdsfds"),true);
    requestIdSum = client->request( "sum", x, y );
    dialog->show();
}

void XmlRpcPlugin::init(QSettings *bookSettings,DbManagerInterface *interface)
{
    __db = interface;
    dialog = new XmlRpcDialog();
    client = new xmlrpc::Client(this);

    dialog->toLog("fdsfs",XmlRpcDialog::Warning);
    dialog->setProgressValues(0,__db->getCountAll());
    connect( client, SIGNAL(done( int, QVariant )),
                     this, SLOT(processReturnValue( int, QVariant )) );
    connect( client, SIGNAL(failed( int, int, QString )),
                     this, SLOT(processFault( int, int, QString )) );
}
void XmlRpcPlugin::processReturnValue( int requestId, QVariant value )
{
    dialog->progressPlus(3);
    if ( requestId == requestIdSum )
        qDebug()<< value;
}

void XmlRpcPlugin::processFault( int requestId, int errorCode, QString errorString )
{
    dialog->progressPlus(1);
    QString errorMsg = tr("Request id:") + QString::number(requestId) +
            tr(". Code:") + QString::number(errorCode) +
            tr(". Message:")+ errorString;
    dialog->toLog(errorMsg,XmlRpcDialog::Error);
}

bool XmlRpcPlugin::isSupportDownload() {
    return true;
}

bool XmlRpcPlugin::isSupportUpload() {
    return true;
}

Q_EXPORT_PLUGIN2(xmlrpcplugin,XmlRpcPlugin)
