#include "settings.h"
#include "ui_settings.h"
#include <QNetworkProxy>
#include <QPixmap>
#include <QFileInfo>
#include <QDir>
#include "QDebug"
#include <QSettings>
Settings::Settings(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::Settings)
{
    ui->setupUi(this);
    /// set proxy
    ui->proxytype->addItem("No-Proxy",QNetworkProxy::NoProxy);
    //  ui->proxytype->addItem("DefaultProxy",QNetworkProxy::DefaultProxy);
    ui->proxytype->addItem("Socks5",QNetworkProxy::Socks5Proxy);
    ui->proxytype->addItem("Http",QNetworkProxy::HttpProxy);
    ui->proxytype->addItem("Http Caching",QNetworkProxy::HttpCachingProxy);
    ui->proxytype->addItem("Ftp Caching",QNetworkProxy::FtpCachingProxy);
    //
    ui->proxyport->setEnabled(false);
    ui->proxyurl->setEnabled(false);
    QImage image(QApplication::applicationDirPath()+"/Templates/blueblog.png");

    ui->image->setPixmap(QPixmap::fromImage(image));
    ui->image->setScaledContents(true);

    QDir currentDir =QDir(QApplication::applicationDirPath()+"/Templates/");
    QStringList files;
    files = currentDir.entryList(QStringList("*.png"),
                                 QDir::Files | QDir::NoSymLinks);
    ui->image->setPixmap(QPixmap::fromImage(QImage(":/htmlpage/default/default.png")));
    ui->themesbox->addItem("default","default");
    QFileInfo fi;
    for(int i=0;i<files.count();i++)
    {  fi.setFile(QApplication::applicationDirPath()+"/Templates/",files.at(i));
        ui->themesbox->addItem(fi.baseName(),fi.baseName());
    }

    Settings::init_data();
}
void Settings::init_data()
{
    QSettings setting;
    setting.endGroup();
    setting.beginGroup("main");
    ui->username->setText(setting.value("username","anonymous").toString());
    ui->themesbox->setCurrentIndex(ui->themesbox->findText(setting.value("htmltheme","default").toString()));
    setting.endGroup();
    setting.beginGroup("web");
    switch (setting.value("proxytype").toInt())
    {
    case 0: ui->proxytype->setCurrentIndex(ui->proxytype->findData(QNetworkProxy::NoProxy));break;
    case 1: ui->proxytype->setCurrentIndex(ui->proxytype->findData(QNetworkProxy::Socks5Proxy));break;
    case 3: ui->proxytype->setCurrentIndex(ui->proxytype->findData(QNetworkProxy::HttpProxy));break;
    case 4: ui->proxytype->setCurrentIndex(ui->proxytype->findData(QNetworkProxy::HttpCachingProxy));break;
    case 5: ui->proxytype->setCurrentIndex(ui->proxytype->findData(QNetworkProxy::FtpCachingProxy));break;
    }
    ui->proxypass->setText(setting.value("proxyuserpass").toString());
    ui->proxyport->setValue(setting.value("proxyport").toInt());
    ui->proxyurl->setText(setting.value("proxyurl").toString());
    ui->proxyuser->setText(setting.value("proxyuser").toString());
    ui->sbport->setValue(setting.value("xmlrpcport",80).toInt());
    ui->sburi->setText(setting.value("xmlrpcuri","/").toString());
    ui->sburl->setText(setting.value("xmlrpcurl","qhda.krabik.co.ua").toString());
    setting.endGroup();

}

Settings::~Settings()
{
    delete ui;
}

void Settings::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Settings::on_buttonBox_clicked(QAbstractButton* button)
{
    if(ui->buttonBox->buttonRole(button)==QDialogButtonBox::ApplyRole )
    {//||     ui->buttonBox->buttonRole(button)==QDialogButtonBox::AcceptRole
        qDebug()<<"apply";
        QSettings setting;
        setting.beginGroup("main");
        setting.setValue("username",ui->username->text().isEmpty()?"anonymous":ui->username->text());
        setting.setValue("htmltheme",ui->themesbox->itemData(ui->themesbox->currentIndex(),32));
        setting.endGroup();
        setting.beginGroup("web");
        //if(ui->proxytype->currentIndex()!=0)
        // {
        setting.setValue("proxytype",ui->proxytype->itemData(ui->proxytype->currentIndex(),32));
        setting.setValue("proxyurl",ui->proxyurl->text());
        setting.setValue("proxyport",ui->proxyport->text());
        setting.setValue("proxyuser",ui->proxyuser->text());
        setting.setValue("proxyuserpass",ui->proxypass->text());
        // }
        setting.setValue("xmlrpcurl",ui->sburl->text());
        setting.setValue("xmlrpcport",ui->sbport->text());
        setting.setValue("xmlrpcuri",ui->sburi->text());
        setting.endGroup();
        ///Settings::close();
        // button->setEnabled(false);
    }
    ///button->
}

void Settings::on_listWidget_itemClicked(QListWidgetItem* item)
{
    ui->stackedWidget->setCurrentIndex(ui->listWidget->row(item));

}

void Settings::on_proxytype_currentIndexChanged(int index)
{
    if(index==0)
    {
        ui->proxyport->setEnabled(false);
        ui->proxyurl->setEnabled(false);
    }
    else
    {
        ui->proxyport->setEnabled(true);
        ui->proxyurl->setEnabled(true);
    }
}

void Settings::on_themesbox_currentIndexChanged(int index)
{ if(index==0)  ui->image->setPixmap(QPixmap::fromImage(QImage(":/htmlpage/default/default.png")));
    else  ui->image->setPixmap(QPixmap::fromImage(QImage(QApplication::applicationDirPath()+"/Templates/"+ui->themesbox->currentText()+".png")));
}
