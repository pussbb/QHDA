#include "headers/qhda.h"
#include "ui_qhda.h"
#include "QDebug"
QHDA::QHDA(QWidget *parent) :
    QCoreWindow(parent),
    ui(new Ui::QHDA)
{
    ui->setupUi(this);
    buildLangMenu("qhda");
    LangMenuToMenuBar("menuOptions");
    init_dockwidgets();
}

QHDA::~QHDA()
{
    delete ui;
}

void QHDA::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
    {
        // BookList->setWindowTitle(QApplication::translate("QHDA", "Books list", 0, QApplication::UnicodeUTF8));
        // BookTableContents->setWindowTitle(QApplication::translate("QHDA", "Table Of Content", 0, QApplication::UnicodeUTF8));
        // SearchInBook->setWindowTitle(QApplication::translate("QHDA", "Search", 0, QApplication::UnicodeUTF8));
        ui->retranslateUi(this);
        break;
    }
    default:
        break;
    }
}

void QHDA::on_actionExit_triggered()
{
   close();
}

void QHDA::init_dockwidgets()
{
    tabifyDockWidget(ui->dBookList,ui->dBookTableContents);
    tabifyDockWidget(ui->dBookList,ui->dSearchInBook);
    QTabBar *tabBar = findChild<QTabBar *>();
    tabBar->setCurrentIndex(0);
    setTabPosition(Qt::LeftDockWidgetArea,QTabWidget::West);
    ui->tabContent->setTabText(0,"WElcome");
    ui->tabContent->setWindowTitle("7687686");
    QWebView *m = new QWebView();
    ui->tabContent->insertTab(0,m,"Welcome");
    m->load(QUrl("http://google.com"));
    ///ui->tabContent-> (0,new QWebView(ui->tabContent),"Welcome");
qDebug()<<restoreDockWidget(ui->dBookList);
}

void QHDA::on_actionFull_Screen_triggered()
{
    if(!this->isFullScreen())
        this->showFullScreen();
    else
        this->showNormal();
}

void QHDA::on_actionBook_List_triggered()
{
    if(ui->dBookList->isHidden())
    {
        QDockWidget *tabBar = findChild<QDockWidget *>("dBookList");
        tabBar->show();
    }
}

void QHDA::on_actionBook_Table_of_Content_triggered()
{
    if(ui->dBookTableContents->isHidden())
    {
        QDockWidget *tabBar = findChild<QDockWidget *>("dBookTableContents");
        tabBar->show();
    }
}

void QHDA::on_actionSearch_In_Book_triggered()
{
    if(ui->dSearchInBook->isHidden())
    {
        QDockWidget *tabBar = findChild<QDockWidget *>("dSearchInBook");
        tabBar->show();
    }
}
