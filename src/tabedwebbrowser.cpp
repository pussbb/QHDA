#include "headers/tabedwebbrowser.h"

TabedWebBrowser::TabedWebBrowser(QWidget *parent) :
    QTabWidget(parent)
{
}

int TabedWebBrowser::addTab(QWidget *widget, const QIcon &icon, const QString &label)
{
    QTabWidget::addTab(widget,icon,label);
}

int TabedWebBrowser::addTab(QWidget *widget, const QString &label)
{
   QTabWidget::addTab(widget, label);
}


void TabedWebBrowser::addTab(QUrl url)
{
    int ind =  addTab(new QWebView(),"");
        QWidget *widget = this->widget(ind);
    if(QWebView *tabPage = qobject_cast<QWebView*>(widget))
        tabPage->load(url);
}

void TabedWebBrowser::addTab(QUrl url, const QString &)
{

}
