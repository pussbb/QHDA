#include "href.h"
#include "ui_href.h"

href::href(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::href)
{
    ui->setupUi(this);
}

href::~href()
{
    delete ui;
}

void href::changeEvent(QEvent *e)
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

void href::on_buttonBox_accepted()
{

}
void href::set(QString text,QString url)
{
 ui->url->setText(url);
 ui->htext->setText(text);
}
    QString href::gethref()
{//target=
    QString url="<a href=\"{url}\" {target}>{text}</a>";
    url.replace("{url}",ui->url->text());
    if(ui->htagetct->currentText()!="none")
            url.replace("{target}","target=\""+ui->htagetct->currentText()+"\"");
    else  url.replace("{target}","");
    url.replace("{text}",ui->htext->text());
    return url;
}
