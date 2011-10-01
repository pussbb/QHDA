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
    enum IconType {Info,Warning,Error};
    void setProgressValues(int min,int max);
    void setOperationTitle(QString title,bool addToLog);
    void progressPlus(int value);
    int leftCount();
    void clear();
    Q_DECLARE_FLAGS(IconTypes, IconType)
    void toLog(QString text,IconTypes iconType);
private slots:
    void on_logButton_clicked();

private:
    Ui::XmlRpcDialog *ui;

};
Q_DECLARE_OPERATORS_FOR_FLAGS(XmlRpcDialog::IconTypes)
#endif // EDITOR_H
