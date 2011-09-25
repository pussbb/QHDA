#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDebug>


#include <QDialog>
#include <QListWidget>
#include <QSettings>
#include <QDir>
#include <extras/editorinterface.h>
#include <extras/synchronizing.h>
namespace Ui {
    class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();
    QString path;

private slots:
    void on_listWidget_itemClicked(QListWidgetItem* item);

    void on_enableProxy_stateChanged(int );
    void initTemplates();
    void initEditors();
    void initSync();
    void on_buttonBox_rejected();

    void on_templatesList_currentIndexChanged(int index);

    void on_editorsList_currentIndexChanged(int index);

    void on_buttonBox_clicked(QAbstractButton* button);

    void on_syncPluginTo_currentIndexChanged(int index);

    void on_syncPluginFrom_currentIndexChanged(int index);

    void on_authRequired_stateChanged(int arg1);

private:
    Ui::Settings *ui;
    QMap<QString , QSettings*> templates;
    QMap<QString , EditorInterface*> editors;
    QMap<QString, SyncInterface*> syncPlugins;
    EditorInterface* editor;
    SyncInterface* syncFace;
    void saveSettings();
    void loadSettings();
    static QList<QString> agentList_;
};

#endif // SETTINGS_H
