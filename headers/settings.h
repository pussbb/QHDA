#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QListWidget>
#include <QDebug>
namespace Ui {
    class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

private slots:
    void on_listWidget_itemClicked(QListWidgetItem* item);

    void on_enableProxy_stateChanged(int );

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
