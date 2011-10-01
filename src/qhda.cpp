#include "headers/qhda.h"
#include "ui_qhda.h"

QHDA::QHDA(QWidget *parent) :
    QCoreWindow(parent),
    ui(new Ui::QHDA)
{
    articleTemplate = new TemplateEngine();
    dbman = new DataBaseManager();
    ui->setupUi(this);
    buildLangMenu("qhda");
    langMenuToMenuBar("menuOptions");
    initDockWidgets();
    initBooks();
    loadSettings();
    restoreWindowState();
}


QHDA::~QHDA()
{
    bool restoreBook = settings.value("Core/lastBook",false).toBool();
    if(restoreBook) {
        settings.setValue("History/lastBookName",currentBookName);
    }
    QStringList searchList;
    for(int i = 0 ; i < ui->searchString->count(); i++) {
        ui->searchString->setCurrentIndex(i);
        searchList.append(ui->searchString->currentText());
    }
    settings.setValue("History/latestSearch",searchList);
    delete ui;
}

void QHDA::loadSettings()
{
    QString path = qApp->applicationDirPath()+QDir::toNativeSeparators("/plugins/editor/");
    QString editorPlugin = settings.value("Editors/file").toString();
    QPluginLoader pluginLoader(path+editorPlugin);
    QObject *plugin = pluginLoader.instance();
    if (plugin) {
        attachTranslation(editorPlugin.replace(".so","_"));
        editor = qobject_cast<EditorInterface *>(plugin);
    }
    ui->searchString->insertItems(0,settings.value("History/latestSearch",QStringList()).toStringList());
    ui->searchString->setCurrentIndex(-1);
    ui->tabedContent->newTab = settings.value("Core/newTab",false).toBool();
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
    ////ui->tabedContent->addTab(QUrl("http://google.com"));

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
bool QHDA::checkArticleData(QVariantMap article)
{
    if(article.value("title","").toString().isEmpty()) {
        msgBox.setText(tr("Article title is required."));
        msgBox.setInformativeText(tr("Return to editor or cancel saving the article\n(All unsaved results will be lost)."));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        int result = msgBox.exec();
        if(result == QMessageBox::Yes)
            raiseEditor = true;
        return false;
    }
    return true;
}

void QHDA::on_tabedContent_tabCloseRequested(int index)
{
    raiseEditor = false;
    QWidget *widget = ui->tabedContent->widget(index);
    if(widget->objectName() == "Editor") {

        msgBox.setText(tr("Are you sure want close editor."));
        msgBox.setInformativeText(tr("All unsaved results will be lost."));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Save | QMessageBox::Cancel);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        int result = msgBox.exec();
        if(result == QMessageBox::Cancel) {
            return;
        }
        else if (result == QMessageBox::Save) {
                ui->tabedContent->setCurrentIndex(index);
                ui->actionSave->trigger();
        }
    }
    if(!raiseEditor) {
        ui->tabedContent->removeTab(index);
        widget->deleteLater();
    }
    else {
        ui->tabedContent->setCurrentIndex(index);
    }
}

void QHDA::initBooks()
{
    ui->bookList->clear();
    QString bookPath ;
    QString bookName;

    if(settings.value("Core/lastBook",false).toBool())
        bookName = settings.value("History/lastBookName","").toString();

    settings.beginGroup("Books");
    foreach (QString item, settings.childKeys()) {
        bookPath = settings.value(item,"").toString()
                + QDir::toNativeSeparators("/");

        books.insert(item,new QSettings(bookPath+item+".ini",QSettings::IniFormat));
        books.value(item)->setValue("Tmp/settingFilePath",bookPath);
        QListWidgetItem* itemList = new QListWidgetItem(ui->bookList);
        itemList->setText(books.value(item)->value("General/Bookname","").toString());
        itemList->setData(Qt::UserRole + 1,bookPath);
        itemList->setData(Qt::UserRole,item);
        if( books.value(item)->value("General/BookIcon","").toString() != "")
            itemList->setIcon(QIcon(bookPath
                                    + books.value(item)->value("General/BookIcon","")
                                    .toString()));
        else
            itemList->setIcon(QIcon(":/app/qhda.png"));
        if(!bookName.isEmpty() && item == bookName)
            openBook(itemList);

    }
    settings.endGroup();
}
void QHDA::openBook(QListWidgetItem* item)
{
    currentBookName = item->data(Qt::UserRole).toString();
    QSettings *currentBook = books.value(currentBookName);

    dbman->setCurrentInterface(currentBook->value("Database/Engine").toString());

    if(currentBook->value("Database/version").toString() != dbman->interface->version()) {
        QMessageBox::warning(0,  QObject::tr("Database engine error"),
                                     QObject::tr("The version of database engine plugin do not match with declared for this book.\nPlease try to reinstall application"));
    }
    QString dbname = item->data(Qt::UserRole).toString();
    if(!dbman->interface->isServerType())
        dbname = item->data(Qt::UserRole+1).toString() + item->data(Qt::UserRole).toString();
    bool ok;
    if(currentBook->value("Database/version").toBool())
       ok = dbman->interface->open(dbname,currentBook->value("Database/settings").toMap());
    else
       ok = dbman->interface->open(dbname);

    if(!ok)
        dbman->showError();
    else
        buildTableOfContent();
    QDockWidget *tabBarWidget = findChild<QDockWidget *>("dBookTableContents");
    tabBarWidget->raise();
}

