#ifndef CKEDITOR_H
#define CKEDITOR_H

#include <QObject>
#include "../../../editorinterface.h"
#include <QtGui>
#include <editor.h>

class Ckeditor : public QObject, EditorInterface
{
    Q_OBJECT
    Q_INTERFACES(EditorInterface)

public:
    QString version();
    QString editorType();
    QString errorStr;
    QWidget* getEditor();
    Editor* editor;
};
#endif
