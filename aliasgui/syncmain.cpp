#include "syncmain.h"
#include "ui_syncmain.h"
#include <QLatin1String>
#include <aliasgui/adifference.h>

syncmain::syncmain(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::syncmain)
{
    ui->setupUi(this);


    dbs=QSqlDatabase::addDatabase("QSQLITE");
    ///qDebug()<<dbs.driver()->hasFeature(QSqlDriver::LastInsertId);
    client = new xmlrpc::Client(this);
    ///client->setUserAgent("Firefox/3.5.8");

    connect( client, SIGNAL(done( int, QVariant )),
             this, SLOT(processReturnValue( int, QVariant )) );
    connect( client, SIGNAL(failed( int, int, QString )),
             this, SLOT(processFault( int, int, QString )) );
    QSettings settings;
    settings.endGroup();
    settings.beginGroup("web");
    host=settings.value("xmlrpcurl").toString();
    xmlport=settings.value("xmlrpcport",80).toInt();
    xmlrpcuri=settings.value("xmlrpcuri","/").toString();
    client->setHost(host,xmlport,xmlrpcuri);
    settings.endGroup();
    error=false;
    ui->wlog->setVisible(false);;
}

syncmain::~syncmain()
{dbs.close();
    dbs.removeDatabase(dbs.connectionName());
    delete ui;
}

void syncmain::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    case QEvent::Close: {
            dbs.close();
            ///qDebug()<<"close";  dbs.removeDatabase(dbs.connectionName());
            break;
        }
    default:
        break;
    }
}
/// start Xml-Rpc client functions
void syncmain::processReturnValue( int requestId, QVariant value )
{
    if ( requestId == requestIdSum )
        id=value.toInt();

    if ( requestId == requestbooks )
        booksrpc.append(value.toStringList());
    //ifexistsbooks
    if ( requestId == ifexistsbooks )
        id=value.toInt();

    resault=true;
}

