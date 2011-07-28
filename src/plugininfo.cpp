#include "headers/plugininfo.h"
#include "ui_plugininfo.h"

PluginInfo::PluginInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PluginInfo)
{
    ui->setupUi(this);
    initDbPlugins();
    initEditors();
}

PluginInfo::~PluginInfo()
{
    delete ui;
}
void PluginInfo::initDbPlugins()
{
    QTreeWidgetItem *parent = new QTreeWidgetItem(ui->treePlugins);
    parent->setText(0,tr("DataBase Engines"));
    QString editorsPath = qApp->applicationDirPath()+QDir::toNativeSeparators("/plugins/db/");
    QDir pluginsDir(editorsPath);
    QString text;
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();
        if (plugin) {
            DbManagerInterface* db = qobject_cast<DbManagerInterface *>(plugin);
            QTreeWidgetItem *item = new QTreeWidgetItem(parent);
            text.append(db->dbDriverName());
            text.append(" " + tr("Version:") + db->version());
            if(db->isServerType())
                text.append(" " + tr("Server Type: ") + tr("Yes"));
            else
                text.append(" " + tr("Server Type: ") + tr("No"));
            item->setText(0,text);
        }
    }
}

void PluginInfo::initEditors()
{
    QTreeWidgetItem *parent = new QTreeWidgetItem(ui->treePlugins);
    parent->setText(0,tr("Editors"));
    QString editorsPath = qApp->applicationDirPath()+QDir::toNativeSeparators("/plugins/editor/");
    QDir pluginsDir(editorsPath);
    QString text;
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();
        if (plugin) {
            EditorInterface * editor = qobject_cast<EditorInterface *>(plugin);
            QTreeWidgetItem *item = new QTreeWidgetItem(parent);
            text.append(editor->name());
            text.append(" " + tr("Version:") + editor->version());
            text.append(" " + tr("Editor Type: ") + editor->editorType());
            item->setText(0,text);
        }
    }
}
