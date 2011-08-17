#include "headers/templateengine.h"
#include <qglobal.h>

QList<QString> TemplateEngine::jsFiles = QList<QString> ()
    << "qrc:/jquery.js"
    << "qrc:/syntaxhighlighter/scripts/shCore.js"
    << "qrc:/syntaxhighlighter/scripts/shAutoloader.js"
    << "qrc:/syntaxhighlighter/functions.js"
    << "qrc:/syntaxhighlighter/functions.js";

QList<QString> TemplateEngine::cssFiles = QList<QString>()
    << "qrc:/syntaxhighlighter/styles/shCore.css"
    << "qrc:/syntaxhighlighter/styles/shThemeDefault.css";

TemplateEngine::TemplateEngine(QObject *parent) :
    QObject(parent)
{
    templateName = "system";
    loadTemplate();
}
void TemplateEngine::setTemplateName(QString name)
{
     templateName = name;
     loadTemplate();
}

void TemplateEngine::loadTemplate()
{
    QString themeFile;
    if(templateName == "system") {
        themeFile = ":/html/templates/silverblog/index.html";
    }
    else if (templateName == "printable") {
        themeFile = ":/html/templates/printable.html";
    }
    QFile file(themeFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
    return;
    }
    QTextStream in(&file);
    theme = in.readAll();
    QString js;
    foreach(QString file,jsFiles)
        js+= "<script src=\""+ file +"\" type=\"text/javascript\"></script>";
    QString css;
    foreach(QString file,cssFiles)
        css+= "<link type=\"text/css\" rel=\"stylesheet\" href=\""+ file +"\"/>";
    theme.replace("{javascript}",js);
    theme.replace("{css}",css);
}

QString TemplateEngine::renderAricle(QVariantMap article)
{
    QString result = theme;
    result.replace("{title}",article.value("title").toString());
    result.replace("{content}",article.value("content").toString());
    QString info = tr("Published:")+ article.value("published").toString()
             +"   "+tr("Author:")+article.value("author").toString();
    result.replace("{info}",info);
    return result;
}

QString TemplateEngine::printable(QVariantMap article)
{
    QString mainTheme = theme;
    QString mainTemplateName = templateName;
    templateName = "printable";
    loadTemplate();
    QString result = renderAricle(article);
    theme  = mainTheme;
    templateName = mainTemplateName;
    return result;
}
