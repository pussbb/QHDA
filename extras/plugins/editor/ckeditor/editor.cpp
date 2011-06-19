#include "editor.h"
#include "ui_editor.h"
#include "QWebInspector"

Editor::Editor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Editor)
{

    ui->setupUi(this);
    QWebInspector *inspector = new QWebInspector;
    ui->webView->page()->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
     ui->webView->page()->settings()->setAttribute(QWebSettings::AutoLoadImages, true);
     ui->webView->page()->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);

 ui->webView->page()->settings()->setAttribute(QWebSettings::JavascriptCanAccessClipboard, true);
  ui->webView->page()->settings()->setAttribute(QWebSettings::JavascriptCanOpenWindows, true);

        inspector->setPage(ui->webView->page());

}

Editor::~Editor()
{
    delete ui;
}
