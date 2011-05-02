#ifndef BOOKWIZARD_H
#define BOOKWIZARD_H

#include <QWizard>
#include "extras/dbmanagerinterface.h"

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
    bool init_db_plugins_list(QMap<QString , DbManagerInterface*> plugins);
private:
    Ui::BookWizard *ui;
    QMap<QString , DbManagerInterface*> dbplugins;
};

#endif // BOOKWIZARD_H
