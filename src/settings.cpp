#include "headers/settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
   path = qApp->applicationDirPath()+QDir::toNativeSeparators("/templates/");
    ui->setupUi(this);
    if(ui->userName->text().isEmpty())
        ui->userName->setText(getenv("USER"));
    initTemplates();
    initEditors();
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
{qDebug()<<ui->buttonBox->buttonRole(button);
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

    settings.setValue("Core/proxyConnection",ui->enableProxy->isCheckable());
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
