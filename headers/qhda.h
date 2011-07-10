#ifndef QHDA_H
#define QHDA_H

#include "headers/qcorewindow.h"

#include "headers/databasemanager.h"
#include <QListWidgetItem>
#include <QInputDialog>
#include <QMessageBox>
#include <extras/editorinterface.h>

namespace Ui {
    class QHDA;
}

class QHDA : public QCoreWindow
{
    Q_OBJECT

public:
    explicit QHDA(QWidget *parent = 0);
    ~QHDA();
    DataBaseManager *dbman;
    QMap<QString , QSettings*> books;
    QMessageBox msgBox;
    EditorInterface* editor;
public slots:
    void changeEvent(QEvent *e);
private slots:
    void on_actionExit_triggered();
    void initDockWidgets();
    void on_actionFull_Screen_triggered();
    void on_actionBook_List_triggered();
    void on_actionBook_Table_of_Content_triggered();
    void on_actionSearch_In_Book_triggered();
    void initBooks();
    void buildTableOfContent();
    bool checkArticleData(QVariantMap article);
    void on_tabedContent_tabCloseRequested(int index);

    void on_bookList_itemDoubleClicked(QListWidgetItem* item);

    void on_actionHelp_Doc_triggered();

    void on_actionPrint_triggered();

    void on_actionFolder_triggered();

    void on_bookList_customContextMenuRequested(QPoint pos);

    void on_actionRemove_book_triggered();

    void on_tableOfContent_customContextMenuRequested(QPoint pos);

    void on_actionRemove_Category_triggered();

    void on_actionArticle_triggered();

    void on_actionSave_triggered();

    void on_tabedContent_currentChanged(int index);

private:
    Ui::QHDA *ui;
    bool raiseEditor;
};

#endif // QHDA_H
