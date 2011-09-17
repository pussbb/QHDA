#include "xmlrpcdialog.h"
#include "ui_xmlrpcdialog.h"

XmlRpcDialog::XmlRpcDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::XmlRpcDialog)
{
    ui->setupUi(this);
}

XmlRpcDialog::~XmlRpcDialog()
{
    delete ui;
}
