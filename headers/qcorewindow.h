#ifndef QCOREWINDOW_H
#define QCOREWINDOW_H

//-------------------
#include <QDebug>
//-------------------

#include <QMainWindow>
#include <QDir>
#include <QApplication>
#include <QMenu>
#include <QLocale>
#include <QTranslator>
#define AppDir QDir::toNativeSeparators ( QApplication::applicationDirPath()+QDir::toNativeSeparators("/"))
#define LangDir QDir::toNativeSeparators ( QApplication::applicationDirPath()+QDir::toNativeSeparators("/lang/"))

class QCoreWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit QCoreWindow(QWidget *parent = 0);
    QString inline app_dir() { return AppDir;};
    void buildLangMenu(QDir *dir = new QDir(LangDir),QString appname = "*",QString icon = "");
    QMenu *languageMenu;
    QString locale;
   /// void inline setAppLangPrefix(QString str){app_lang_prefix = str;};


signals:

private:
    QString app_lang_prefix;
    QString lang_files_path;
    QTranslator translator;
    QCoreWindow *d;
public slots:
    void switchLanguage(QAction *action);

};

#endif // QCOREWINDOW_H
