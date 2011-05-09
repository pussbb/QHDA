#ifndef BOOKWIZARD_H
#define BOOKWIZARD_H

#include <QWizard>
#include "extras/dbmanagerinterface.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>

namespace Ui {
    class BookWizard;
}

class BookWizard : public QWizard
{
    Q_OBJECT

public:
    explicit BookWizard(QWidget *parent = 0);
    ///DbManagerInterface *interface;
    ~BookWizard();
    bool initDbPluginsList(QMap<QString , DbManagerInterface*> plugins);
    QString iconfile;
private slots:
    void on_chooseicon_clicked();

    void on_folderchoose_clicked();

    void accept();

private:
    Ui::BookWizard *ui;

    QMap<QString , DbManagerInterface*> dbplugins;
};

#endif // BOOKWIZARD_H