void syncmain::processFault( int requestId, int errorCode, QString errorString )
{
    Q_UNUSED( requestId );

    QMessageBox::warning(this, tr("Request failed"),
                         QString("XML-RPC request  failed.\n\nFault code: %1\n%2\n") \
                         .arg(errorCode).arg(errorString),
                         QMessageBox::Ok );
    resault=true;error=true;
    syncmain::close();

}
/// end of Xml-Rpc client functions
/// Here functions for upload books to site
void syncmain::addbook(QString command)
{resault=true;
    QSqlQuery query("SELECT Count(*) FROM articles");
    query.next();
    ui->pbar->setMaximum(query.value(0).toInt());
    ui->articleall->setText(query.value(0).toString());
    query.clear();
    query.exec("SELECT Count(*) FROM bookcat");
    query.next();
    ui->catall->setText(query.value(0).toString());
    ui->pbar->setMaximum(ui->pbar->maximum()+query.value(0).toInt());
    //   while (!resault) { qApp->processEvents(QEventLoop::WaitForMoreEvents | QEventLoop::ExcludeUserInputEvents); }
    if(command=="add" )
    {
        ui->log->addItem("Add book "+bname);
        if(!error)
        {  resault=false;
            QList<xmlrpc::Variant > q;
            q.append("1");
            q.append(bname);
            q.append(bdescr);
            /// не знаю  почему но этот код работает на моем серваку
            /// скорей всего из-за закрытия соединения
            delete client;
            client = new xmlrpc::Client(this);
            connect( client, SIGNAL(done( int, QVariant )),
                     this, SLOT(processReturnValue( int, QVariant )) );
            connect( client, SIGNAL(failed( int, int, QString )),
                     this, SLOT(processFault( int, int, QString )) );
            client->setHost(host,xmlport,xmlrpcuri);
            /// удалить если у Вас работает без него
            requestIdSum = client->request(q, command);//"add"
            while (!resault) { qApp->processEvents(QEventLoop::WaitForMoreEvents | QEventLoop::ExcludeUserInputEvents); }
        }
        else
        { return ;}


    }
    syncmain::catup(id,command);
}
void syncmain::catup(int bookid,QString command)
{
    resault=false;
    QSqlQuery query("SELECT * FROM bookcat WHERE parent=1");
    while (query.next() && !error) {
        QList<xmlrpc::Variant > q;
        q.append(2);
        q.append(query.value(1).toString());

        q.append(bookid);
        q.append((int)1);
        q.append((int)0);

        /// не знаю  почему но этот код работает на моем серваку
        /// скорей всего из-за закрытия соединения

        delete client;
        client = new xmlrpc::Client(this);
        connect( client, SIGNAL(done( int, QVariant )),
                 this, SLOT(processReturnValue( int, QVariant )) );
        connect( client, SIGNAL(failed( int, int, QString )),
                 this, SLOT(processFault( int, int, QString )) );
        client->setHost(host,xmlport,xmlrpcuri);
        /// удалить если у Вас работает без него
        requestIdSum = client->request(q,command);

        resault=false;
        while (!resault) {
            qApp->processEvents(QEventLoop::WaitForMoreEvents | QEventLoop::ExcludeUserInputEvents);
        }
        ui->catcurr->setText(QString::number( ui->catcurr->text().toInt()+1));
        ui->log->addItem("Added category "+query.value(1).toString());
        int val=ui->pbar->value();
        ui->pbar->setValue(++val);
        int parent=id;
        syncmain::article(parent,query.value(0).toString(),command);
        syncmain::subcat(parent,query.value(0).toString(),bookid,command);
    }
}
void syncmain::article(int cat,QString catsql,QString command)
{
    QSqlQuery article("SELECT * FROM articles WHERE catid='"+catsql+"'");
    while (article.next() && !error) {
        while (!resault) { qApp->processEvents(QEventLoop::WaitForMoreEvents | QEventLoop::ExcludeUserInputEvents); }
        QList<xmlrpc::Variant> q;
        q.append(4);
        q.append(article.value(1).toString());
        syncmain::bookimages(article.value(2).toString(),command);
        q.append(article.value(2).toString().toUtf8());//body
        q.append(article.value(3).toString());//author
        q.append(article.value(4).toString());//pdate
        q.append(article.value(5).toString());//md5
        q.append(cat);//catid
        /// не знаю  почему но этот код работает на моем серваку
        /// скорей всего из-за закрытия соединения
        delete client;
        client = new xmlrpc::Client(this);
        connect( client, SIGNAL(done( int, QVariant )),
                 this, SLOT(processReturnValue( int, QVariant )) );
        connect( client, SIGNAL(failed( int, int, QString )),
                 this, SLOT(processFault( int, int, QString )) );
        client->setHost(host,xmlport,xmlrpcuri);
        /// удалить если у Вас работает без него
        requestIdSum = client->request(q,command);
        resault=false;
        ui->articlecurr->setText(QString::number( ui->articlecurr->text().toInt()+1));
        ui->log->addItem("Added article "+article.value(1).toString());
        int val=ui->pbar->value();
        ui->pbar->setValue(++val);
    }
}
void syncmain::bookimages(QString data,QString command)
{
    QRegExp rx("<img[^>]src=\"([^<]*)\"*/>");
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
        //   while (!resault) { qApp->processEvents(QEventLoop::WaitForMoreEvents | QEventLoop::ExcludeUserInputEvents); }
        QString szTmp = list.at( n);
        qDebug()<<szTmp;
        szTmp.replace("{imgpath}",bpath+"img/");
        szTmp.replace('"',"");
        szTmp.replace(' ',"");

        // szTmp.replace( "\n", "<br />");
        // data.replace( list.at( n), szTmp);
    }

}

