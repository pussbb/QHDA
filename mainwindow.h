#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMessageBox>
#include <QtGui/QMainWindow>
#include <QListWidgetItem>
#include <QSettings>
#include <QDebug>
#include <QtSql>
#include <QInputDialog>
#include <QTreeWidget>
#include <QPrinter>
#include <QPrintPreviewDialog>
#include <QTextCharFormat>
#include <QTextTable>
#include <QTextCursor>
#include <QFileDialog>
#include "aliasgui/href.h"
#include "aliasgui/syncmain.h"
#include "QTextDocumentFragment"
namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QString bookpath;
    QMessageBox msgBox;
private:
    Ui::MainWindow *ui;
    QSettings settings;
 QSqlDatabase db;
    QStringList imglist;
bool saved;
QString htmltheme;
QTextCursor lastcursor;
    bool istable;
    QString username;
    QTextImageFormat image;
    QTextTable *table;
    int sqlindex;
private slots:
    void on_actionRemove_Book_triggered();
    void on_bookitems_customContextMenuRequested(QPoint pos);
    void load_article(QString id);
    void on_startSearch_clicked();
    void on_actionReport_For_new_Bug_triggered();
    void on_actionMain_Site_triggered();
    void initSettings();
    void on_actionSettings_triggered();
    void on_actionInsert_code_triggered();
    void on_actionExport_PDF_triggered();
    void on_actionSyncronize_triggered();
    void on_actionAdd_Link_triggered();
    void on_actionEdit_Article_triggered();
    void on_books_currentChanged(int index);
    void on_actionImage_Settings_triggered();
    bool eventFilter(QObject *obj, QEvent *event);
    void on_actionImage_Default_triggered();
    void on_actionImage_Right_triggered();
    void on_actionImage_Left_triggered();
    void on_tabWidget_currentChanged(int index);
    void on_actionMerge_triggered();
    void on_actionDelete_Cell_triggered();
    void on_actionDelete_Row_triggered();
    void on_actionAdd_Cell_triggered();
    void on_actionAdd_Row_triggered();
    void on_actionAlign_Justify_triggered();
    void on_actionAlign_Right_triggered();
    void on_actionAlign_Center_triggered();
    void on_actionAlign_Left_triggered();
    void on_editor_cursorPositionChanged();
    void on_actionInsert_Table_triggered();
    void on_actionInsert_Image_triggered();
    void on_actionUnderLine_triggered();
    void on_actionItalic_triggered();
    void on_actionBold_triggered();
    void on_actionCut_triggered();
    void on_actionPaste_triggered();
    void on_actionCopy_triggered();
    void on_actionSave_triggered();
    void on_booktree_itemDoubleClicked(QTreeWidgetItem* item, int column);
    void on_booktree_clicked(QModelIndex index);
    void articles(QString cat,QTreeWidgetItem *parent);
    void subcat(QString subcat,QTreeWidgetItem *parent);
    void on_actionRemove_Category_triggered();
    void treeupdate();
    void on_actionAdd_Category_triggered();
    void on_actionExit_triggered();
    void on_actionNew_triggered();
    void on_action_2_triggered();
    void on_newbook_triggered();
    void on_bookitems_itemDoubleClicked(QListWidgetItem* item);
    void delall(QString id);
    void on_sresult_itemDoubleClicked(QListWidgetItem* item);
    void on_appclose_triggered();
    void on_about_triggered();
    void on_actionO_QT_triggered();
    void init_books();
    void mergeFormatOnWordOrSelection(const QTextCharFormat &format);
};

#endif // MAINWINDOW_H
