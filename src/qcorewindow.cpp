#include "headers/qcorewindow.h"


QCoreWindow::QCoreWindow(QWidget *parent) :
    QMainWindow(parent)
{

}
void QCoreWindow::buildLangMenu(QDir *dir,QString appname,QString icon)
{
    lang_files_path = dir->absolutePath()+QDir::toNativeSeparators("/");
    app_lang_prefix = appname;
    languageMenu = new QMenu(tr("langmenu"),this);
    if(!icon.isEmpty())
        languageMenu->setIcon(QIcon(icon));

    QActionGroup *languageActionGroup = new QActionGroup(this);
    connect(languageActionGroup, SIGNAL(triggered(QAction *)),
            this, SLOT(switchLanguage(QAction *)));

    QStringList fileNames =
            dir->entryList(QStringList(appname+"*.qm"));
    QString syslocale = QLocale::system().name();
    QString lang;
    if(syslocale.length()>2)
    {
        syslocale.resize(2);
    }
    for (int i = 0; i < fileNames.size(); ++i) {
        QString locale = fileNames[i];
        locale.remove(0, locale.indexOf('_') + 1);
        locale.truncate(locale.lastIndexOf('.'));
        QTranslator translator1;
        translator1.load(lang_files_path+fileNames[i]);
        QString language = translator1.translate("Language","English");
        QAction *action = new QAction(tr("&%2").arg(language), this);
        action->setCheckable(true);
        action->setData(locale);
        languageMenu->addAction(action);
        languageActionGroup->addAction(action);
      /*  if(settings.value("locale","none")=="none")
        {
            if (locale== syslocale)
            {
                action->setChecked(true);
                lang=locale;
            }
        }
        else
        {
            if (locale==settings.value("locale","none"))
            {
                action->setChecked(true);
                lang=settings.value("locale","none").toString();
            }
        }*/

    }
    translator.load(lang_files_path+appname+lang);
    QApplication::installTranslator(&translator);
    languageMenu->setTitle(tr("langmenu"));
}

void QCoreWindow::switchLanguage(QAction *action)
{
    locale = action->data().toString();
    translator.load(app_lang_prefix + locale, lang_files_path);
    QApplication::installTranslator(&translator);
    languageMenu->setTitle(tr("langmenu"));
}
