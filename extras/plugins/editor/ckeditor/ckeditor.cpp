#include <ckeditor.h>

QString Ckeditor::version()
{
  return "0.0.1";
}

QString Ckeditor::name()
{
    return "CKEditor";
}

QString Ckeditor::editorType()
{
  return "webkit";
}

QWidget* Ckeditor::getEditor()
{
    editor = new Editor();
    return editor;
}

QWidget* Ckeditor::getEditor(QVariantList categories,QVariantMap article)
{
    editor = new Editor();
    editor->title = article.value("title","").toString();
    editor->content = article.value("content","").toString();
    editor->buildCategoriesList(categories);
    editor->loadCkeditor();
    if(article.value("catid",-1).toInt() > 0) {
           TreeBox *category = editor->findChild<TreeBox *>("categories");
           /*int index = category->findData(article.value("catid",-1));
           qDebug()<<index;
           category->setCurrentIndex(index);*/
           category->setCurrentIndexByData(
                       article.value("catid",-1),
                       Qt::UserRole);
    }
    editor->setProperty("article",article);
    return editor;
}
QVariantMap Ckeditor::getData(QWidget *edit)
{
   QVariantMap article = edit->property("article").toMap();
   QLineEdit *title = edit->findChild<QLineEdit *>("title");
   if(title != NULL)
       article.insert("title",title->text());
   TreeBox *category = edit->findChild<TreeBox *>("categories");

   if(category != NULL) {
           article.insert("catid",category->getData(Qt::UserRole));
   }

   QWebView *page = edit->findChild<QWebView *>("webView");
   if(page != NULL) {
       QString content = page->page()->mainFrame()->evaluateJavaScript("getContents();").toString();
       QRegExp rx("<body>(.*)</body>");
       rx.indexIn(content, 0);
       article.insert("content",rx.cap (1));
   }

   return article;
}

Q_EXPORT_PLUGIN2(ckeditor,Ckeditor)
