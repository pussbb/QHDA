#ifndef TEMPLATEENGINE_H
#define TEMPLATEENGINE_H

#include <QObject>

class TemplateEngine : public QObject
{
    Q_OBJECT
public:
    explicit TemplateEngine(QObject *parent = 0);
    inline QString getTemplateName() {return templateName;};
    inline void setTemplateName(QString name) {templateName = name;};

signals:

public slots:

private:
    QString templateName;
};

#endif // TEMPLATEENGINE_H
