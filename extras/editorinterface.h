#ifndef EDITORINTERFACE_H
#define EDITORINTERFACE_H
#include <QString>
#include <QtGui>
class EditorInterface
{
public:
    virtual ~EditorInterface() {}
    virtual QString version() = 0;
    virtual QString editorType() = 0;
    virtual QWidget* getEditor() = 0;
    QString errorStr;
};

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(EditorInterface,
                    "com.pussbb.QHDA.Plugin.EditorInterface/0.1");
QT_END_NAMESPACE
#endif // EDITORINTERFACE_H
