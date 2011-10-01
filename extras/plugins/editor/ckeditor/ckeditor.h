#ifndef CKEDITOR_H
#define CKEDITOR_H

#include <QObject>
#include "../../../editorinterface.h"
#include <QtGui>
#include <editor.h>
#include "../../../widgets/treebox.h"
class Ckeditor : public QObject, EditorInterface
{
    Q_OBJECT
    Q_INTERFACES(EditorInterface)

public:
    QString version();
    QString editorType();
    QString name();
    QString errorStr;
    QWidget* getEditor();
    Editor *editor;
    QWidget* getEditor(QVariantList categories,QVariantMap article);
    QVariantMap getData(QWidget* edit);


};
#endif
