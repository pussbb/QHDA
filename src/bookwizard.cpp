#include "headers/bookwizard.h"
#include "ui_bookwizard.h"

BookWizard::BookWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::BookWizard)
{

    ui->setupUi(this);
    QRegExp nameExpr("[a-zA-Z]+");
    QRegExp passExpr("[a-zA-Z0-9_\\-\\+=`~!@#$%^&\\*\\(\\)?\\[\\]:;,\\./]+");
    ui->host->setValidator(new QRegExpValidator(nameExpr ,this));
    ui->port->setValidator(new QRegExpValidator(nameExpr ,this));
    ui->username->setValidator(new QRegExpValidator(nameExpr ,this));
    ui->password->setValidator(new QRegExpValidator(passExpr ,this));
    ui->dbname->setValidator(new QRegExpValidator(nameExpr ,this));
}

BookWizard::~BookWizard()
{
    delete ui;
}

bool BookWizard::initDbPluginsList(QMap<QString, DbManagerInterface *> plugins)
{
    dbplugins = plugins;
    if(plugins.count() == 0)
    {
        return false;
    }
    foreach (QString plugin_name, plugins.keys()) {
        ui->dbengineslist->addItem(plugin_name);
    }
    DbManagerInterface *interface = dbplugins.value(ui->dbengineslist->currentText());
    if(interface->authConection())
    {
        ui->auth_options->setEnabled(true);
        QMap<QString,QString> auth = interface->defaultAuthOptions();
        ui->host->setText(auth.value("host",""));
        ui->port->setText(auth.value("port",""));
        ui->username->setText(auth.value("username",""));
        ui->password->setText(auth.value("password",""));
    }
    else
        ui->auth_options->setEnabled(false);
    ui->connoptions->setText(interface->defaultConnectionOptions());
    return true;
}

void BookWizard::on_chooseicon_clicked()
{
    iconfile = QFileDialog::getOpenFileName(this, tr("Open File"),
                                            "",
                                            tr("Images (*.png *.jpg)"));
    if (!iconfile.isEmpty())
    {
        ui->chooseicon->setIcon(QIcon(iconfile));
        ui->chooseicon->setIconSize(QSize(64,64));
    }
}

void BookWizard::on_folderchoose_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Choose Directory"),
                                                    "",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    if(!dir.isEmpty())
    {
        QFileInfo d(dir);
        if(d.isWritable())
            ui->folder_edit->setText(dir);
        else
        {
            QMessageBox::warning(0,  QObject::tr("Directory write protected"),
                                 QObject::tr("%1\nPlease choose another directory.")
                                 .arg(dir));
        }
    }
}

void BookWizard::accept()
{
    QString errorMsg = "";
    if(ui->bookname->text().isEmpty())
        errorMsg = tr("Field Book name is requied\n");
    if(ui->dbname->text().isEmpty())
        errorMsg +=  tr("Field Database name is requied\n");
    if(ui->folder_edit->text().isEmpty())
        errorMsg += tr("Field Folder is requied");
    if(!errorMsg.isEmpty())
    {
        QMessageBox::warning(0,  QObject::tr("Please fill all fields"),
                             errorMsg);
    }
    else
    {
        QDir dir(ui->folder_edit->text());
        dir.mkdir(ui->dbname->text());
        dir.cd(ui->dbname->text());
        QString path = dir.canonicalPath()+QDir::toNativeSeparators("/");
        /// create settings
        QSettings bookSettings(path+ui->dbname->text()+".ini",
                                QSettings::IniFormat);
        bookSettings.setValue("General/Bookname",ui->bookname->text());
        bookSettings.setValue("General/Bookpath",path);
        if(!iconfile.isEmpty())
        {
            //resize and copy image icon to book folder
            QFileInfo icon_info(iconfile);
            ///QFile::copy(iconfile,path+icon_info.fileName());
            QPixmap icon(iconfile);
            icon = icon.scaled(64,64,Qt::KeepAspectRatio,Qt::SmoothTransformation );
            icon.save(path+icon_info.fileName());
            bookSettings.setValue("General/BookIcon",icon_info.fileName());
        }
        else
            bookSettings.setValue("General/BookIcon","");
        bookSettings.setValue("General/BookDescr",ui->description->document()->toPlainText());
        bookSettings.setValue("Database/Engine",ui->dbengineslist->currentText());
        QMap<QString, QVariant> options;
        DbManagerInterface *interface = dbplugins.value(ui->dbengineslist->currentText());
        bookSettings.setValue("Database/auth_connection",interface->authConection());
        if(interface->authConection())
        {
            options.insert("host",ui->host->text());
            options.insert("port",ui->port->text());
            options.insert("username",ui->username->text());
            options.insert("password",ui->password->text());
        }
        options.insert("connoptions",ui->connoptions->document()->toPlainText());
        bookSettings.setValue("Database/settings",options);
        bookSettings.setValue("Database/connoptions",ui->connoptions->document()->isEmpty());
        bookSettings.setValue("Database/version",interface->version());
        bookSettings.setValue("Database/isservertype",interface->isServerType());
        bookSettings.sync();
        if(!interface->isServerType())
        {
            if(!interface->create(path+ui->dbname->text()))
            {
                QMessageBox::warning(0,  QObject::tr("Couldn't create database"),
                                     QObject::tr("Unfortunately we couldn't create database\n%1\n RollBacking changes\nError :%2")
                                     .arg(path+ui->dbname->text()).arg(interface->errorStr));
                dir.remove(dir.canonicalPath());
            }
        }
        else
        {
            if(!interface->create(ui->dbname->text()))
            {
                QMessageBox::warning(0,  QObject::tr("Couldn't create database"),
                                     QObject::tr("Unfortunately we couldn't create database\n%1\n RollBacking changes\nError :%2")
                                     .arg(ui->dbname->text()).arg(interface->errorStr));
                dir.remove(dir.canonicalPath());
            }
        }
        QSettings settings;
        settings.setValue("Books/"+ui->dbname->text(),path);
        QDialog::accept();

    }

}


