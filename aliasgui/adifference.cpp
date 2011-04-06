#include "adifference.h"
#include "ui_adifference.h"

adifference::adifference(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adifference)
{
    ui->setupUi(this);
}

adifference::~adifference()
{
    delete ui;
}

void adifference::changeEvent(QEvent *e)
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
void adifference::setsitetext(QString text)
{
    QRegExp rx("<pre[^>]*>([^<]*)</pre>");
    rx.setMinimal(true);

    QStringList list;
     int pos = 0;
    while((pos = rx.indexIn( text, pos)) != -1)
    {
       list << rx.cap(1);
       pos += rx.matchedLength();

    }

    for( int n = 0; n < list.size(); n++)
    {
       QString szTmp = list.at( n);
       szTmp.replace( "\n", "<br />");
       text.replace( list.at( n), szTmp);
    }
    text.replace("<pre class","{prevclass");
    text.replace("id=\"syntaxhighlight\">","pclass}");//"&gt;
    text.replace("</pre>",QString("{/preclass}"));
    text.replace(QString('\n'),"<br />");
    ui->sitetext->insertHtml(text);
}
void adifference::setdbtext(QString text)
{
    QRegExp rx("<pre[^>]*>([^<]*)</pre>");
    rx.setMinimal(true);

    QStringList list;
     int pos = 0;
    while((pos = rx.indexIn(text, pos)) != -1)
    {
       list << rx.cap(1);
       pos += rx.matchedLength();

    }

    for( int n = 0; n < list.size(); n++)
    {
       QString szTmp = list.at( n);
       szTmp.replace( "\n", "<br />");
       text.replace( list.at( n), szTmp);
    }
    text.replace("<pre class","{prevclass");
    text.replace("id=\"syntaxhighlight\">","pclass}");//"&gt;
    text.replace("</pre>",QString("{/preclass}"));
    text.replace(QString('\n'),"<br />");
    ui->dbtext->insertHtml(text);
}
