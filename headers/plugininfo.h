#ifndef PLUGININFO_H
#define PLUGININFO_H

#include <QDialog>
#include <QTreeWidget>

#include <extras/editorinterface.h>
#include <extras/dbmanagerinterface.h>

namespace Ui {
    class PluginInfo;
}

class PluginInfo : public QDialog
{
    Q_OBJECT

public:
    explicit PluginInfo(QWidget *parent = 0);
    ~PluginInfo();

private:
    Ui::PluginInfo *ui;
    void initDbPlugins();
    void initEditors();
  ///  void initSynchPlugins();
};

#endif // PLUGININFO_H
