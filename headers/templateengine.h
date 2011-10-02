#ifndef TEMPLATEENGINE_H
#define TEMPLATEENGINE_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QVariant>
#include <QResource>
#include <QSettings>
class TemplateEngine : public QObject
{
    Q_OBJECT
public:
    explicit TemplateEngine(QObject *parent = 0);
    inline QString getTemplateName() {return templateName;};
    void setTemplateName(QString fileName);
    QString renderAricle(QVariantMap article);
    QString printable(QVariantMap article);
    QString templatesDirectory;
signals:

public slots:

private:
    void loadTemplate();
    QString templateName;
    QString theme;
    static QList<QString> jsFiles;
    static QList<QString> cssFiles;
};

#endif // TEMPLATEENGINE_H
