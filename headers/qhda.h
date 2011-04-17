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

private:
    Ui::QHDA *ui;
};

#endif // QHDA_H
