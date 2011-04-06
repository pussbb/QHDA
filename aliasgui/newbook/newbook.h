#ifndef NEWBOOK_H
#define NEWBOOK_H
 #include <QtSql>
#include <QtGui/QDialog>
 #include <QFileDialog>
#include <QSettings>
#include <QMessageBox>
namespace Ui {
    class newbook;
}

class newbook : public QDialog {
    Q_OBJECT
public:
    newbook(QWidget *parent = 0);
    ~newbook();
void setbook(QString name,QString descr);
protected:
    void changeEvent(QEvent *e);

private:
    Ui::newbook *m_ui;
QString filename;

private slots:
    void on_buttonBox_accepted();
    void on_iconchoose_clicked();
    void on_pushButton_clicked();
    void on_buttonBox_rejected();

};

#endif // NEWBOOK_H
