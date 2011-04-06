#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkProxy>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->helview->page()->OpenLinkInNewWindow
    //ui->widget->setBaseSize();
    db = QSqlDatabase::addDatabase("QSQLITE");
    MainWindow::initSettings(); //set normal view
    //   ui->textwidget->setVisible(false);
    ui->txtedit->setVisible(false);
    ui->tabletool->setVisible(false);
    ui->blist->setEnabled(false);
    ui->imgtool->setVisible(false);
    // end of section
    this->init_books();
    ui->editor->viewport()->installEventFilter(this);
    ui->actionRemove_Category->setEnabled(false);
    ui->books->widget(1)->setEnabled(false);
//ui->bookitems->set
    //  QResource::registerResource(QApplication::applicationDirPath()+"/Templates/manuscript.rcc");

}
void MainWindow::initSettings()
{ if(!settings.group().isEmpty()) settings.endGroup();
    settings.beginGroup("main");

    if(!settings.contains("username"))
    {
        msgBox.setText("You must setup settings first.");
        msgBox.exec();
        emit MainWindow::on_actionSettings_triggered();

    }
    username=settings.value("username").toString();
    htmltheme=settings.value("htmltheme").toString();
    if(htmltheme=="default")  htmltheme=":/htmlpage/default/index.html";
    else {
        QResource::registerResource(QApplication::applicationDirPath()+"/Templates/"+htmltheme+".rcc");
        htmltheme=":/"+htmltheme+"/index.html";
        qDebug()<<htmltheme;
    }
    settings.endGroup();
    settings.beginGroup("web");
    int proxytype=settings.value("proxytype","-1").toInt();
    if (proxytype!=2 || proxytype!=-1)
    {
        QNetworkProxy proxy;
        switch (proxytype)
        {
        case 1: proxy.setType(QNetworkProxy::Socks5Proxy);break;
        case 3:  proxy.setType(QNetworkProxy::HttpProxy);break;
        case 4:  proxy.setType(QNetworkProxy::HttpCachingProxy);break;
        case 5:  proxy.setType(QNetworkProxy::FtpCachingProxy);break;
        }

        proxy.setHostName(settings.value("proxyurl").toString());
        proxy.setPort(settings.value("proxyport").toInt());
        proxy.setUser(settings.value("proxyuser").toString());
        proxy.setPassword(settings.value("proxyuserpass").toString());
        QNetworkProxy::setApplicationProxy(proxy);

    }
    settings.endGroup();
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    //  if(obj==ui->editor)
    //  {


    if(event->type()==QEvent::MouseButtonDblClick)
    {
        lastcursor=ui->editor->textCursor();
        image=lastcursor.charFormat().toImageFormat();
        if(image.isValid())
            ui->imgtool->setVisible(true);
        else ui->imgtool->setVisible(false);
        return true;

    }
    else {return false;}
    //  }
    //  else{   return QWidget::eventFilter(obj, event);}

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::init_books()
{ui->bookitems->clear();

    if(settings.group()!="Books")
        settings.beginGroup("Books");
    QStringList keys = settings.childKeys();
    int i=0;
    while(i<keys.count()){
        QListWidgetItem *item=new QListWidgetItem();
        QSettings books(settings.value(keys[i],"").toString()+"/settings.ini",QSettings::IniFormat);
        item->setText(books.value("bookname","").toString());
        item->setIcon(QIcon(settings.value(keys[i],"").toString()+books.value("bookicon","").toString()));
        item->setToolTip(books.value("bookdescr","").toString());

        item->setData(32,QVariant(settings.value(keys[i],"").toString()+books.value("bookdb","").toString()));
        item->setData(33,QVariant(settings.value(keys[i],"").toString()));
        ui->bookitems->addItem(item);
        ++i;
    }
}
void MainWindow::on_actionO_QT_triggered()
{
    QApplication::aboutQt ();
}
#include <aliasgui/about.h>
void MainWindow::on_about_triggered()
{
    About* about=new About(this);
    about->exec();
    // msgBox.setText(QString::fromLocal8Bit("<h1>Help World</h1> прогрмма для сбора докумениации"));
    // msgBox.exec();
    while(about->isVisible()){qApp->processEvents(QEventLoop::WaitForMoreEvents );}
   delete about;
}

void MainWindow::on_appclose_triggered()
{
    QApplication::exit(0);
}



void MainWindow::on_sresult_itemDoubleClicked(QListWidgetItem* item)
{

MainWindow::load_article(item->data(32).toString());
}



void MainWindow::on_bookitems_itemDoubleClicked(QListWidgetItem* item)
{qDebug()<<db.lastError();
    if(db.isOpen())
    {qDebug()<<"close db conection"; db.close();}
    ui->booktree->clear();
db = QSqlDatabase::addDatabase("QSQLITE");
    ui->blist->setEnabled(true);
    ui->books->widget(1)->setEnabled(true);
    ui->books->setCurrentIndex(1);
    bookpath=item->data(33).toString();qDebug()<<"Db path"<< bookpath;
    db.setDatabaseName( item->data(32).toString());
    if (!db.open()) {
        QMessageBox::critical(0, tr("Cannot open database"),
                              tr("Cannot open database."), QMessageBox::Cancel);
        return;
    }
    MainWindow::treeupdate();
}
#include "aliasgui/newbook/newbook.h"
void MainWindow::on_newbook_triggered()
{
    newbook* nb=new newbook();
    if(nb->exec())
    {
        ui->bookitems->clear();
        this->init_books();
    }
    //nb->~newbook();
//delete nb;
}



void MainWindow::on_action_2_triggered()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    "",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    if(!dir.isEmpty())
    {
        if(!QFile::exists(dir+"/settings.ini"))
        {
            msgBox.setText("Folder doesn't contain any book");
            msgBox.exec();
            return ;
        }
        QSettings books(dir+"/settings.ini",QSettings::IniFormat);

        if(settings.group()!="Books")
            settings.beginGroup("Books");
        settings.setValue(books.value("bookname").toString(),dir+"/");
        ui->bookitems->clear();
        init_books();

    }
}


