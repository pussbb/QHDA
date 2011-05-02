#include "headers/bookwizard.h"
#include "ui_bookwizard.h"
#include <QDebug>
BookWizard::BookWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::BookWizard)
{

    ui->setupUi(this);
}

BookWizard::~BookWizard()
{
    delete ui;
}

bool BookWizard::init_db_plugins_list(QMap<QString, DbManagerInterface *> plugins)
{
    dbplugins = plugins;
    if(plugins.count() == 0)
    {
        return false;
    }
    foreach (QString plugin_name, plugins.keys()) {
        ui->dbengineslist->addItem(plugin_name);
    }
    DbManagerInterface *interface = dbplugins.value(ui->dbengineslist->currentText());
    if(interface->auth_conection())
    {
        ui->auth_options->setEnabled(true);
        QMap<QString,QString> auth = interface->default_auth_options();
        ui->host->setText(auth.value("host",""));
        ui->port->setText(auth.value("port",""));
        ui->username->setText(auth.value("username",""));
        ui->password->setText(auth.value("password",""));
    }
    else
        ui->auth_options->setEnabled(false);
    ui->connoptions->setText(interface->default_connection_options());
    return true;
}
