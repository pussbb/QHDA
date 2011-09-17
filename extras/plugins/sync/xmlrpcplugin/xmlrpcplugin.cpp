#include <xmlrpcplugin.h>

QString XmlRpcPlugin::name(){
    return "Xml-Rpc";
}
QString XmlRpcPlugin::version() {
    return "0.0.0.2";
}

QVariantMap XmlRpcPlugin:: aboutInfo() {
    QVariantMap result;
    return result;
}
void XmlRpcPlugin::start() {
    dialog->show();
}
#include "QDebug"
void XmlRpcPlugin::init(QSettings *bookSettings,DbManagerInterface *interface) {
    dialog = new XmlRpcDialog();
    qDebug()<<interface->version();
}

bool XmlRpcPlugin::isSupportDownload() {
    return true;
}

bool XmlRpcPlugin::isSupportUpload() {
    return true;
}

Q_EXPORT_PLUGIN2(xmlrpcplugin,XmlRpcPlugin)
