#include "headers/tabedwebbrowser.h"

TabedWebBrowser::TabedWebBrowser(QWidget *parent) :
    QTabWidget(parent)
{
    newTab = true;
    _newTab = true;
}

int TabedWebBrowser::addTab(QWidget *widget, const QIcon &icon, const QString &label)
{
    return QTabWidget::addTab(widget,icon,label);
}

int TabedWebBrowser::addTab(QWidget *widget, const QString &label)
{
   return QTabWidget::addTab(widget, label);
}


void TabedWebBrowser::addTab(QUrl url)
{
    if(!newTab && _newTab) {
        toExistingTab(url.toString(),"");
        return;
    }
    _newTab = true;
    int ind =  addTab(new QWebView(),"");
        QWidget *widget = this->widget(ind);
    if(QWebView *tabPage = qobject_cast<QWebView*>(widget))
        tabPage->load(url);
    setCurrentIndex(ind);
}
void TabedWebBrowser::addTab(QUrl url,const QString &label)
{
    if(!newTab && _newTab) {
        toExistingTab(url.toString(),label);
        return;
    }
    _newTab = true;
    if(raiseExisting(label))
        return;

    int ind =  addTab(new QWebView(),label);
        QWidget *widget = this->widget(ind);
    if(QWebView *tabPage = qobject_cast<QWebView*>(widget))
        tabPage->load(url);
    setCurrentIndex(ind);
}

void TabedWebBrowser::addTab(QString html)
{
    if(!newTab && _newTab) {
        toExistingTab(html,"");
        return;
    }
    _newTab = true;
    int ind =  addTab(new QWebView(),"");
        QWidget *widget = this->widget(ind);
    if(QWebView *tabPage = qobject_cast<QWebView*>(widget))
        tabPage->setHtml(html);
    setCurrentIndex(ind);
}

void TabedWebBrowser::addTab(QString html,const QString &label)
{
    if(!newTab && _newTab) {
        toExistingTab(html,label);
        return;
    }
    _newTab = true;
    if(raiseExisting(label))
        return;
    int ind =  addTab(new QWebView(),label);
        QWidget *widget = this->widget(ind);
    if(QWebView *tabPage = qobject_cast<QWebView*>(widget))
        tabPage->setHtml(html);

    setCurrentIndex(ind);
}

bool TabedWebBrowser::raiseExisting(QString label)
{
    for(int i = 0 ; i < count(); i++) {
        if(tabText(i) == label) {
            setCurrentIndex(i);
            raise();
            return true;
        }
    }
    return false;
}

void TabedWebBrowser::toExistingTab(QString d,QString label)
{
    QWidget *widget = currentWidget();

    QUrl url(d);
    QWebView *tabPage = qobject_cast<QWebView*>(widget);
    if(tabPage != NULL) {
        setTabText(currentIndex(),label);
        if(url.host() == "http" || url.host() == "https")
            tabPage->setUrl(QUrl(d));
        else
            tabPage->setHtml(d);
    }
    else {
        _newTab = false;
        if(url.host() == "http" || url.host() == "https")
            addTab(url,label);
        else
            addTab(d,label);
    }
}
