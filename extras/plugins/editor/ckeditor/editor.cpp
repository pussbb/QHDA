#include "editor.h"
#include "ui_editor.h"
#include "QWebInspector"
#include <QWebElement>
Editor::Editor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Editor)
{

    ui->setupUi(this);
//    QWebInspector *inspector = new QWebInspector;
//    ui->webView->page()->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
     ui->webView->page()->settings()->setAttribute(QWebSettings::AutoLoadImages, true);
     ui->webView->page()->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);
     connect(ui->webView->page(), SIGNAL(loadFinished(bool)),
             this, SLOT(render(bool)));
/// ui->webView->page()->settings()->setAttribute(QWebSettings::JavascriptCanAccessClipboard, true);
//  ui->webView->page()->settings()->setAttribute(QWebSettings::JavascriptCanOpenWindows, true);

//       inspector->setPage(ui->webView->page());
//inspector->show();
alreadyInserted = false;

}

Editor::~Editor()
{
    delete ui;
}

void Editor::render(bool ok)
{
    if(!ok)
        return;

   if(content.isEmpty()
           || alreadyInserted)
       return;

  /* QWebElement document = ui->webView->page()->mainFrame()->documentElement();
   QWebElement elem = document.findFirst("textarea#editor1");
   elem.appendInside(content);
   ui->webView->page()->mainFrame()->evaluateJavaScript("insertHTML();");
*/
   ui->title->setText(title);
   alreadyInserted = true;
}

void Editor::clean()
{

}
void Editor::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
    {
        ui->retranslateUi(this);
        break;
    }
    default:
        break;
    }
}
void Editor::loadCkeditor()
{
    QFile file(":/ckeditor/editor.html");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
    return;
    }
    QTextStream in(&file);
    QString content_ = in.readAll();
    content_.replace("{content}",content);
    ui->webView->setHtml(content_);
}

void Editor::buildCategoriesList(QVariantList categories)
{
    QTreeWidget *tree = new QTreeWidget;

    QMap<QString, QTreeWidgetItem*> elements;
    QListIterator<QVariant> i(categories);
    while (i.hasNext()) {
        QVariantMap attr =i.next().toMap();
        QTreeWidgetItem *parent =elements.value(attr.value("parent").toString());
        QTreeWidgetItem* item = new QTreeWidgetItem(parent);
        item->setText(0,attr.value("name").toString());
        item->setIcon(0,QIcon(":/actions/folder.png"));
        item->setData(0,Qt::UserRole,attr.value("id"));
        item->setData(0,Qt::UserRole+1,"folder");
        elements.insertMulti(attr.value("id").toString(),item);
        if(parent == NULL ) {
            tree->insertTopLevelItem(0,item);
        }
    }
    TreeBox *combo = new TreeBox(this);
    combo->setModel(tree->model());
    combo->setObjectName("categories");
    ui->gridLayout_2->addWidget(combo, 0, 1, 1, 1);

}