void MainWindow::on_actionNew_triggered()
{//ui->booktree->currentIndex().isValid()

    if(ui->booktree->currentItem()->isSelected() && ui->booktree->currentItem()->data(0,Qt::UserRole+1).toBool()==false){

        ui->stackedWidget->setCurrentWidget(ui->weditor); ;
        imglist.clear();
         sqlindex=-1;
        ui->txtedit->setVisible(true);
        ui->editor->document()->clear();
        ui->blist->setVisible(false);
        saved=false;
    }
    else
    {
        msgBox.setText(QString::fromUtf8("Вы не выбрали категорию."));
        msgBox.setInformativeText(QString::fromUtf8("Вы не можете создавать докумены без родительской категории"));
        // msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        msgBox.setIcon(QMessageBox::Warning);
        //msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.exec();
    }
    // ui->bookWidget->setVisible(false);
}

void MainWindow::on_actionExit_triggered()
{
    if(saved==false){
        msgBox.setText(QString::fromUtf8("Вы уверены что хотите выйти."));
        msgBox.setInformativeText(QString::fromUtf8("Все изменения в документе не будут сохраненны"));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        if(msgBox.exec()==QMessageBox::Yes)
        {
            ui->stackedWidget->setCurrentWidget(ui->mpage); ;
            ui->txtedit->setVisible(false);

            ui->blist->setVisible(true);
            //ui->bookWidget->setVisible(true);
        }
    }
    else{ ui->stackedWidget->setCurrentWidget(ui->mpage); ;
    ui->txtedit->setVisible(false);
    ui->blist->setVisible(true);
}
}

