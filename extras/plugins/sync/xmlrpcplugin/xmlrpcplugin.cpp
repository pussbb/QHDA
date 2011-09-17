#include <xmlrpcplugin.h>

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

    client->setHost( "qhda",80,"/rpc" );
    int x = 5;
    int y =56;
    dialog->setOperationTitle(tr("fdsfdsfds"),true);
    requestIdSum = client->request( "sum", x, y );
    dialog->show();
}
#include "QDebug"
void XmlRpcPlugin::init(QSettings *bookSettings,DbManagerInterface *interface)
{
    __db = interface;
    dialog = new XmlRpcDialog();
    client = new xmlrpc::Client(this);

    dialog->setProgressValues(0,__db->getCountAll());
    connect( client, SIGNAL(done( int, QVariant )),
                     this, SLOT(processReturnValue( int, QVariant )) );
    connect( client, SIGNAL(failed( int, int, QString )),
                     this, SLOT(processFault( int, int, QString )) );
}
void XmlRpcPlugin::processReturnValue( int requestId, QVariant value )
{
    if ( requestId == requestIdSum )
        qDebug()<< value;
}

void XmlRpcPlugin::processFault( int requestId, int errorCode, QString errorString )
{
    Q_UNUSED( requestId );

    qDebug()<< errorCode +  errorString ;

}

bool XmlRpcPlugin::isSupportDownload() {
    return true;
}

bool XmlRpcPlugin::isSupportUpload() {
    return true;
}

Q_EXPORT_PLUGIN2(xmlrpcplugin,XmlRpcPlugin)
