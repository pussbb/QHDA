#include "headers/qhda.h"
#include "ui_qhda.h"
#include "QDebug"
QHDA::QHDA(QWidget *parent) :
    QCoreWindow(parent),
    ui(new Ui::QHDA)
{
    ui->setupUi(this);
    buildLangMenu("qhda");
    LangMenuToMenuBar("menuOptions");

}

QHDA::~QHDA()
{
    delete ui;
}

void QHDA::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
           ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void QHDA::on_actionExit_triggered()
{
    exit(0);
}
