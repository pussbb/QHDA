#ifndef QHDA_H
#define QHDA_H

#include "headers/qcorewindow.h"
#include "headers/databasemanager.h"

#include <QListWidgetItem>
#include <QInputDialog>
#include <QMessageBox>
#include <extras/editorinterface.h>
#include "headers/templateengine.h"
#include "headers/bookwizard.h"
#include "headers/settings.h"
#include "headers/plugininfo.h"
#include "headers/about.h"

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
    TemplateEngine* articleTemplate;
    QString currentBookName;
    void openBook(QListWidgetItem* item);
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

    void on_actionRemove_Article_triggered();

    void on_actionEdit_Article_triggered();



    void on_tableOfContent_itemDoubleClicked(QTreeWidgetItem* item, int column);

    void on_actionSettings_triggered();
    void loadSettings();

    void on_actionAbout_QT_triggered();

    void on_actionPlugins_triggered();

    void on_actionAbout_triggered();

    void on_actionPDF_triggered();

    void on_actionQuick_Print_triggered();

    void on_searchButton_clicked(bool checked);


    void on_searchResults_itemDoubleClicked(QListWidgetItem* item);

    void on_actionTo_Remote_Server_triggered();

private:
    Ui::QHDA *ui;
    bool raiseEditor;

};

#endif // QHDA_H
