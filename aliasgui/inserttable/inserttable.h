#ifndef INSERTTABLE_H
#define INSERTTABLE_H

#include <QDialog>

namespace Ui {
    class insertTable;
}

class insertTable : public QDialog {
    Q_OBJECT
public:
    insertTable(QWidget *parent = 0);
    ~insertTable();
    int row,cell;
protected:
    void changeEvent(QEvent *e);

private:
    Ui::insertTable *ui;

private slots:
    void on_buttonBox_accepted();
};

#endif // INSERTTABLE_H
