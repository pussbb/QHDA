#include "qhda.h"
#include "ui_qhda.h"

QHDA::QHDA(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QHDA)
{
    ui->setupUi(this);
}

QHDA::~QHDA()
{
    delete ui;
}