void syncmain::subcat(int cat,QString catsql,int bookid,QString command)
{ while (!resault) { qApp->processEvents(QEventLoop::WaitForMoreEvents | QEventLoop::ExcludeUserInputEvents); }
    QSqlQuery query("SELECT * FROM bookcat WHERE subcat='"+catsql+"'");
    while (query.next() && !error) {
        while (!resault) { qApp->processEvents(QEventLoop::WaitForMoreEvents | QEventLoop::ExcludeUserInputEvents); }
        QList<xmlrpc::Variant > q;
        q.append(2);
        q.append(query.value(1).toString());
        q.append(bookid);
        q.append((int)0);
        q.append(cat);
        /// не знаю  почему но этот код работает на моем серваку
        /// скорей всего из-за закрытия соединения
        delete client;
        client = new xmlrpc::Client(this);
        connect( client, SIGNAL(done( int, QVariant )),
                 this, SLOT(processReturnValue( int, QVariant )) );
        connect( client, SIGNAL(failed( int, int, QString )),
                 this, SLOT(processFault( int, int, QString )) );
        client->setHost(host,xmlport,xmlrpcuri);
        /// удалить если у Вас работает без него
        requestIdSum = client->request(q,command);
        resault=false;
        while (!resault) { qApp->processEvents(QEventLoop::WaitForMoreEvents | QEventLoop::ExcludeUserInputEvents); }
        ui->catcurr->setText(QString::number( ui->catcurr->text().toInt()+1));
        ui->log->addItem("Added category "+query.value(1).toString());
        int val=ui->pbar->value();
        ui->pbar->setValue(++val);
        int parent=id;
        syncmain::article(parent,query.value(0).toString(),command);
        syncmain::subcat(parent,query.value(0).toString(),bookid,command);
    }
}

void syncmain::on_uploadgo_clicked()
{
    resault=false;
    bool exesting=false;
    ui->noiterms->setVisible(false);
    requestbooks=client->request("books");
    while (!resault) { qApp->processEvents(QEventLoop::WaitForMoreEvents | QEventLoop::ExcludeUserInputEvents); }
    QSettings settings;
    if(settings.group()!="Books")
        settings.beginGroup("Books");
    QStringList keys = settings.childKeys();
    int i=0;
    while(i<keys.count()){
        QListWidgetItem *item=new QListWidgetItem();
        QSettings books(settings.value(keys[i],"").toString()+"/settings.ini",QSettings::IniFormat);
        if(!booksrpc.contains(books.value("bookname","").toString(),Qt::CaseInsensitive	))
        { exesting=true;
            item->setText(books.value("bookname","").toString());
            item->setIcon(QIcon(settings.value(keys[i],"").toString()+books.value("bookicon","").toString()));
            item->setToolTip(books.value("bookdescr","").toString());
            item->setData(32,QVariant(settings.value(keys[i],"").toString()+books.value("bookdb","").toString()));
            item->setData(33,QVariant(settings.value(keys[i],"").toString()));
            ui->books->addItem(item);
        }
        ++i;
    }
    if (!exesting) ui->noiterms->setVisible(true);
    ui->stack->setCurrentWidget(ui->upload);
}

void syncmain::on_books_itemDoubleClicked(QListWidgetItem* item)
{
    if(dbs.isOpen())
    { dbs.close();}
    bpath=item->data(33).toString();
    bdescr=item->toolTip();
    bname=item->text();
    dbs.setDatabaseName( item->data(32).toString());

    if (!dbs.open()) {
        QMessageBox::critical(0, tr("Cannot open database"),
                              tr("Cannot open database."), QMessageBox::Ok);
        return;
    }ui->wlog->setVisible(true);
    syncmain::addbook("add");
    QMessageBox::information(0, tr("Transfer"),
                          tr("Transfer data complete."), QMessageBox::Ok);
}

