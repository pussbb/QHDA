#include "headers/settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_listWidget_itemClicked(QListWidgetItem* item)
{
   /// item->view->row()
    ui->settingswidgets->setCurrentIndex(ui->listWidget->currentRow());
}

void Settings::on_enableProxy_stateChanged(int state)
{
    if(state == 0)
        ui->ProxySettings->setEnabled(false);
    else
        ui->ProxySettings->setEnabled(true);
}
