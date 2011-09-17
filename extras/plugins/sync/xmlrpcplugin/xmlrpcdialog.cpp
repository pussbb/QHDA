#include "xmlrpcdialog.h"
#include "ui_xmlrpcdialog.h"

XmlRpcDialog::XmlRpcDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::XmlRpcDialog)
{
    ui->setupUi(this);
    ui->log->setVisible(false);
    adjustSize();

}

XmlRpcDialog::~XmlRpcDialog()
{
    delete ui;
}

void XmlRpcDialog::on_logButton_clicked()
{
    bool state = ui->log->isVisible();
    int logHeight = ui->log->height();
    if(logHeight < ui->log->minimumHeight())
        logHeight = ui->log->minimumHeight();
    QSize size = window()->size();

    if(state) {
        ui->logButton->setText(tr("Show Log"));
        ui->log->setVisible(false);
        size.setHeight(size.height() - logHeight);
    }
    else {
        ui->logButton->setText(tr("Hide Log"));
        ui->log->setVisible(true);
        size.setHeight(size.height() + logHeight);
    }
    resize(size);
}

void XmlRpcDialog::setProgressValues(int min, int max)
{
    ui->progressBar->setMinimum(min);
    ui->progressBar->setMaximum(max);
}

void XmlRpcDialog::setOperationTitle(QString title, bool addToLog = false)
{
    ui->itemName->setText(title);
    if(addToLog) {
        QListWidgetItem *item = new QListWidgetItem(ui->log);
        item->setText(title);
        ui->log->addItem(item);
    }
}
