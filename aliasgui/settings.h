#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include "QAbstractButton"
#include <QListWidgetItem>
namespace Ui {
    class Settings;
}

class Settings : public QDialog {
    Q_OBJECT
public:
    Settings(QWidget *parent = 0);
    ~Settings();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Settings *ui;

private slots:
    void on_themesbox_currentIndexChanged(int index);
    void on_proxytype_currentIndexChanged(int index);
    void on_listWidget_itemClicked(QListWidgetItem* item);
    void on_buttonBox_clicked(QAbstractButton* button);
    void init_data();
};

#endif // SETTINGS_H
