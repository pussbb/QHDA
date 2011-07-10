#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>
#include <QtWebKit>
#include "../../../widgets/treebox.h"

namespace Ui {
    class Editor;
}

class Editor : public QWidget
{
    Q_OBJECT

public:
    explicit Editor(QWidget *parent = 0);
    ~Editor();
    void clean();
    void buildCategoriesList(QVariantList categories);
    QString content;
    QString title;
public slots:
    void render(bool ok);
private:
    Ui::Editor *ui;
        bool alreadyInserted;
};

#endif // EDITOR_H
