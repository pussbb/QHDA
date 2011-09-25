#include "headers/settings.h"
#include "ui_settings.h"

QList<QString> Settings::agentList_ = QList<QString> ()
    << "QHDA"
    << "Opera/9.63 (Windows NT 6.0; U; ru) Presto/2.1.1"
    << "Opera/9.80 (X11; Linux i686; U; ru) Presto/2.6.30 Version/10.61"
    << "Opera/9.80 (Windows NT 6.1; U; it) Presto/2.6.30 Version/10.63"
    << "Opera/9.80 (Windows NT 5.1; U; en) Presto/2.6.37 Version/11.00"
    << "Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.9.1) Gecko/20090624 Firefox/3.5"
    << "Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US) AppleWebKit/534.6 (KHTML like Gecko) Chrome/7.0.503.0 Safari/534.6"
    << "Mozilla/5.0 (Windows; U; Windows NT 5.1; pl; rv:1.9.2.11) Gecko/20101012 Firefox/3.6.11"
    << "Mozilla/5.0 (Windows; U; Windows NT 5.1; it; rv:1.9.0.16) Gecko/2010021013 Firefox/3.0.16 Flock/2.5.6"
    << "Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US) AppleWebKit/534.7 (KHTML like Gecko) Chrome/7.0.517.41 Safari/534.7"
    << "Mozilla/5.0 (Windows; U; Windows NT 5.1; cs; rv:1.9.1.14) Gecko/20101001 Firefox/3.5.14"
    << "Mozilla/5.0 (Windows; U; Windows NT 6.0; en-US; rv:1.7.13) Gecko/20050610 K-Meleon/0.9"
    << "Mozilla/5.0 (Windows; U; Windows NT 6.1; en-GB; rv:1.9.2.10) Gecko/20100914 Firefox/3.6.10"
    << "Mozilla/5.0 (Windows; U; Windows NT 6.1; de; rv:1.9.2.11) Gecko/20101012 AskTbSPC2/3.8.0.12304 Firefox/3.6.11"
    << "Mozilla/5.0 (Windows; U; Windows NT 6.1; de-DE) AppleWebKit/533.18.1 (KHTML like Gecko) Version/5.0.2 Safari/533.18.5"
    << "Mozilla/5.0 (Windows NT 5.1; U; en; rv:1.9.1.6) Gecko/20091201 Firefox/3.5.6"
    << "Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.0; WOW64; SLCC1; .NET CLR 2.0.50727; .NET CLR 3.0.04506; Media Center PC 5.0)"
    << "Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.1; Trident/4.0)"
    << "Mozilla/5.0 (Macintosh; U; Intel Mac OS X 10_5_6; en-us) AppleWebKit/525.27.1 (KHTML like Gecko) Version/3.2.1 Safari/525.27.1"
    << "Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.8.1.2) Gecko/20070221 SeaMonkey/1.1.1"
    << "Mozilla/5.0 (X11; U; Linux i686 (x86_64); en-US; rv:1.8.1.6) Gecko/2007072300 Iceweasel/2.0.0.6 (Debian-2.0.0.6-0etch1+lenny1)"
    << "Mozilla/5.0 (X11; U; Linux x86_64; en-US) AppleWebKit/534.10 (KHTML like Gecko) Chrome/8.0.552.11 Safari/534.10"
    << "Mozilla/5.0 (X11; U; Linux x86_64; de; rv:1.9.2.11) Gecko/20101013 Ubuntu/10.10 (maverick) Firefox/3.6.11"
    << "Mozilla/5.0 (X11; U; Linux i686; it; rv:1.9.2.10) Gecko/20100915 Ubuntu/10.04 (lucid) Firefox/3.6.10 GTB7.1"
    << "Mozilla/5.0 (X11; U; Linux i686; it-it) AppleWebKit/531.2+ (KHTML like Gecko) Safari/531.2+ Epiphany/2.30.6"
    << "Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.9.2.11) Gecko/20101013 Ubuntu/10.04 (lucid) Firefox/3.6.11"
    << "Mozilla/5.0 (compatible; Konqueror/3.5; Linux) KHTML/3.5.5 (like Gecko) (Debian|Debian)"
    << "Mozilla/5.0 (Linux; U; Android 2.1-update1; ru-ru; GT-I9000 Build/ECLAIR) AppleWebKit/530.17 (KHTML like Gecko) Version/4.0 Mobile Safari/530.17"
    << "Mozilla/5.0 (Macintosh; U; Intel Mac OS X 10_6_4; en-us) AppleWebKit/533.18.1 (KHTML like Gecko) Version/5.0.2 Safari/533.18.5"
    << "Mozilla/5.0 (Macintosh; U; Intel Mac OS X 10.6; it; rv:1.9.2.11) Gecko/20101012 Firefox/3.6.11";

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    path = qApp->applicationDirPath()+QDir::toNativeSeparators("/templates/");
    ui->setupUi(this);

    initTemplates();
    initEditors();
    initSync();
    loadSettings();
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_listWidget_itemClicked(QListWidgetItem* item)
{
    Q_UNUSED(item);
    ui->settingswidgets->setCurrentIndex(ui->listWidget->currentRow());
}

