#ifndef SYNTAXHILIGHT_H
#define SYNTAXHILIGHT_H

#include <QtGui/QDialog>

namespace Ui {
    class syntaxhilight;
}

class syntaxhilight : public QDialog {
    Q_OBJECT
public:
    syntaxhilight(QWidget *parent = 0);
    ~syntaxhilight();
    QString gethtml();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::syntaxhilight *ui;
    void initlang();

private slots:
    void on_codelist_activated(int index);
};

#endif // SYNTAXHILIGHT_H