void syncmain::on_syncmain_destroyed()
{
    dbs.close();
    dbs.removeDatabase(dbs.connectionName());
}
/// end's a section where functions for upload book
/// Section where download full information for updating local books from site content
void syncmain::on_downgo_clicked()
{
    httperror=false;
    syncmain::download(QUrl("http://"+host+"/welcome/xml"));
    while (!resault) { qApp->processEvents(QEventLoop::WaitForMoreEvents | QEventLoop::ExcludeUserInputEvents); }
    if(!httperror){
        QFile file(QDir::tempPath ()+"/hda.xml");
        if(!file.open(QIODevice::ReadOnly))
        {
            ///qDebug()<<"error";
        }
        /// QDomDocument xml("booksxml");

        ui->stack->setCurrentWidget(ui->download);
        xml.setContent(&file);
        if(xml.documentElement().hasAttributes())
            ///qDebug()<< xml.documentElement().nodeName();
        { QDomElement attr=xml.documentElement();
            ui->sitearticles->setText(ui->sitearticles->text()+attr.attribute("articlenum",""));
            ui->sitecat->setText(ui->sitecat->text()+ attr.attribute("catnum",""));
            ui->siteregbooks->setText(ui->siteregbooks->text()+attr.attribute("num",""));

            ui->pball->setMaximum(attr.attribute("sum","").toInt());

        }
        // booklist
        syncmain::initbooks();
    }

}
void syncmain::initbooks()
{
    booklist.clear();
    QSettings settings;
    if(settings.group()!="Books")
        settings.beginGroup("Books");
    QStringList keys = settings.childKeys();
    int i=0;
    ui->localbookscount->setText(QString::number(keys.count()));
    while(i<keys.count()){
        QSettings books(settings.value(keys[i],"").toString()+"/settings.ini",QSettings::IniFormat);
        booklist.insert(books.value("bookname","").toString(),settings.value(keys[i],"").toString()+books.value("bookdb","").toString());
        ++i;
    }
}

void syncmain::download(QUrl url)
{
    progressDialog = new QProgressDialog(this);
    request.setUrl(url);
    request.setRawHeader("User-Agent", "HDA");
    QNetworkReply *reply=manager.get(request);
    connect(&manager, SIGNAL(finished(QNetworkReply*)) , this, SLOT(readydown(QNetworkReply*)));
    connect(reply, SIGNAL(downloadProgress (qint64,qint64)),
            this, SLOT(updateDataReadProgress(qint64,qint64)));

    progressDialog->setWindowTitle(tr("Download"));
    progressDialog->adjustSize();
    progressDialog->show();;

}
void syncmain::updateDataReadProgress(qint64 received, qint64 total)
{
    // progressDialog->setValue((int) total / received);
    progressDialog->setMaximum(total);
    progressDialog->setValue(received);
}

void syncmain::readydown(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QFile file(QDir::tempPath ()+"/hda.xml");
        if(!file.open(QIODevice::WriteOnly))
        {
            ///qDebug()<<"error";
        }
        file.write(reply->readAll());
        file.close();

    }
    // Some http error received
    else
    { httperror=true;
        QMessageBox::critical(0, tr("Network error"),
                              tr("Error:")+reply->errorString(), QMessageBox::Ok);
        //return; // handle errors here
        resault=true;
        syncmain::close();
    }

    // We receive ownership of the reply object
    // and therefore need to handle deletion.
    //delete reply;
    resault=true;
    reply->close();
    progressDialog->close();
}

void syncmain::on_begin_clicked()
{
    QDomNode tnode;
    QDomElement elem;

    for(int i=0;i<xml.documentElement().childNodes().count();i++)
    {
        int tmp=ui->pball->value();
        ui->pball->setValue(++tmp);
        QDomNode node=xml.documentElement().childNodes().item(i);
        elem=node.toElement();
        if(!booklist.contains(elem.attribute("name",""))){
            syncmain::new_book(elem.attribute("name",""),elem.attribute("descr",""));
            syncmain::initbooks();
            dbs=QSqlDatabase::addDatabase("QSQLITE");
        }
        if(booklist.contains(elem.attribute("name",""))){
            if(dbs.open()) {dbs.close();}
            dbs.setDatabaseName( booklist.value(elem.attribute("name","")));

            if (!dbs.open()) {
                QMessageBox::critical(0, tr("Cannot open database"),
                                      "Cannot open database."+dbs.lastError().text(), QMessageBox::Ok);
                return;
            }
            syncmain::lmapins();
            ui->wlog->setVisible(true);
            ui->log->addItem("Found book "+elem.attribute("name",""));
            if(node.hasChildNodes())
            {
                for(int w=0;w<node.childNodes().count();w++)
                {
                    int tmp=ui->pball->value();
                    ui->pball->setValue(++tmp);
                    tnode=node.childNodes().item(w) ;
                    elem=tnode.toElement();
                    if (tnode.nodeName()=="cat" && !lmap.contains(elem.attribute("name","")))
                    {ui->log->addItem("Not Found category "+elem.attribute("name","")+" in current book trieng to add");
                        QSqlQuery query("insert into  bookcat('name','parent','subcat') VALUES ('"+elem.attribute("name","")+"','1','0')");
                        if(query.lastError().isValid()) { ui->log->addItem("Error "+query.lastError().text());}
                        else
                        {
                            lmap.insert(elem.attribute("name",""),query.lastInsertId().toInt());

                        }
                    }
                    syncmain::parse(tnode,lmap.value(elem.attribute("name","")),0);
                }
            }

            else {
                /// not found in local we must create with confirmation dialog
                QMessageBox::critical(0, tr("Book not found"),
                                      tr("Cannot find book in application settings."), QMessageBox::Ok);
                return;
            }
        }
    }
}
#include "newbook/newbook.h"
void syncmain::new_book(QString name,QString descr)
{
    newbook *nb=new newbook();
    nb->setbook(name,descr);
    if(nb->exec()== QDialog::Accepted)
    {
        syncmain::initbooks();
    }
}

