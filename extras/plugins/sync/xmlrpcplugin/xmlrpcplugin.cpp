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
void XmlRpcPlugin::setUserAgent(QString agent)
{
    client->setUserAgent(agent);
}

void XmlRpcPlugin::start(QSettings *bookSettings,DbManagerInterface *interface,SyncTypes syncType)
{
    __db = interface;
    dialog->clear();
    dialog->setProgressValues(0,__db->getCountAll());
    dialog->setOperationTitle(tr("Check for user permission"),true);
    QMap<QString,xmlrpc::Variant> book;
    book.insert("bookName",bookSettings->value("General/Bookname","").toString());
    book.insert("bookDescription",bookSettings->value("General/BookDescr","").toString());
    book.insert("bookImage",bookSettings->value("General/BookIcon","").toString());
    book.insert("userName",_userName);
    book.insert("apiKey",_apiKey);

    if(!bookSettings->value("Tmp/settingFilePath","").isNull()) {
        QString image_file = bookSettings->value("Tmp/settingFilePath","").toString() +
                                    bookSettings->value("General/BookIcon","").toString();
        QImage image(QIcon(image_file).pixmap(36,36).toImage());
        QByteArray byteArray;
        QBuffer buffer(&byteArray);
        image.save(&buffer, "PNG"); // writes the image in PNG format inside the buffer
        book.insert("image",byteArray.toBase64());
    }
    else{
        book.insert("image",(QString)"");
    }
    requestIdItem = client->request("qhda.bookcheck",book);
    dialog->show();
}

void XmlRpcPlugin::setHost(QString host, int port, QString path)
{
    client->setHost(host,port,path);
}

void XmlRpcPlugin::setProxy(QNetworkProxy proxy)
{
    client->setProxy(proxy.hostName(),proxy.port(),proxy.user(),proxy.password());
}

void XmlRpcPlugin::authAccess(QString userName, QString userPassword)
{
     client->setUser(userName,userPassword);
}

void XmlRpcPlugin::init(QString userName,QString apiKey)
{
    dialog = new XmlRpcDialog();
    client = new xmlrpc::Client();
    _userName = userName;
    _apiKey = apiKey;
    connect( client, SIGNAL(done( int, QVariant )),
                     this, SLOT(processReturnValue( int, QVariant )) );
    connect( client, SIGNAL(failed( int, int, QString )),
                     this, SLOT(processFault( int, int, QString )) );
}
void XmlRpcPlugin::processReturnValue( int requestId, QVariant value )
{
    dialog->progressPlus(3);
    if ( requestId == requestIdItem )
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

bool XmlRpcPlugin::isSupportDownload()
{
    return true;
}

bool XmlRpcPlugin::isSupportUpload()
{
    return true;
}

Q_EXPORT_PLUGIN2(xmlrpcplugin,XmlRpcPlugin)