void Settings::on_enableProxy_stateChanged(int state)
{
    if(state == 0)
        ui->ProxySettings->setEnabled(false);
    else
        ui->ProxySettings->setEnabled(true);
}

void Settings::initTemplates()
{
    QDir templatesDir(path);
    templatesDir.setNameFilters(QStringList()<<"*.ini");
    foreach (QString fileName, templatesDir.entryList(QDir::Files)) {
        templates.insert(fileName,new QSettings(path
                                                +fileName,QSettings::IniFormat));
        ui->templatesList->addItem(templates.value(fileName)->value("Template/Name").toString(),fileName);
    }
}
void Settings::initSync()
{
    ui->agentList->insertItems(0,agentList_);
    QString editorsPath = qApp->applicationDirPath()+QDir::toNativeSeparators("/plugins/sync/");
    QDir pluginsDir(editorsPath);
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();
        if (plugin) {
            syncFace = qobject_cast<SyncInterface *>(plugin);
            syncPlugins.insert(fileName,syncFace);
            if(syncFace->isSupportUpload())
                    ui->syncPluginTo->addItem(syncFace->name(),fileName);
            if(syncFace->isSupportDownload())
                    ui->syncPluginFrom->addItem(syncFace->name(),fileName);
        }
    }
}

void Settings::on_buttonBox_rejected()
{
    reject();
}

void Settings::on_templatesList_currentIndexChanged(int index)
{
    if(index == -1)
            return;
    QString templateFile =  ui->templatesList->itemData(index,Qt::UserRole).toString();
    QSettings* templateInfo = templates.value(templateFile);
    if(templateInfo == NULL)
        return;
    QString screenshot = templateInfo->value("Template/Screenshot").toString();

      ui->templateScreenshot->setPixmap(
                  QPixmap(path + screenshot)
                  );

    QString description;
    description.append( tr("Author: ")+templateInfo->value("Template/Author").toString());
    description.append( "\n" + tr("Description: ")+templateInfo->value("Template/Description").toString());
    ui->templateDescription->setText(description);
}

void Settings::initEditors()
{
    QString editorsPath = qApp->applicationDirPath()+QDir::toNativeSeparators("/plugins/editor/");
    QDir pluginsDir(editorsPath);
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();
        if (plugin) {
            editor = qobject_cast<EditorInterface *>(plugin);
            editors.insert(fileName,editor);
            ui->editorsList->addItem(editor->name(),fileName);
        }
    }
}

void Settings::on_editorsList_currentIndexChanged(int index)
{
    if(index == -1)
        return;
    QString editorFile =  ui->editorsList->itemData(index,Qt::UserRole).toString();
    QString description;
    description.append(tr("Editor type: ")+ editors.value(editorFile)->editorType());
    description.append("\n" + tr("Verision: ") + editors.value(editorFile)->version());
    ui->editorsDescription->setText(description);
}

void Settings::on_buttonBox_clicked(QAbstractButton* button)
{
    if( ui->buttonBox->buttonRole(button) == QDialogButtonBox::ApplyRole) {
        saveSettings();
    }
    else if (ui->buttonBox->buttonRole(button) == QDialogButtonBox::AcceptRole) {
        saveSettings();
        accept();
    }
}

