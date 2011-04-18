#ifndef QHDA_H
#define QHDA_H

#include "headers/qcorewindow.h"

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

private:
    Ui::QHDA *ui;
};

#endif // QHDA_H
