#ifndef HREF_H
#define HREF_H

#include <QDialog>

namespace Ui {
    class href;
}

class href : public QDialog {
    Q_OBJECT
public:
    href(QWidget *parent = 0);
    ~href();
QString gethref();
void set(QString text,QString url);
protected:
    void changeEvent(QEvent *e);

private:
    Ui::href *ui;

private slots:
    void on_buttonBox_accepted();
};

#endif // HREF_H
