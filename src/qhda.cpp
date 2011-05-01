#include "headers/qhda.h"
#include "ui_qhda.h"
#include "QDebug"

QHDA::QHDA(QWidget *parent) :
    QCoreWindow(parent),
    ui(new Ui::QHDA)
{
    dbman = new DataBaseManager();
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


    int ind =  ui->tabContent->addTab(new QWebView(),"Welcome");
    QWidget *widget = ui->tabContent->widget(ind);

    if(QWebView *tab_page = qobject_cast<QWebView*>(widget))
        tab_page->load(QUrl("http://google.com"));


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

void QHDA::on_tabContent_tabCloseRequested(int index)
{
   ui->tabContent->removeTab(index);
}
