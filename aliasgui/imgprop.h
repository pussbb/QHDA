#ifndef IMGPROP_H
#define IMGPROP_H

#include <QDialog>
#include <QTextImageFormat>
 #include <QPixmap>
namespace Ui {
    class imgprop;
}

class imgprop : public QDialog {
    Q_OBJECT
public:
    imgprop(QWidget *parent = 0);
    ~imgprop();
  QPixmap currimage;
 //QTextImageFormat img;
  void setimage(QTextImageFormat image);
 QString getimage();
protected:
    void changeEvent(QEvent *e);

private:
    Ui::imgprop *ui;

private slots:
    void on_wimg_valueChanged(int );
    void on_imgprop_accepted();
};

#endif // IMGPROP_H