void MainWindow::on_actionAdd_Category_triggered()
{
    qDebug()<<"fgdf";bool ok;
    if(ui->booktree->currentItem()!=NULL and ui->booktree->currentItem()->isSelected()){
        qDebug()<<ui->booktree->currentItem()->isSelected();
        QString text = QInputDialog::getText(this, tr("Category"),
                                             tr("name:"), QLineEdit::Normal,
                                             "", &ok);
        if (ok && !text.isEmpty())
        {
            db.exec("insert into bookcat ('name','descr','parent',subcat) values('"+text+"','descr',0,"+ui->booktree->currentItem()->data(0,32).toString()+")");
            MainWindow::treeupdate();
        }
    }
    else {
        QString text = QInputDialog::getText(this, tr("Category"),
                                             tr("name:"), QLineEdit::Normal,
                                             "", &ok);
        if (ok && !text.isEmpty())
        { // textLabel->setText(text);
            /*
     query.exec("create table bookcat (id int primary key, "
                "name varchar(20), descr text,parent int default 0, subcat int default 0)");
*/
            db.exec("insert into bookcat ('name','descr','parent',subcat) values('"+text+"','descr',1,0)");
            MainWindow::treeupdate();
        }
    }
}
void MainWindow::treeupdate()
{ui->booktree->clear();

    QSqlQuery query("SELECT * FROM bookcat WHERE parent=1");
    while (query.next()) {
        QTreeWidgetItem* item=new QTreeWidgetItem(ui->booktree);
        item->setText(0,query.value(1).toString());
        item->setData(0,32,QVariant(query.value(0)));
        item->setData(0,Qt::UserRole+1,false);
        item->setIcon(0,QIcon(":/etc/icons/file-manager.png"));
        MainWindow::articles(query.value(0).toString(),item);
        MainWindow::subcat(query.value(0).toString(),item);
        ui->booktree->addTopLevelItem(item);

    }
    ui->actionRemove_Category->setEnabled(false);
}
void MainWindow::subcat(QString subcat,QTreeWidgetItem *parent)
{qDebug()<<subcat;
    QSqlQuery query("SELECT * FROM bookcat WHERE subcat='"+subcat+"'");
    qDebug()<<query.lastQuery();
    qDebug()<<query.lastError();
    while (query.next()) {
        qDebug()<<"found"<<query.value(1);
        QTreeWidgetItem *child=new QTreeWidgetItem(parent);
        child->setText(0,query.value(1).toString());
        child->setData(0,32,QVariant(query.value(0)));
        child->setData(0,Qt::UserRole+1,false);
        child->setIcon(0,QIcon(":/etc/icons/file-manager.png"));
        MainWindow::articles(query.value(0).toString(),child);
        MainWindow::subcat(query.value(0).toString(),child);
        parent->addChild(child);

    }
}
void MainWindow::articles(QString cat,QTreeWidgetItem *parent)
{
    QSqlQuery article("SELECT * FROM articles WHERE catid='"+(QString)cat+"'");
    while (article.next()) {
        QTreeWidgetItem *item=new QTreeWidgetItem(parent);
        item->setText(0,article.value(1).toString());
        item->setData(0,32,QVariant(article.value(0)));
        item->setData(0,Qt::UserRole+1,true);
        item->setIcon(0,QIcon(":/etc/icons/document.png"));
        ui->booktree->addTopLevelItem(item);

    }
}

void MainWindow::on_actionRemove_Category_triggered()
{

    if(ui->booktree->currentItem()->isSelected()){
        msgBox.setText(QString::fromUtf8("Вы действительно хотите удалить елемент."));
        msgBox.setInformativeText(QString::fromUtf8("Если он являеться родительським то все остальные елементы удаляться тоже"));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        if(msgBox.exec()==QMessageBox::Yes) {
            if(ui->booktree->currentItem()->data(0,Qt::UserRole+1).toBool()){
                QSqlQuery query("DELETE FROM articles WHERE id='"+ui->booktree->currentItem()->data(0,32).toString()+"'");
                query.exec();
            }
            else
            { QSqlQuery query("SELECT * FROM bookcat WHERE  name='"+ui->booktree->currentItem()->text(0)+"'");
                query.exec();
                if(query.next()){
                    MainWindow::delall(query.value(0).toString()) ;
                }
                // QSqlQuery query();
                query.exec("DELETE FROM bookcat WHERE name='"+ui->booktree->currentItem()->text(0)+"'");

            }
            MainWindow::treeupdate();
        }
    }
}
void MainWindow::delall(QString id)
{
    QSqlQuery article("SELECT * FROM articles WHERE catid='"+id+"'");
    while(article.next())
    {
        QSqlQuery query("DELETE FROM articles WHERE id='"+article.value(0).toString()+"'");
        query.exec();
    }
    QSqlQuery cat("SELECT * FROM bookcat WHERE subcat='"+id+"'");
    while(cat.next())
    {
        QSqlQuery query("DELETE FROM bookcat WHERE id='"+cat.value(0).toString()+"'");
        query.exec();
        MainWindow::delall(cat.value(0).toString()) ;
    }
}

void MainWindow::on_booktree_clicked(QModelIndex index)
{

    ui->actionRemove_Category->setEnabled(true);

}

