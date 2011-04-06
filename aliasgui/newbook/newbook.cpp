#include "newbook.h"
#include "ui_newbook.h"
newbook::newbook(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::newbook)
{
    m_ui->setupUi(this);
m_ui->pathto->setText(QApplication::applicationDirPath()+"/books");
m_ui->dbname->setLocale(QLocale::English);
}

newbook::~newbook()
{
    delete m_ui;
}

void newbook::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;

    default:
        break;
    }
}

void newbook::on_buttonBox_rejected()
{
 delete m_ui;
}

void newbook::on_pushButton_clicked()
{
QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
if(!dir.isEmpty())
    m_ui->pathto->setText(dir);
}

void newbook::on_iconchoose_clicked()
{
 filename = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                 "",
                                                 tr("Images (*.png)"));
 if (!filename.isEmpty())
    m_ui->iconchoose->setIcon(QIcon(filename));

}
void newbook::setbook(QString name, QString descr)
{
    m_ui->helpbookname->setText(name);
    m_ui->descr->append(descr);
}

void newbook::on_buttonBox_accepted()
{QFileInfo fi(filename);
 fi.completeBaseName();
// try{
 QDir *dir=new QDir();
 if(dir->mkdir(m_ui->pathto->text()+"/"+m_ui->dbname->text())){
    QString dbpath=m_ui->pathto->text()+"/"+m_ui->dbname->text()+"/";
    QFile::copy(filename,dbpath+fi.fileName() );
    QSettings books(dbpath+"settings.ini",QSettings::IniFormat);
    books.setValue("bookname",m_ui->helpbookname->text());
    books.setValue("bookdescr",m_ui->descr->toPlainText());
    books.setValue("bookpath",m_ui->pathto->text()+"/"+m_ui->dbname->text());
    books.setValue("bookimgpath","img");
    dir->mkdir(dbpath+"/img");
    books.setValue("bookicon",fi.fileName());
     books.setValue("bookdb",m_ui->dbname->text()+".db");
    QSettings setting;
    setting.beginGroup("Books");
    setting.setValue(m_ui->helpbookname->text(),dbpath);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
     db.setDatabaseName(dbpath+m_ui->dbname->text()+".db");
     if (!db.open()) {
         QMessageBox::critical(0, tr("Cannot open database"),
             tr("Cannot open database."), QMessageBox::Cancel);
         return;
     }
     QSqlQuery query;
     query.exec("create table general ("
                "bokname text, descr text,hash text,articles int)");
     query.exec("create table bookcat (id INTEGER PRIMARY KEY AUTOINCREMENT, "
                "name varchar(20), descr text,parent int default 0, subcat int default 0)");
     query.exec("create table articles (id INTEGER PRIMARY KEY AUTOINCREMENT, "
                "name text, body text,author varchar(50),pdate datetime,md5 text,catid int)");
     db.close();
}
//}catch(){}
}



