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
    exit(0);
}

void QHDA::init_dockwidgets()
{
    tabifyDockWidget(ui->BookList,ui->BookTableContents);
    tabifyDockWidget(ui->BookList,ui->SearchInBook);
    QTabBar *tabBar = findChild<QTabBar *>();
    tabBar->setCurrentIndex(0);
    setTabPosition(Qt::LeftDockWidgetArea,QTabWidget::West);

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
    if(ui->BookList->isHidden())
    {
        QDockWidget *tabBar = findChild<QDockWidget *>("BookList");
        tabBar->show();
    }
}

void QHDA::on_actionBook_Table_of_Content_triggered()
{
    if(ui->BookTableContents->isHidden())
    {
        QDockWidget *tabBar = findChild<QDockWidget *>("BookTableContents");
        tabBar->show();
    }
}

void QHDA::on_actionSearch_In_Book_triggered()
{
    if(ui->SearchInBook->isHidden())
    {
        QDockWidget *tabBar = findChild<QDockWidget *>("SearchInBook");
        tabBar->show();
    }
}
