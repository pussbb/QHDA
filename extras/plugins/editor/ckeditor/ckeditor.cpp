#include <ckeditor.h>

QString Ckeditor::version()
{
  return "0.0.1";
}

QString Ckeditor::editorType()
{
  return "webkit";
}

QWidget* Ckeditor::getEditor()
{
    editor = new Editor();
    return editor;
}
QWidget* Ckeditor::getEditor(QVariantList categories,QString title,QString content)
{
    editor = new Editor();
    editor->buildCategoriesList(categories);
    editor->title = title;
    editor->content = content;
    return editor;
}

Q_EXPORT_PLUGIN2(ckeditor,Ckeditor);
