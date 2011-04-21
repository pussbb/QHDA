#ifndef QHDA_H
#define QHDA_H

#include "headers/qcorewindow.h"
#include <QtWebKit>
namespace Ui {
    class QHDA;
}

class QHDA : public QCoreWindow
{
    Q_OBJECT

public:
    explicit QHDA(QWidget *parent = 0);
    ~QHDA();
public slots:
    void changeEvent(QEvent *e);
private slots:
    void on_actionExit_triggered();
    void init_dockwidgets();
    void on_actionFull_Screen_triggered();
    void on_actionBook_List_triggered();
    void on_actionBook_Table_of_Content_triggered();
    void on_actionSearch_In_Book_triggered();

private:
    Ui::QHDA *ui;
};

#endif // QHDA_H
