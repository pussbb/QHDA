#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDebug>


#include <QDialog>
#include <QListWidget>
#include <QSettings>
#include <QDir>
#include <extras/editorinterface.h>
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
    void on_buttonBox_rejected();

    void on_templatesList_currentIndexChanged(int index);

    void on_editorsList_currentIndexChanged(int index);

    void on_buttonBox_clicked(QAbstractButton* button);

private:
    Ui::Settings *ui;
    QMap<QString , QSettings*> templates;
    QMap<QString , EditorInterface*> editors;
    EditorInterface* editor;
    void saveSettings();
};

#endif // SETTINGS_H