void syncmain::parse(QDomNode node,int dparent,int dsub)
{ int parent,sub;
    QDomNode tnode;
    if(node.hasChildNodes())
    {
        for(int w=0;w<node.childNodes().count();w++)
        {/// ui->log->addItem("Found book "+elem.attribute("name",""));
            int tmp=ui->pball->value();
            ui->pball->setValue(++tmp);
            /// QDomElement pelem=node.toElement();

            tnode=node.childNodes().item(w) ;
            QDomElement elem=tnode.toElement();

            if(tnode.nodeName()=="cat" )///&& tnode.hasChildNodes()
            {
                QSqlQuery query("SELECT * FROM bookcat WHERE name='"+elem.attribute("name","")+"'");
                /// lmap.contains(elem.attribute("name",""))
                query.exec();
                if(query.next())
                { ui->log->addItem("Found category "+elem.attribute("name",""));
                    ///qDebug()<<"found :  "+elem.attribute("name","");
                    parent=query.value(3).toInt();
                    sub=query.value(4).toInt();
                }
                else
                {///create cat name
                    ui->log->addItem("Not Found category "+elem.attribute("name","")+" in current book trieng to add");
                    QSqlQuery query("insert into  bookcat('name','parent','subcat') VALUES ('"+elem.attribute("name","")+"','0','"+QString::number(dparent)+"')");
                    ///qDebug()<<"not found :   "+elem.attribute("name","");

                    //query.exec() ;
                    if(query.lastError().isValid()) { ui->log->addItem("Error "+query.lastError().text());}
                    else
                    {
                        ///qDebug()<<query.lastInsertId();
                        QSqlQuery data("SELECT * FROM bookcat WHERE name='"+elem.attribute("name","")+"'");
                        data.exec() ;
                        if( data.next())
                        {
                            parent=data.value(0).toInt();
                            sub=data.value(4).toInt();
                            lmap.insert(elem.attribute("name",""),query.lastInsertId().toInt());

                        }
                    }

                }
                syncmain::parse(tnode,parent,sub);

            }
            if (tnode.nodeName()=="article")
            {
                ui->log->addItem("Found article  "+elem.attribute("title",""));
                // ///qDebug()<<"found article  :   "+elem.attribute("title","");
                QSqlQuery query("SELECT * FROM articles WHERE name='"+elem.attribute("title","")+"'");

                if (query.next())
                {//query.exec()
                    ;
                    // ///qDebug()<<"found in db article  :   "+elem.attribute("title","");
                    if(query.value(5).toString()!=elem.attribute("md5",""))
                    {
                        adifference *adiff=new adifference(this);
                        adiff->setsitetext(elem.text());
                        adiff->setdbtext(query.value(2).toString());
                        if(adiff->exec()==QDialog::Accepted){
                            dbs.exec("update articles set name='"+elem.attribute("title","")+"',body='"+elem.text()+"',catid='"+QString::number(lmap.value(tnode.parentNode().toElement().attribute("name","")))+
                                     "',author='"+elem.attribute("author","")+"',pdate=datetime('now'),md5='"+elem.attribute("md5","")+"' WHERE id='"+query.value(0).toString()+"'");
                            if(dbs.lastError().isValid()) { ui->log->addItem("Error "+query.lastError().text());}
                        }
                    }

                }
                else
                {/////qDebug()<<"not found in db article  :   "+elem.attribute("title","");
                    ui->log->addItem("Not Found article  "+elem.attribute("title","")+"in current category");
                    QString sql="insert into articles ('name','body','catid','author','pdate','md5') values('"+elem.attribute("title","")+"','"
                                +elem.text()+"','"+QString::number(lmap.value(tnode.parentNode().toElement().attribute("name","1")))+ ///QString::number(dparent)
                                "','"+elem.attribute("author","")+"',datetime('now'),'"+elem.attribute("md5","")+"')";
                    sql.replace("\\\"","\"");
                    sql.replace("\\n","");

                    dbs.exec(sql);
                    if(dbs.lastError().isValid()) ui->log->addItem("Error adding article  "+elem.attribute("title","")+" to current category");
                    /// ///qDebug()<< dbs.lastError();
                }

            }
        }

    } /// node.has child
}

