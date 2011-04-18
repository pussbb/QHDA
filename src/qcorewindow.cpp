#include "headers/qcorewindow.h"


QCoreWindow::QCoreWindow(QWidget *parent) :
    QMainWindow(parent)
{
    set_locale();
}
void QCoreWindow::buildLangMenu(QString appname,QDir *dir,QString icon)
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

    for (int i = 0; i < fileNames.size(); ++i)
    {
        QString file_locale = fileNames[i];
        file_locale.remove(0, file_locale.indexOf('_') + 1);
        file_locale.truncate(file_locale.lastIndexOf('.'));

        QTranslator translator1;
        translator1.load(lang_files_path+fileNames[i]);
        QString language = translator1.translate("Language","English");
        QAction *action = new QAction(tr("&%2").arg(language), this);
        action->setCheckable(true);
        action->setData(file_locale);
        languageMenu->addAction(action);
        languageActionGroup->addAction(action);
        if(file_locale == locale)
            action->setChecked(true);
    }
    translator.load(lang_files_path+appname+locale);
    QApplication::installTranslator(&translator);
    languageMenu->setTitle(tr("langmenu"));
}

void QCoreWindow::switchLanguage(QAction *action)
{
    locale = action->data().toString();
    translator.load(app_lang_prefix + "_" +locale, lang_files_path);
    QApplication::installTranslator(&translator);
    languageMenu->setTitle(tr("langmenu"));
}

void QCoreWindow::LangMenuToMenuBar(QString objectName)
{
    QMenuBar* bar=this->menuBar();
    QList<QAction *> actions = bar->actions();
    QList<QAction *>::const_iterator it = actions.begin();
    for(; it != actions.end(); it++)
    {
        QAction *action = *it;
        if(action->menu()->objectName() == objectName)
        {

            action->menu()->addMenu(languageMenu);
        }
    }
}

void QCoreWindow::set_locale()
{
    syslocale = QLocale::system().name();
    if(syslocale.length()>2)
    {
        syslocale.resize(2);
    }
    settings.beginGroup("Core");
    if(settings.value("locale","none")=="none")
        locale = syslocale;
    else
        locale = settings.value("locale","none").toString();
    settings.endGroup();
}


