#ifndef WEBBROWSER_H
#define WEBBROWSER_H

#include <QTabWidget>
#include <QWebView>
#include <QUrl>
class TabedWebBrowser : public QTabWidget
{
    Q_OBJECT
public:
    explicit TabedWebBrowser(QWidget *parent = 0);
    bool newTab;

signals:

public slots:
    void addTab(QUrl url, const QString &label);
    void addTab(QUrl url);
    void addTab(QString html, const QString &label);
    void addTab(QString html);
    int addTab(QWidget *widget, const QIcon &icon, const QString &label);
    int addTab(QWidget *widget, const QString &label);
private:
    bool raiseExisting(QString label);
    bool _newTab;
    void toExistingTab(QString d,QString label = "");
};

#endif // WEBBROWSER_H
