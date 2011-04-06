#ifndef ADIFFERENCE_H
#define ADIFFERENCE_H

#include <QtGui/QDialog>

namespace Ui {
    class adifference;
}

class adifference : public QDialog {
    Q_OBJECT
public:
    adifference(QWidget *parent = 0);
    ~adifference();
  void  setsitetext(QString text);
  void  setdbtext(QString text);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::adifference *ui;
};

#endif // ADIFFERENCE_H
