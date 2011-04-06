#include "imgprop.h"
#include "ui_imgprop.h"

imgprop::imgprop(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::imgprop)
{
    ui->setupUi(this);

}

imgprop::~imgprop()
{
    delete ui;
}
void imgprop::setimage(QTextImageFormat image)
{// img=image;
    currimage=QPixmap(image.name());
    if(image.height()==0){
    ui->himg->setValue(currimage.height());
    ui->wimg->setValue(currimage.width());
}
    else {
        ui->himg->setValue(image.height());
        ui->wimg->setValue(image.width());
    }
}

void imgprop::changeEvent(QEvent *e)
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

void imgprop::on_imgprop_accepted()
{

}
QString imgprop::getimage()
{
// img.setWidth(ui->wimg->value());
// img.setHeight(ui->himg->value());
    QString i;
 return "width='"+i.setNum(ui->wimg->value())+"' height='"+i.setNum(ui->himg->value())+"'";
}

void imgprop::on_wimg_valueChanged(int )
{

}