void MainWindow::on_booktree_itemDoubleClicked(QTreeWidgetItem* item, int column)
{
    if(item->data(0,Qt::UserRole+1).toBool()){
MainWindow::load_article(item->data(column,32).toString());
//        QSqlQuery query("SELECT * FROM articles WHERE id='"+item->data(column,32).toString()+"'");
//        query.exec();query.next();
//
//
//        QFile file(htmltheme);
//
//        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
//        {qDebug()<<"canot open the file";}
//        QTextStream in(&file);
//        QString string= in.readAll();
//
//        string.replace(QString("{section}"),item->parent()->text(0));
//        QString str=query.value(2).toString();
//        str.replace("&lt;","<");
//        str.replace("&gt;",">");//&quot;
//        str.replace("&quot;","'");
//        string.replace(QString("{title}"),query.value(1).toString());
//        string.replace(QString("{body}"),str);
//        string.replace(QString("{imgpath}"),"file://"+bookpath+"/img/");
//        string.replace(QString("{pdate}"),query.value(4).toString());
//        string.replace(QString("{author}"),query.value(3).toString());
//        ui->helview->setHtml(string);

    }
}
void MainWindow::load_article(QString id)
{
    QSqlQuery query("SELECT * FROM articles WHERE id='"+id+"'");
    query.exec();query.next();


    QFile file(htmltheme);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {qDebug()<<"canot open the file";}
    QTextStream in(&file);
    QString string= in.readAll();
    QSqlQuery cat("SELECT * FROM bookcat WHERE id='"+query.value(6).toString()+"'");
    cat.exec();cat.next();
    string.replace(QString("{section}"),cat.value(1).toString());
    QString str=query.value(2).toString();
    str.replace("&lt;","<");
    str.replace("&gt;",">");//&quot;
    str.replace("&quot;","'");
    string.replace(QString("{title}"),query.value(1).toString());
    string.replace(QString("{body}"),str);
    string.replace(QString("{imgpath}"),"file://"+bookpath+"/img/");
    string.replace(QString("{pdate}"),query.value(4).toString());
    string.replace(QString("{author}"),query.value(3).toString());
    ui->helview->setHtml(string);
}

void MainWindow::on_actionSave_triggered()
{
    QString data=ui->editor->document()->toHtml();
    // anything up to the html tag
    int i = data.indexOf("<html");
    if (i > 0)
        data.remove(0, i - 1);

    // everything inside the head tag
    i = data.indexOf("<html");
    if (i > 0)
        data.remove(i, data.indexOf("</head>") - i + 7);
    i = data.indexOf("<body");
    if (i > 0)
        data.remove(i, data.indexOf(">") - i + 1);
    i = data.indexOf("</body");
    if (i > 0)
        data.remove(i, data.indexOf("</html>") - i + 7);
    qDebug()<<imglist.count();
    for(int i=0;i<imglist.count();i++)
    {
        QFileInfo fi(imglist.value(i));
        data.replace(QString(imglist.value(i)),QString("{imgpath}"+fi.fileName()));
        if(!QFile::exists(bookpath+"img/"+fi.fileName ())){ QFile::copy(imglist.value(i),bookpath+"img/"+fi.fileName ());}
    }
    data.replace("'","\"");
    data.replace("[prevclass","<pre class");
    data.replace("pclass]","id=\"syntaxhighlight\">");//"&gt;
    data.replace(QString("[/preclass]"),"</pre>");
    data.replace("<br />",QString('\n'));
    //  qDebug()<<data;
    QCryptographicHash *md5=new QCryptographicHash(QCryptographicHash::Md5);
    md5->addData(data.toUtf8());

QString ind;
    QString q="update articles set name='"+ui->doctitle->text()+"',body='"+data+"',author='"+username+"',pdate=datetime('now'), md5='"+QString(md5->result().toHex())+"' where id="+ ind.setNum(sqlindex);
    if(sqlindex<0)
        db.exec("insert into articles ('name','body','catid','author','pdate','md5') values('"+ui->doctitle->text()+"','"+data+"','"+ui->booktree->currentItem()->data(0,32).toString()+"','"+username+"',datetime('now'),'"+QString(md5->result().toHex())+"')");
    else
        db.exec(q);
    if(db.lastError().isValid())
        msgBox.setText("Error ocurred while save article"+db.lastError().text());
    else{
        MainWindow::treeupdate();
        saved=true;
        ui->actionExit->trigger();
        sqlindex=-1;
    }
}

void MainWindow::on_actionCopy_triggered()
{
    ui->editor->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->editor->paste();
}