void QHDA::on_bookList_itemDoubleClicked(QListWidgetItem* item)
{
    openBook(item);
}
void QHDA::buildTableOfContent()
{
    QVariantList categories = dbman->interface->categoriesList();
    QVariantList articles = dbman->interface->articlesList();
    QMap<QString, QTreeWidgetItem*> catList;
    ui->tableOfContent->clear();

    QListIterator<QVariant> i(categories);
    while (i.hasNext()) {
        QVariantMap attr =i.next().toMap();
        QTreeWidgetItem* item = new QTreeWidgetItem();
        item->setText(0,attr.value("name").toString());
        item->setIcon(0,QIcon(":/actions/folder.png"));
        item->setData(0,Qt::UserRole,attr.value("id"));
        item->setData(0,Qt::UserRole+1,"folder");
        catList.insertMulti(attr.value("id").toString(),item);
        if(attr.value("parent").toInt() == 0 ) {
            ui->tableOfContent->insertTopLevelItem(0,item);
        }
        else {
            QTreeWidgetItem *parent =catList.value(attr.value("parent").toString());
            if(parent != NULL)
                parent->addChild(item);
            else
                qDebug()<<"not inserted "+attr.value("name").toString();
        }
    }
    foreach(QVariant article ,articles){
        QVariantMap attr = article.toMap();
        QTreeWidgetItem* item = new QTreeWidgetItem();
        item->setText(0,attr.value("title").toString());
        item->setIcon(0,QIcon(":/actions/signature.png"));
        item->setData(0,Qt::UserRole,attr.value("id"));
        item->setData(0,Qt::UserRole+1,"article");
        QTreeWidgetItem *parent = catList.value(attr.value("catid").toString());
        if(parent != NULL)
            parent->addChild(item);

    }
}

