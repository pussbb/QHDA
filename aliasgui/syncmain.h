#ifndef syncmain_H
#define syncmain_H
#include <QDialog>
#include "3thd/xmlrpc/client.h"
#include "QtSql"
#include "QListWidgetItem"
#include "QMessageBox"
#include <QFile>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDomDocument>
#include <QProgressDialog>
#include <QMap>

namespace Ui {
    class syncmain;
}

class syncmain : public QDialog {
    Q_OBJECT
public:
    syncmain(QWidget *parent = 0);
    ~syncmain();
    xmlrpc::Client *client;
protected:
    void changeEvent(QEvent *e);
    //QSettings book;
    QSqlDatabase dbs;
    bool error;
    QString host;
private:
    Ui::syncmain *ui;
    QString bpath,bdescr,bname;
   /// QFile file;
    QNetworkAccessManager manager;
    QNetworkRequest request;
    int id;
    bool resault;
    int requestIdSum;
    int requestbooks;
    int ifexistsbooks;
   int xmlport;
   QString xmlrpcuri;
   QStringList imglist;
    QStringList booksrpc;
    QProgressDialog *progressDialog;
    QDomDocument xml;
    bool httperror;
    QMap<QString,QString> booklist;
    QMap<QString,int> lmap;

private slots:

    void on_syncsite_clicked();
    void on_begin_clicked();
    void on_downgo_clicked();
    void on_syncmain_destroyed();
    void catup(int bookid,QString command);
    void subcat(int cat,QString catsql,int bookid,QString command);
    void article(int cat,QString catsql,QString command);
    void on_books_itemDoubleClicked(QListWidgetItem* item);
    void on_uploadgo_clicked();
    void processReturnValue( int requestId, QVariant value );
    void processFault( int requestId, int errorCode, QString errorString );
    void addbook(QString command);//add new book to the site if not exist there
    void readydown(QNetworkReply* reply);
    void download(QUrl url);
    void updateDataReadProgress(qint64 received, qint64 total);
    void parse(QDomNode node,int dparent,int dsub);
    void lmapins();
    void new_book(QString name,QString descr);
    void initbooks();
    void bookimages(QString data,QString command);
};

#endif // syncmain_H