void MainWindow::on_actionCut_triggered()
{
    ui->editor->cut();
}
void MainWindow::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
    QTextCursor cursor = ui->editor->textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(format);
    ui->editor->mergeCurrentCharFormat(format);
}
void MainWindow::on_actionBold_triggered()
{
    QTextCharFormat fmt;
    fmt.setFontWeight(ui->actionBold->isChecked() ? QFont::Bold : QFont::Normal);

    this->mergeFormatOnWordOrSelection(fmt);
}

void MainWindow::on_actionItalic_triggered()
{
    QTextCharFormat fmt;

    fmt.setFontItalic(ui->actionItalic->isChecked());

    this->mergeFormatOnWordOrSelection(fmt);
}

void MainWindow::on_actionUnderLine_triggered()
{
    QTextCharFormat fmt;

    fmt.setFontUnderline(ui->actionUnderLine->isChecked());

    this->mergeFormatOnWordOrSelection(fmt);
}

void MainWindow::on_actionInsert_Image_triggered()
{
    QString  filename = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                     "",
                                                     tr("Images (*.png *.bmp *.gif *.jpg)"));
    if(!filename.isEmpty()){
        imglist<<filename;

        ui->editor->append("<img src='"+filename+"'/>");

       // qDebug()<<imglist;

    }
}
#include "aliasgui/inserttable/inserttable.h"
void MainWindow::on_actionInsert_Table_triggered()
{
    QTextTableFormat format;
    //format.setWidth( QTextLength(QTextLength::PercentageLength,20) );
    //format.setCellSpacing(20);
    insertTable* itf=new insertTable(this);
    if (itf->exec()== QDialog::Accepted)
    { QTextCursor cursor(ui->editor->textCursor());
        cursor.insertTable(itf->row,itf->cell,format);
    }
    delete itf;
}

void MainWindow::on_editor_cursorPositionChanged()
{
    lastcursor=ui->editor->textCursor();
    istable=lastcursor.currentTable();
    //isemage=lastcursor.charFormat().CssFloat;
    image=lastcursor.charFormat().toImageFormat();
    if(image.isValid())
        ui->imgtool->setVisible(true);
    else ui->imgtool->setVisible(false);
    if (!istable)
        ui->tabletool->setHidden(true);


    else {ui->tabletool->setHidden(false);
        if (lastcursor.hasSelection())
            ui->actionMerge->setEnabled(true);
        else ui->actionMerge->setDisabled(true) ;
    }
}

void MainWindow::on_actionAlign_Left_triggered()
{
    ui->editor->setAlignment(ui->actionAlign_Left->isChecked()?Qt::AlignLeft:Qt::AlignAbsolute);
}

void MainWindow::on_actionAlign_Center_triggered()
{
    ui->editor->setAlignment(Qt::AlignCenter);
}

void MainWindow::on_actionAlign_Right_triggered()
{
    ui->editor->setAlignment(Qt::AlignRight);
}

void MainWindow::on_actionAlign_Justify_triggered()
{
    ui->editor->setAlignment(Qt::AlignJustify);
}

void MainWindow::on_actionAdd_Row_triggered()
{
    table=ui->editor->textCursor().currentTable();
    QTextTableCell cell = table->cellAt(lastcursor);
    table->insertRows(cell.row()+1,1);
}

void MainWindow::on_actionAdd_Cell_triggered()
{
    table=ui->editor->textCursor().currentTable();
    QTextTableCell cell = table->cellAt(lastcursor);
    table->insertColumns(cell.row()+1,1);
}

void MainWindow::on_actionDelete_Row_triggered()
{
    table=ui->editor->textCursor().currentTable();
    QTextTableCell cell = table->cellAt(lastcursor);
    table->removeRows(cell.row(), 1);
}

void MainWindow::on_actionDelete_Cell_triggered()
{
    table=ui->editor->textCursor().currentTable();
    QTextTableCell cell = table->cellAt(lastcursor);
    table->removeColumns(cell.row(), 1);
}

void MainWindow::on_actionMerge_triggered()
{
    table=ui->editor->textCursor().currentTable();
    table->mergeCells(lastcursor);
}

void MainWindow::on_tabWidget_currentChanged(int index)
{qDebug()<<index;
    if(index==1)
    {
        ui->plainTextEdit->document()->setPlainText(ui->editor->document()->toHtml());}
    else {
        ui->editor->document()->setHtml(ui->plainTextEdit->document()->toPlainText());
    }
}

