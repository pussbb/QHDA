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
    langMenuToMenuBar("menuOptions");
    initDockWidgets();
    initBooks();

   // dbman->interface->createCategory();
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

void QHDA::initDockWidgets()
{
    tabifyDockWidget(ui->dBookList,ui->dBookTableContents);
    tabifyDockWidget(ui->dBookList,ui->dSearchInBook);
    QTabBar *tabBar = findChild<QTabBar *>();
    tabBar->setCurrentIndex(0);
    setTabPosition(Qt::LeftDockWidgetArea,QTabWidget::West);
    ui->tabedContent->addTab(QUrl("http://google.com"));

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
    if(ui->dBookList->isHidden()) {
        QDockWidget *tabBar = findChild<QDockWidget *>("dBookList");
        tabBar->show();
    }
}

void QHDA::on_actionBook_Table_of_Content_triggered()
{
    if(ui->dBookTableContents->isHidden()) {
        QDockWidget *tabBar = findChild<QDockWidget *>("dBookTableContents");
        tabBar->show();
    }
}

void QHDA::on_actionSearch_In_Book_triggered()
{
    if(ui->dSearchInBook->isHidden()) {
        QDockWidget *tabBar = findChild<QDockWidget *>("dSearchInBook");
        tabBar->show();
    }
}

void QHDA::on_tabContent_tabCloseRequested(int index)
{
   ui->tabedContent->removeTab(index);
}

void QHDA::initBooks()
{
    QString bookPath ;
    settings.beginGroup("Books");
    foreach (QString item, settings.childKeys()) {

        bookPath = settings.value(item,"").toString()
                + QDir::toNativeSeparators("/");

        books.insert(item,new QSettings(bookPath+item+".ini",QSettings::IniFormat));

        QListWidgetItem* itemList = new QListWidgetItem(ui->bookList);
        itemList->setText(books.value(item)->value("General/Bookname","").toString());
        itemList->setData(Qt::UserRole,settings.value(item,""));
        itemList->setData(Qt::UserRole + 1,item);
        if( books.value(item)->value("General/BookIcon","").toString() != "")
            itemList->setIcon(QIcon(bookPath
                                    + books.value(item)->value("General/BookIcon","")
                                    .toString()));
        else
            itemList->setIcon(QIcon(":/app/qhda.png"));
    }
    settings.endGroup();
}

#include "headers/bookwizard.h"



void QHDA::on_bookList_itemDoubleClicked(QListWidgetItem* item)
{
    Q_UNUSED(item);
    QDockWidget *tabBarWidget = findChild<QDockWidget *>("dBookTableContents");
    tabBarWidget->raise();
}

void QHDA::on_actionHelp_Doc_triggered()
{
    BookWizard *bw = new BookWizard(this);
    if(bw->initDbPluginsList(dbman->plugins))
    {
        bw->show();
    }
    else
    {
        QMessageBox::warning(0,  QObject::tr("Database engine error"),
                                     QObject::tr("Unfortunately we couldn't find any database engine plugin.\nPlease try to reinstall application"));
    }
}
#include <QPrinter>
void QHDA::on_actionPrint_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Export PDF",
                                                    QString(), "*.pdf");
    QPrinter printer(QPrinter::HighResolution);

    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    printer.setPaperSize(QPrinter::A4);
    if (!fileName.isEmpty()) {
        if (QFileInfo(fileName).suffix().isEmpty())
            fileName.append(".pdf");
        QWebView *tabPage = qobject_cast<QWebView*>(ui->tabedContent->currentWidget());
        tabPage->print(&printer);

    }
}
