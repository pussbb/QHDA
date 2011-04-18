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
        BookList->setWindowTitle(QApplication::translate("QHDA", "Books list", 0, QApplication::UnicodeUTF8));
        BookTableContents->setWindowTitle(QApplication::translate("QHDA", "Table Of Content", 0, QApplication::UnicodeUTF8));
        SearchInBook->setWindowTitle(QApplication::translate("QHDA", "Search", 0, QApplication::UnicodeUTF8));
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
    BookList = new QDockWidget(this);
    BookList->setObjectName(QString::fromUtf8("BookList"));
   BookList->setSizeIncrement(500,500);
    BookListContent = new QWidget();
  ///  BookListContent->resize(500,500);
    ///BookListContent->setObjectName(QString::fromUtf8("dockWidgetContents"));
    BookList->setWidget(BookListContent);
    this->addDockWidget(static_cast<Qt::DockWidgetArea>(1), BookList);
    BookTableContents = new QDockWidget(this);
    BookTableContents->setObjectName(QString::fromUtf8("BookTableContents"));
    BookTCContent = new QWidget();
   // dockWidgetContents_2->setObjectName(QString::fromUtf8("dockWidgetContents_2"));
    BookTableContents->setWidget(BookTCContent);
    this->addDockWidget(static_cast<Qt::DockWidgetArea>(1), BookTableContents);
    SearchInBook = new QDockWidget(this);
    SearchInBook->setObjectName(QString::fromUtf8("SearchInBook"));
    SearchContent = new QWidget();
   // dockWidgetContents_3->setObjectName(QString::fromUtf8("dockWidgetContents_3"));
    SearchInBook->setWidget(SearchContent);
    this->addDockWidget(static_cast<Qt::DockWidgetArea>(1), SearchInBook);

    tabifyDockWidget(BookList,BookTableContents);
    tabifyDockWidget(BookList,SearchInBook);
   /// BookList->setFocus();
    setTabPosition(Qt::LeftDockWidgetArea,QTabWidget::West);
}