void MainWindow::on_actionImage_Left_triggered()
{
    if(image.isValid())
    {qDebug()<<image.name();
        QString name=image.name();
        // image.setProperty(QTextFormat::CssFloat,QTextFrameFormat::FloatLeft);
        //image.doubleProperty()
        //image.toFrameFormat().setPosition(QTextFrameFormat::FloatLeft);
        // qDebug()<<image.toFrameFormat().position();
        // qDebug()<<ui->editor->document()->findBlock(lastcursor.blockNumber()).text();
        // ui->editor->document()->findBlock(lastcursor.blockNumber());

        //      QTextFrameFormat f=image.toFrameFormat();
        //      f.setPosition(QTextFrameFormat::FloatLeft);
        //

        //QTextFrameFormat ffmt;
        //     ffmt.setPosition(QTextFrameFormat::FloatLeft);
        //  image.merge(ffmt);
        ;
        //    QTextCursor cursor = ui->editor->textCursor();

        //cursor.insertText(QString(QChar::ReplacementCharacter), ffmt);
        //image.merge(lastcursor.currentFrame()->setFrameFormat(ffmt));
        //lastcursor.setCharFormat(image);
        QString data=ui->editor->document()->toHtml();
        int i = data.indexOf(QString("<img src=\""+name+"\""));
        qDebug()<<i;qDebug()<< data.indexOf("/>",i) ;
        if (i > 0){
            if(ui->actionImage_Right->isEnabled()==false )
            {
                int ii=data.indexOf("style=",i);
                if(ii>0)
                    data.replace(ii,data.indexOf("\"",ii+7)," style=\"float: left;\"");
            }
            else  data.insert(data.indexOf("/>",i) -1," style=\"float: left;\""); //data.remove(i, data.indexOf("/>",i)-i + 2);
        }
        ui->editor->document()->setHtml(data);
        // lastcursor.insertImage(image,QTextFrameFormat::FloatLeft);
        // ui->editor->insertHtml("<img style='float: left'src='"+name+"'></img>");
        //lastcursor.insertHtml("<img style='float: left'src='"+name+"'></img>");

        ui->actionImage_Left->setEnabled(false);
        ui->actionImage_Default->setEnabled(true);
        ui->actionImage_Right->setEnabled(true);

    }
    else {
        ui->imgtool->setVisible(false);
    }
}

void MainWindow::on_actionImage_Right_triggered()
{
    if(image.isValid())
    {qDebug()<<image.name();
        QString name=image.name();
        //   ui->editor->document()->findBlock(lastcursor.blockNumber()).text().clear();
        //    lastcursor.insertHtml("<img style='float: right'src='"+name+"'></img>");
        QString data=ui->editor->document()->toHtml();
        int i = data.indexOf(QString("<img src=\""+name+"\""));
        if(i>0) {
            if(ui->actionImage_Left->isEnabled()==false)
            {
                int ii=data.indexOf("style=",i);
                if(ii>0)
                    data.replace(ii,data.indexOf("\"",ii+7)," style=\"float: right;\"");
            }
            else  data.insert(data.indexOf("/>",i) -1," style=\"float: right;\"");
        }

        //data.remove(i, data.indexOf("/>",i) + 2);
        ui->editor->document()->setHtml(data);
        //lastcursor.insertImage(image,QTextFrameFormat::FloatRight);
        ui->actionImage_Left->setEnabled(true);
        ui->actionImage_Default->setEnabled(true);
        ui->actionImage_Right->setEnabled(false);


    }
    else {
        ui->imgtool->setVisible(false);
    }
}

