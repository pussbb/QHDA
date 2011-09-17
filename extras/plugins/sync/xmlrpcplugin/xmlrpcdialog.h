#ifndef EDITOR_H
#define EDITOR_H

#include <QDialog>

namespace Ui {
    class XmlRpcDialog;
}

class XmlRpcDialog: public QDialog
{
    Q_OBJECT

public:
    explicit XmlRpcDialog(QWidget *parent = 0);
    ~XmlRpcDialog();

private:
    Ui::XmlRpcDialog *ui;

};

#endif // EDITOR_H
