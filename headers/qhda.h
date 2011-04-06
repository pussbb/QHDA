#ifndef QHDA_H
#define QHDA_H

#include <QMainWindow>

namespace Ui {
    class QHDA;
}

class QHDA : public QMainWindow
{
    Q_OBJECT

public:
    explicit QHDA(QWidget *parent = 0);
    ~QHDA();

private:
    Ui::QHDA *ui;
};

#endif // QHDA_H
