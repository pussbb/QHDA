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

signals:

public slots:
    void addTab(QUrl url, const QString &);
    void addTab(QUrl url);
    int addTab(QWidget *widget, const QIcon &icon, const QString &label);
    int addTab(QWidget *widget, const QString &label);
};

#endif // WEBBROWSER_H