void Settings::saveSettings()
{
    QSettings settings;
    settings.setValue("Core/save_locale",ui->saveLang->isChecked());
    settings.setValue("Core/saveWindowLayout",ui->saveWindowState->isChecked());
    settings.setValue("Core/username",ui->userName->text());
    settings.setValue("Core/checkUpdates",ui->checkUpdates->isChecked());
    settings.setValue("Core/checkSync",ui->checkSync->isChecked());
    settings.setValue("Core/lastBook",ui->lastBook->isChecked());
    settings.setValue("Core/newTab",ui->newTab->isChecked());

    settings.setValue("Templates/name",ui->templatesList->currentText());
    settings.setValue("Templates/file",ui->templatesList->itemData(
                            ui->templatesList->currentIndex(),
                            Qt::UserRole
                          ));

    settings.setValue("Editors/name",ui->editorsList->currentText());
    settings.setValue("Editors/file",ui->editorsList->itemData(
                          ui->editorsList->currentIndex(),
                          Qt::UserRole
                          ));

    settings.setValue("Core/proxyConnection",ui->enableProxy->isChecked());
    if(ui->enableProxy->isCheckable()) {
        if(ui->systemProxy->isChecked())
            settings.setValue("Proxy/system",true);
        else
            settings.setValue("Proxy/system",false);

        settings.setValue("Proxy/Type",ui->proxyType->currentIndex());
        settings.setValue("Proxy/Url",ui->proxyUrl->text());
        settings.setValue("Proxy/Port",ui->proxyPort->text());
        settings.setValue("Proxy/Username",ui->proxyUserName->text());
        settings.setValue("Proxy/Password",ui->proxyPassword->text());
    }
    // Synchronizing option
    settings.setValue("Synchronizing/apiKey",ui->apiKey->text());
    settings.setValue("Synchronizing/userAgent",ui->agentList->currentText());
    settings.setValue("Synchronizing/pluginToRemote",ui->syncPluginTo->itemData(ui->syncPluginTo->currentIndex(),Qt::UserRole));
    settings.setValue("Synchronizing/pluginFromRemote",ui->syncPluginFrom->itemData(ui->syncPluginFrom->currentIndex(),Qt::UserRole));
    settings.setValue("Synchronizing/host",ui->syncHost->text());
    settings.setValue("Synchronizing/port",ui->synchPort->value());
    settings.setValue("Synchronizing/path",ui->syncPath->text());
    settings.setValue("Synchronizing/isAuth",ui->authRequired->isChecked());
    settings.setValue("Synchronizing/authUserName",ui->authUserName->text());
    settings.setValue("Synchronizing/authPassword",ui->authPassword->text());


}
void Settings::loadSettings()
{
    QSettings settings;
    ui->saveLang->setChecked(settings.value("Core/save_locale",false).toBool());
    ui->saveWindowState->setChecked(settings.value("Core/saveWindowLayout",false).toBool());
    ui->userName->setText(settings.value("Core/username",getenv("USER")).toString());
    ui->checkSync->setChecked(settings.value("Core/checkSync",true).toBool());
    ui->checkUpdates->setChecked(settings.value("Core/checkUpdates",true).toBool());
    ui->lastBook->setChecked(settings.value("Core/lastBook",false).toBool());
    ui->newTab->setChecked(settings.value("Core/newTab",false).toBool());

    int index = ui->templatesList->findData(settings.value("Templates/file"));
    if(index >= 0)
        ui->templatesList->setCurrentIndex(index);

    index = ui->editorsList->findData(settings.value("Editors/file"));
    if(index >= 0)
        ui->editorsList->setCurrentIndex(index);

    ui->enableProxy->setChecked(settings.value("Core/proxyConnection",false).toBool());
    if(settings.value("Proxy/system",false).toBool())
        ui->systemProxy->setChecked(true);
    else
        ui->customProxy->setChecked(true);
    ui->proxyType->setCurrentIndex(settings.value("Proxy/Type",0).toInt());
    ui->proxyUrl->setText(settings.value("Proxy/Url","").toString());
    ui->proxyPort->setValue(settings.value("Proxy/Port",2000).toInt());
    ui->proxyUserName->setText(settings.value("Proxy/Username").toString());
    ui->proxyPassword->setText(settings.value("Proxy/Password").toString());
   // ui->checkUpdates->setChecked();
    //synchronizing options
    ui->apiKey->setText(settings.value("Synchronizing/apiKey","").toString());

    index = ui->agentList->findText(settings.value("Synchronizing/userAgent","").toString());
    if(index >= 0)
        ui->agentList->setCurrentIndex(index);

    index = ui->syncPluginTo->findData(settings.value("Synchronizing/pluginToRemote",""));
    if(index >= 0)
        ui->syncPluginTo->setCurrentIndex(index);

    index = ui->syncPluginFrom->findData(settings.value("Synchronizing/pluginFromRemote"));
    if(index >= 0)
        ui->syncPluginFrom->setCurrentIndex(index);

    ui->syncHost->setText(settings.value("Synchronizing/host","").toString());
    ui->synchPort->setValue(settings.value("Synchronizing/port",80).toInt());
    ui->syncPath->setText(settings.value("Synchronizing/path","").toString());
    ui->authRequired->setChecked(settings.value("Synchronizing/isAuth",false).toBool());
    ui->authUserName->setText(settings.value("Synchronizing/authUserName","").toString());
    ui->authPassword->setText(settings.value("Synchronizing/authPassword","").toString());

}

void Settings::on_syncPluginTo_currentIndexChanged(int index)
{
    if(index == -1)
        return;
    QString syncFile =  ui->syncPluginTo->itemData(index,Qt::UserRole).toString();
    ui->syncPluginToVersion->setText(syncPlugins.value(syncFile)->version());
}

void Settings::on_syncPluginFrom_currentIndexChanged(int index)
{
    if(index == -1)
        return;
    QString syncFile =  ui->syncPluginFrom->itemData(index,Qt::UserRole).toString();
    ui->syncPluginFromVersion->setText(syncPlugins.value(syncFile)->version());
}

void Settings::on_authRequired_stateChanged(int arg1)
{
    if(arg1 == 0) {
        ui->authPassword->setEnabled(false);
        ui->authUserName->setEnabled(false);
    }
    else {
        ui->authPassword->setEnabled(true);
        ui->authUserName->setEnabled(true);
    }
}