void syncmain::lmapins()
{
    lmap.clear();
    QSqlQuery query("SELECT * FROM bookcat");
    while(query.next())
    {
        lmap.insert(query.value(1).toString(),query.value(0).toInt());
    }

}

void syncmain::on_syncsite_clicked()
{ui->stack->setCurrentWidget(ui->upload);
    ui->noiterms->setVisible(false);
    QSettings settings;
    if(settings.group()!="Books")
        settings.beginGroup("Books");
    QStringList keys = settings.childKeys();
    int i=0;
    while(i<keys.count()){
        QListWidgetItem *item=new QListWidgetItem();
        QSettings books(settings.value(keys[i],"").toString()+"/settings.ini",QSettings::IniFormat);
        item->setText(books.value("bookname","").toString());
        item->setIcon(QIcon(settings.value(keys[i],"").toString()+books.value("bookicon","").toString()));
        // item->setToolTip(books.value("bookdescr","").toString());
        // item->setData(32,QVariant(settings.value(keys[i],"").toString()+books.value("bookdb","").toString()));
        // item->setData(33,QVariant(settings.value(keys[i],"").toString()));
        item->setFlags(Qt::NoItemFlags);
        ui->books->addItem(item);
        if(dbs.isOpen())
        { dbs.close();}
        bpath=settings.value(keys[i],"").toString();
        bdescr=books.value("bookdescr","").toString();
        bname=books.value("bookname","").toString();
        dbs.setDatabaseName( settings.value(keys[i],"").toString()+books.value("bookdb","").toString());

        if (!dbs.open()) {
            QMessageBox::critical(0, tr("Cannot open database"),
                                  tr("Cannot open database."), QMessageBox::Ok);
            return;
        }
        ui->wlog->setVisible(true);
        resault=false;
        /// не знаю  почему но этот код работает на моем серваку
        /// скорей всего из-за закрытия соединения

        delete client;
        client = new xmlrpc::Client(this);
        connect( client, SIGNAL(done( int, QVariant )),
                 this, SLOT(processReturnValue( int, QVariant )) );
        connect( client, SIGNAL(failed( int, int, QString )),
                 this, SLOT(processFault( int, int, QString )) );
        client->setHost(host,xmlport,xmlrpcuri);
        /// удалить если у Вас работает без него
        ifexistsbooks=client->request("ifexistbook",books.value("bookname","").toString());
        while (!resault) { qApp->processEvents(QEventLoop::WaitForMoreEvents | QEventLoop::ExcludeUserInputEvents); }
        /// id==1 found; id==0 not found
        if(id>0){
            syncmain::addbook("update");
        }
        else { syncmain::addbook("add");}
        ++i;
    }
    QMessageBox::information(0, tr("Transfer"),
                          tr("Transfer data complete."), QMessageBox::Ok);

}
