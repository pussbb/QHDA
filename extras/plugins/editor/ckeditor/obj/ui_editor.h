/********************************************************************************
** Form generated from reading UI file 'editor.ui'
**
** Created: Sun Jun 19 22:02:39 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITOR_H
#define UI_EDITOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>
#include <QtWebKit/QWebView>

QT_BEGIN_NAMESPACE

class Ui_Editor
{
public:
    QGridLayout *gridLayout;
    QWebView *webView;

    void setupUi(QWidget *Editor)
    {
        if (Editor->objectName().isEmpty())
            Editor->setObjectName(QString::fromUtf8("Editor"));
        Editor->resize(400, 300);
        gridLayout = new QGridLayout(Editor);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        webView = new QWebView(Editor);
        webView->setObjectName(QString::fromUtf8("webView"));
        webView->setUrl(QUrl("qrc:/ckeditor/editor.html"));

        gridLayout->addWidget(webView, 0, 0, 1, 1);


        retranslateUi(Editor);

        QMetaObject::connectSlotsByName(Editor);
    } // setupUi

    void retranslateUi(QWidget *Editor)
    {
        Editor->setWindowTitle(QApplication::translate("Editor", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Editor: public Ui_Editor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITOR_H
