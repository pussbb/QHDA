#include "xmlrpcdialog.h"
#include "ui_xmlrpcdialog.h"

XmlRpcDialog::XmlRpcDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::XmlRpcDialog)
{
    ui->setupUi(this);
    ui->log->setVisible(false);
    adjustSize();
    ui->cancelButton->setVisible(false);
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
void XmlRpcDialog::toLog(QString text, IconTypes iconType)
{
    QString icon = ":/plugin/xmlrpc/status/";
    switch(iconType) {
        default:
        case Info :
                icon += "info.png";
                break;
        case Warning :
                icon += "warning.png";
                break;
        case Error :
                icon += "error.png";
                if(!ui->log->isVisible())
                    ui->logButton->click();
                break;
    }
    QListWidgetItem *item = new QListWidgetItem(ui->log);
    item->setText(text);
    item->setIcon(QIcon(icon));
    ui->log->addItem(item);
    ui->log->setCurrentItem(item);
}
void XmlRpcDialog::progressPlus(int value)
{
    ui->progressBar->setValue(ui->progressBar->value() + value);
}

void XmlRpcDialog::clear()
{
    ui->log->clear();
    if(!ui->log->isVisible())
        ui->logButton->click();
}
int XmlRpcDialog::leftCount()
{
    int max = ui->progressBar->maximum() ;
    int current = ui->progressBar->value();
    return  max - current  ;
}

void XmlRpcDialog::setProgressValues(int min, int max)
{
    ui->progressBar->setMinimum(min);
    ui->progressBar->setMaximum(max);
}

void XmlRpcDialog::setOperationTitle(QString title, bool addToLog = false)
{
    ui->itemName->setText(title);
    if(addToLog)
        toLog(title,Info);
}
