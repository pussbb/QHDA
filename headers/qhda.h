#ifndef QHDA_H
#define QHDA_H

#include "headers/qcorewindow.h"
#include <QDockWidget>
namespace Ui {
    class QHDA;
}

class QHDA : public QCoreWindow
{
    Q_OBJECT

public:
    explicit QHDA(QWidget *parent = 0);
    QDockWidget *BookList;
    QDockWidget *BookTableContents;
    QDockWidget *SearchInBook;
    QWidget *BookListContent;
    QWidget *BookTCContent;
    QWidget *SearchContent;
    ~QHDA();
public slots:
    void changeEvent(QEvent *e);
private slots:
    void on_actionExit_triggered();
    void init_dockwidgets();
private:
    Ui::QHDA *ui;
};

#endif // QHDA_H
