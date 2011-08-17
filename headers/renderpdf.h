#ifndef RENDERPDF_H
#define RENDERPDF_H

#include <QObject>
#include <QtWebKit>
#include <QPrinter>
class RenderPdf : public QObject
{
    Q_OBJECT
public:
    explicit RenderPdf(QObject *parent = 0);
    void render(QString html,QString file);
signals:

private:
        QWebView webView;
        QPrinter printer;
public slots:
    void loadFinished(bool ok);

};

#endif // RENDERPDF_H