void MainWindow::on_actionImage_Default_triggered()
{
    if(image.isValid())
    {qDebug()<<image.name();
        QString name=image.name();


        QString data=ui->editor->document()->toHtml();
        int i = data.indexOf(QString("<img src=\""+name+"\""));
        if (i > 0){
            if(ui->actionImage_Left->isEnabled()==false || ui->actionImage_Right->isEnabled()==false )
            {
                int ii=data.indexOf("style=",i);
                if(ii>0)
                    data.replace(ii,data.indexOf("\"",ii+7),"style=\"float: none;\"");
            }
            //else data.insert(data.indexOf("/>",i) -1," style=\"float: none;\""); //data.remove(i, data.indexOf("/>",i) + 2);
        }


        ui->editor->document()->setHtml(data);
        //lastcursor.insertImage(image);
        ui->actionImage_Left->setEnabled(true);
        ui->actionImage_Default->setEnabled(false);
        ui->actionImage_Right->setEnabled(true);

    }
    else {
        ui->imgtool->setVisible(false);
    }
}
#include "aliasgui/imgprop.h"
void MainWindow::on_actionImage_Settings_triggered()
{
    imgprop* ip=new imgprop();

    qDebug()<<image.height();
    ip->setimage(image);
    if(ip->exec() && ip->result()==QDialog::Accepted ){
        //  lastcursor.setCharFormat(ip->getimage());
        // lastcursor.setCharFormat(image);
        QString name=image.name();
        QString data=ui->editor->document()->toHtml();
        int i = data.indexOf(QString("<img src=\""+name+"\""));
        qDebug()<<i;qDebug()<< data.indexOf("/>",i) ;
        if (i > 0)
            data.insert(data.indexOf("/>",i) -1,ip->getimage());// remove(i, data.indexOf("/>",i) + 2);
        ui->editor->document()->setHtml(data);
    }
    delete ip;
}

void MainWindow::on_books_currentChanged(int index)
{if(db.isOpen()){
        if (index==0 || index==2)ui->blist->setEnabled(false);
        else ui->blist->setEnabled(true);}
}

void MainWindow::on_actionEdit_Article_triggered()
{
    if(ui->booktree->currentItem()->isSelected() && ui->booktree->currentItem()->data(0,Qt::UserRole+1).toBool()){
      //  if(ui->booktree->currentItem()->data(0,Qt::UserRole+1).toBool()){
            sqlindex=ui->booktree->currentItem()->data(0,32).toInt();
            QSqlQuery query("SELECT * FROM articles WHERE id='"+ui->booktree->currentItem()->data(0,32).toString()+"'");
            query.exec();query.next();
            //ui->actionNew->trigger();
            /// need to rewrite function NEW
            ui->stackedWidget->setCurrentWidget(ui->weditor); ;
            imglist.clear();

            ui->txtedit->setVisible(true);
            ui->editor->document()->clear();
            ui->blist->setVisible(false);
            saved=false;
            ///
            ui->doctitle->setText(query.value(1).toString());
            //ui->editor->document()->setHtml(query.value(2).toString());
            QString data=query.value(2).toString();
            QRegExp rx("<pre[^>]*>([^<]*)</pre>");
            rx.setMinimal(true);

            QStringList list;
            int pos = 0;
            while((pos = rx.indexIn( data, pos)) != -1)
            {
                list << rx.cap(1);
                pos += rx.matchedLength();

            }

            for( int n = 0; n < list.size(); n++)
            {
                QString szTmp = list.at( n);
                szTmp.replace( "\n", "<br />");
                data.replace( list.at( n), szTmp);
            }

            data.replace("<pre class","[prevclass");
            data.replace("id=\"syntaxhighlight\">","pclass]");//"&gt;
            data.replace("</pre>",QString("[/preclass]"));
            data.replace(QString("{imgpath}"),bookpath+"img/");
            imglist.clear();
            QRegExp rx1("<img[^>]src=\"([^<]*)\"*/>");
                rx1.setMinimal(true);

                QStringList list1;
                 pos = 0;
                while((pos = rx1.indexIn( data, pos)) != -1)
                {
                   list1 << rx1.cap(1);
                   pos += rx1.matchedLength();

                }

                for( int n = 0; n < list1.size(); n++)
                {
                  //   while (!resault) { qApp->processEvents(QEventLoop::WaitForMoreEvents | QEventLoop::ExcludeUserInputEvents); }
                   QString szTmp = list1.at( n);
                   qDebug()<<szTmp;
                  // szTmp.replace("{imgpath}",bookpath+"/img/");
                   imglist<<szTmp;

                  // szTmp.replace( "\n", "<br />");
                   //data.replace( list.at(n), szTmp);
                }
                qDebug()<< imglist;
            ui->editor->clear();
            ui->editor->append(data);
            saved=false;


       // }
       // else
       // {
        //    msgBox.setText(QString::fromUtf8("Вы не выбрали документ."));
       //     msgBox.setInformativeText(QString::fromUtf8("Вы не можете редактировать докумет"));
            /// msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
       //     msgBox.setIcon(QMessageBox::Warning);
            ///  msgBox.setDefaultButton(QMessageBox::Cancel);
       //     msgBox.exec();
       // }
    }
    else
    {
        msgBox.setText(QString::fromUtf8("Вы не выбрали документ."));
        msgBox.setInformativeText(QString::fromUtf8("Вы не можете редактировать докумет"));
        /// msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        msgBox.setIcon(QMessageBox::Warning);
        /// msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.exec();
    }
}

