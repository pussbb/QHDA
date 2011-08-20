#include "headers/settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
   path = qApp->applicationDirPath()+QDir::toNativeSeparators("/templates/");
    ui->setupUi(this);

    initTemplates();
    initEditors();
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

void Settings::on_buttonBox_rejected()
{
    reject();
}

void Settings::on_templatesList_currentIndexChanged(int index)
{
   QString templateFile =  ui->templatesList->itemData(index,Qt::UserRole).toString();

  QString screenshot = templates.value(templateFile)->value("Template/Screenshot").toString();
  qDebug()<< path + screenshot;
  ui->templateScreenshot->setPixmap(
              QPixmap(path + screenshot)
              );
  QString description;
  description.append( tr("Author: ")+templates.value(templateFile)->value("Template/Author").toString());
  description.append( "\n" + tr("Description: ")+templates.value(templateFile)->value("Template/Description").toString());
  ///ui->templateDescription->setTextFormat(Qt::RichText);
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
    ui->templatesList->setCurrentIndex(index);

    index = ui->editorsList->findData(settings.value("Editors/file"));
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
}
