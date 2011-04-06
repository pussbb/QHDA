#include "inserttable.h"
#include "ui_inserttable.h"

insertTable::insertTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::insertTable)
{
    ui->setupUi(this);
}

insertTable::~insertTable()
{
    delete ui;
}

void insertTable::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void insertTable::on_buttonBox_accepted()
{
    row=ui->rowcount->value();
    cell=ui->cellcount->value();
}
