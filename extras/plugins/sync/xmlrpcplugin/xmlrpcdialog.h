#ifndef EDITOR_H
#define EDITOR_H

#include <QDialog>
#include <QListWidgetItem>
#include <QDebug>
namespace Ui {
    class XmlRpcDialog;
}

class XmlRpcDialog: public QDialog
{
    Q_OBJECT

public:
    explicit XmlRpcDialog(QWidget *parent = 0);
    ~XmlRpcDialog();
    void setProgressValues(int min,int max);
    void setOperationTitle(QString title,bool addToLog);
private slots:
    void on_logButton_clicked();

private:
    Ui::XmlRpcDialog *ui;

};

#endif // EDITOR_H