void QHDA::on_actionHelp_Doc_triggered()
{
    BookWizard *bw = new BookWizard(this);
    if(bw->initDbPluginsList(dbman->plugins))
    {
        if(bw->exec() == QDialog::Accepted)
            initBooks();
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

    QPrinter printer(QPrinter::HighResolution);
    printer.setPaperSize(QPrinter::A4);
    int articleId = ui->tabedContent->currentWidget()->property("articleId").toInt();
    if(articleId == 0) {
        msgBox.setWindowTitle(tr("Error"));
        msgBox.setText(tr("Sorry, but could not get article."));
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }
    QString articleTheme = articleTemplate->printable(
                                            dbman->interface->article(articleId)
                                                );
    QPrintDialog *printDialog = new QPrintDialog(&printer,this);
    printDialog->setWindowTitle(tr("Print Document"));
    QTextDocument doc;
    doc.setHtml(articleTheme);
    if(printDialog->exec() ==QDialog::Accepted)
        doc.print(&printer);

}

void QHDA::on_actionQuick_Print_triggered()
{
#ifndef QT_NO_PRINTER
    msgBox.setWindowTitle(tr("Printing error!"));
    msgBox.setText(tr("There is no default printer set in the system."));
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.exec();
#else
    QPrinter printer(QPrinter::HighResolution);
    printer.setPaperSize(QPrinter::A4);
    int articleId = ui->tabedContent->currentWidget()->property("articleId").toInt();
    if(articleId == 0) {
        msgBox.setWindowTitle(tr("Error"));
        msgBox.setText(tr("Sorry, but could not get article."));
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }
    QString articleTheme = articleTemplate->printable(
                                            dbman->interface->article(articleId)
                                                );
    QTextDocument doc;
    doc.setHtml(articleTheme);
    doc.print(&printer);
#endif
}

void QHDA::on_actionFolder_triggered()
{
    bool ok;
         QString text = QInputDialog::getText(this, tr("New category name"),
                                              tr("Name:"), QLineEdit::Normal,
                                              "", &ok);
         if (ok && !text.isEmpty()) {
             int parentId = 0;
             if(ui->tableOfContent->onItem) {
                 QTreeWidgetItem *item = ui->tableOfContent->currentItem();
                 if(item->data(0,Qt::UserRole+1).toString() == "folder"){
                     parentId = item->data(0,Qt::UserRole).toInt();
                 }
                 else {
                     if( item->parent() != NULL) {
                        if(item->parent()->data(0,Qt::UserRole+1).toString() == "folder")
                            parentId = item->parent()->data(0,Qt::UserRole).toInt();
                     }
                 }
             }
             if(!dbman->interface->createCategory(text,parentId))
                 dbman->showError();
             else
                 buildTableOfContent();
         }
}

void QHDA::on_bookList_customContextMenuRequested(QPoint pos)
{
    QMenu *m=new QMenu();
    m->addAction(ui->actionHelp_Doc);
    if( ui->bookList->currentIndex ().isValid ()
                && ui->bookList->currentItem ()->isSelected ()) {
        pos.setX(pos.x()+5);
        pos.setY(pos.y()+10);
        m->addAction(ui->actionRemove_book);
        m->addAction(ui->actionEdit_Book_Properties);

    }
    m->exec(ui->bookList->mapToGlobal(pos));
}

void QHDA::on_actionRemove_book_triggered()
{
    msgBox.setText(tr("Are you sure want delete item."));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    if(msgBox.exec()==QMessageBox::Yes) {
        QListWidgetItem* item = ui->bookList->currentItem();
        settings.remove("Books/"+item->text());
        settings.sync();
        delete item;
    }
}

void QHDA::on_tableOfContent_customContextMenuRequested(QPoint pos)
{
    QMenu *m=new QMenu();
    m->addAction(ui->actionFolder);
    if( ui->tableOfContent->onItem) {
        pos.setX(pos.x()+5);
        pos.setY(pos.y()+10);
        QTreeWidgetItem *item = ui->tableOfContent->currentItem();
        if(item->data(0,Qt::UserRole+1).toString() == "folder") {
            m->addAction(ui->actionRemove_Category);
        }
        else {
            m->addAction(ui->actionRemove_Article);
            m->addAction(ui->actionEdit_Article);
        }
    }
    m->exec(ui->tableOfContent->mapToGlobal(pos));
}

void QHDA::on_actionRemove_Category_triggered()
{
    msgBox.setText(tr("Are you sure want delete item."));
    msgBox.setInformativeText(tr("All child categories and articles for this category will be deleted to.\n Are you sure"));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    if(msgBox.exec()==QMessageBox::Yes) {
        QTreeWidgetItem *item = ui->tableOfContent->currentItem();
        bool ok = dbman->interface->deleteCategory(item->data(0,Qt::UserRole).toInt());
        if(!ok)
            dbman->showError();
        else
            delete item;
    }
}

void QHDA::on_actionArticle_triggered()
{
    ui->tabedContent->addTab(editor->getEditor(dbman->interface->categoriesList(),
                                           dbman->interface->getTableColumnNames("articles")    ),
                             tr("New Article"));
}

void QHDA::on_actionSave_triggered()
{
   QWidget *widget = ui->tabedContent->currentWidget();
   QVariantMap article = editor->getData(widget);
   bool ok = false;
   if(checkArticleData(article))
        ok = dbman->saveArticle(article);
   if(ok) {
       buildTableOfContent();
       ui->tabedContent->removeTab(ui->tabedContent->currentIndex());
       widget->deleteLater();
   }
}

void QHDA::on_tabedContent_currentChanged(int index)
{
    QWidget *widget = ui->tabedContent->widget(index);
       if(widget != NULL &&
               widget->objectName() == "Editor")
           ui->actionSave->setEnabled(true);
       else
           ui->actionSave->setEnabled(false);
}

void QHDA::on_actionRemove_Article_triggered()
{
    msgBox.setText(tr("Are you sure want delete this article."));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    if(msgBox.exec()==QMessageBox::Yes) {
        QTreeWidgetItem *item = ui->tableOfContent->currentItem();
        bool ok = dbman->interface->deleteArticle(item->data(0,Qt::UserRole).toInt());
        if(!ok)
            dbman->showError();
        else
            delete item;
    }
}

void QHDA::on_actionEdit_Article_triggered()
{
    int index = ui->tableOfContent->currentItem()->data(0,Qt::UserRole).toInt();
    QVariantMap article = dbman->interface->article(index);
    ui->tabedContent->addTab(editor->getEditor(dbman->interface->categoriesList(),
                                           article    ),
                             tr("Edit")+"   "+article.value("title").toString());
}

void QHDA::on_tableOfContent_itemDoubleClicked(QTreeWidgetItem* item, int column)
{
    if(item == NULL)
        return;

    QString type = item->data(column,Qt::UserRole+1).toString();
    if( type == "folder")
        return;
    int articleId = item->data(column,Qt::UserRole).toInt();
    QVariantMap article = dbman->interface->article(articleId);
    QString articleTheme = articleTemplate->renderAricle(article);
    ui->tabedContent->addTab(articleTheme,article.value("title").toString());
    ui->tabedContent->currentWidget()->setProperty("articleId",articleId);
}

void QHDA::on_actionSettings_triggered()
{
    Settings *settingsDialog = new Settings(this);
    settingsDialog->exec();
    settingsDialog->deleteLater();
}

void QHDA::on_actionAbout_QT_triggered()
{
    QApplication::aboutQt();
}

void QHDA::on_actionPlugins_triggered()
{
    PluginInfo *pluginInfo = new PluginInfo(this);
    pluginInfo->exec();
    pluginInfo->deleteLater();
}

void QHDA::on_actionAbout_triggered()
{
    About *about = new About(this);
    about->exec();
    about->deleteLater();
}
#include "headers/renderpdf.h"
void QHDA::on_actionPDF_triggered()
{
    int articleId = ui->tabedContent->currentWidget()->property("articleId").toInt();

    QString fileName = QFileDialog::getSaveFileName(this, tr("Export PDF"),
                                                    QString(), "*.pdf");

    if (!fileName.isEmpty() && articleId != 0) {
        if (QFileInfo(fileName).suffix().isEmpty())
            fileName.append(".pdf");
        QVariantMap article = dbman->interface->article(articleId);
        QString articleTheme = articleTemplate->printable(article);
        RenderPdf pdf;
        pdf.render(articleTheme,fileName);
    }
}

void QHDA::on_searchButton_clicked(bool checked)
{
    Q_UNUSED(checked);

    if(ui->searchString->currentText().isEmpty())
        return;

    ui->searchString->insertItem(0,ui->searchString->currentText());
    QVariantList results = dbman->interface->search(ui->searchString->currentText());
    ui->searchResults->clear();
    foreach(QVariant item, results){
        QVariantMap data = item.toMap();
        QListWidgetItem *listItem = new QListWidgetItem(ui->searchResults);
        listItem->setText(data.value("title","").toString());
        listItem->setData(Qt::UserRole,data.value("id",""));
        ui->searchResults->addItem(listItem);
    }
}

void QHDA::on_searchResults_itemDoubleClicked(QListWidgetItem* item)
{
    int articleId = item->data(Qt::UserRole).toInt();
    QVariantMap article = dbman->interface->article(articleId);
    QString articleTheme = articleTemplate->renderAricle(article);
    ui->tabedContent->addTab(articleTheme,article.value("title").toString());
    ui->tabedContent->currentWidget()->setProperty("articleId",articleId);
}
SyncInterface* QHDA::loadSyncPlugin(QString file)
{
    QString path = qApp->applicationDirPath()+QDir::toNativeSeparators("/plugins/sync/");
    QDir d(path);
    SyncInterface *syncFace;

    QPluginLoader pluginLoader(d.absoluteFilePath(file));
    QObject *plugin = pluginLoader.instance();
    if (plugin) {
        attachTranslation(file.replace(".so","_"));
        syncFace = qobject_cast<SyncInterface *>(plugin);
    }

    syncFace->init(settings.value("Core/username","").toString(),
                   settings.value("Synchronizing/apiKey","").toString());
    syncFace->setHost(settings.value("Synchronizing/host","").toString(),
                        settings.value("Synchronizing/port",80).toInt(),
                            settings.value("Synchronizing/path","").toString());
    syncFace->setUserAgent(settings.value("Synchronizing/userAgent","QHDA").toString());
    bool isAuth =settings.value("Synchronizing/isAuth",false).toBool();
    if(isAuth)
        syncFace->authAccess(settings.value("Synchronizing/authUserName","").toString(),
                             settings.value("Synchronizing/authPassword","").toString());

    return syncFace;
}

void QHDA::on_actionTo_Remote_Server_triggered()
{
    QString file = settings.value("Synchronizing/pluginToRemote","").toString();
    SyncInterface *syncFace = loadSyncPlugin(file);
    syncFace->start(books.value(currentBookName),dbman->interface,SyncInterface::Upload);
}

void QHDA::on_actionFrom_Site_triggered()
{
    QString file = settings.value("Synchronizing/pluginFromRemote","").toString();
    SyncInterface *syncFace = loadSyncPlugin(file);
    syncFace->start(books.value(currentBookName),dbman->interface,SyncInterface::Download);
    buildTableOfContent();
}
