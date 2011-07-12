#include "headers/templateengine.h"

TemplateEngine::TemplateEngine(QObject *parent) :
    QObject(parent)
{
    templateName = "system";
}