void MainWindow::on_actionAdd_Link_triggered()
{href *link=new href();
    if (lastcursor.hasSelection())
    {
        link->set(lastcursor.selectedText(),lastcursor.charFormat().anchorHref().isEmpty()?"http://":lastcursor.charFormat().anchorHref());
    }
    if(link->exec() && link->result()==QDialog::Accepted){
        QTextDocumentFragment fragment = QTextDocumentFragment::fromHtml(link->gethref());
        ui->editor->textCursor().insertFragment(fragment);
    }
}

void MainWindow::on_actionSyncronize_triggered()
{
    syncmain *s=new syncmain(this);
    db.close();
    db.removeDatabase(db.connectionName());
    ui->blist->setEnabled(false);
    ui->books->widget(1)->setEnabled(false);
    ui->books->setCurrentIndex(0);
    s->exec();
    db = QSqlDatabase::addDatabase("QSQLITE");
    this->init_books();
}
/// #include <QWebFrame>
void MainWindow::on_actionExport_PDF_triggered()
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
        ///   QWebFrame *frame=ui->helview->page()->mainFrame();
        ui->helview->print(&printer);
    }
    //! [0]
}
#include <aliasgui/syntaxhilight.h>
void MainWindow::on_actionInsert_code_triggered()
{
    syntaxhilight* syntax=new syntaxhilight(this);
    if(syntax->exec()== QDialog::Accepted)
    {
        // QTextDocumentFragment fragment = QTextDocumentFragment::fromPlainText(syntax->gethtml());
        //fragment.fromPlainText()
        //   ui->editor->setAutoFormatting(
        //ui->editor->document()->begin();
        lastcursor=ui->editor->textCursor();
       // lastcursor.beginEditBlock();
        lastcursor.insertHtml(syntax->gethtml());
       // lastcursor.endEditBlock();
       // ui->editor->document()->end();

        //ui->editor->insertHtml(syntax->gethtml());
    }
    delete syntax;
}
#include <aliasgui/settings.h>
void MainWindow::on_actionSettings_triggered()
{
    Settings* set=new Settings(this) ;
    if(set->exec()==QDialog::Accepted){  MainWindow::initSettings();}

   delete set;
}
#include <QDesktopServices>
void MainWindow::on_actionMain_Site_triggered()
{
    QDesktopServices::openUrl(QUrl("http://qhda.krabik.co.ua/", QUrl::TolerantMode));
}

void MainWindow::on_actionReport_For_new_Bug_triggered()
{//http://localhost/bugs/#tabs-3
     QDesktopServices::openUrl(QUrl("http://qhda.krabik.co.ua/bugs/#tabs-3", QUrl::TolerantMode));
}

void MainWindow::on_startSearch_clicked()
{//select * from articles where body like '%gl%'
    ui->sresult->clear();
    QSqlQuery query("select * from articles where body like '%"+ui->searchstr->text()+"%'");
    query.exec();
   if(query.lastError().isValid())
    {
       msgBox.setText("Database Error : "+query.lastError().text());
       msgBox.exec();
       return;
   }
   while(query.next())
    { QListWidgetItem* item=new QListWidgetItem(ui->sresult);
       item->setText(query.value(1).toString());
       item->setData(32,QVariant(query.value(0)));
       ui->sresult->addItem(item);
   }


}



void MainWindow::on_bookitems_customContextMenuRequested(QPoint pos)
{
    if(ui->bookitems->currentItem()->isSelected()){
QMenu contextMenu(tr("Context menu"), this);

contextMenu.addAction(ui->actionRemove_Book);

contextMenu.exec(ui->bookitems->mapToGlobal(pos));
}
}

void MainWindow::on_actionRemove_Book_triggered()
{
    msgBox.setText(QString::fromUtf8("Удалить справочник."));
    msgBox.setInformativeText(QString::fromUtf8("Удалиться только запись в настройках программы все файлы остануться "));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    if(msgBox.exec()==QMessageBox::Yes)
    { if(settings.group()!="Books")
        settings.beginGroup("Books");
        settings.remove(ui->bookitems->currentItem()->text());
        MainWindow::init_books();
    }
}
