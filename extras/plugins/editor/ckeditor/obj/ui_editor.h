/********************************************************************************
** Form generated from reading UI file 'editor.ui'
**
** Created: Sun Jul 3 01:44:00 2011
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
#include <QtGui/QComboBox>
#include <QtGui/QFormLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QWidget>
#include <QtWebKit/QWebView>

QT_BEGIN_NAMESPACE

class Ui_Editor
{
public:
    QWebView *webView;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *title;
    QComboBox *categories;

    void setupUi(QWidget *Editor)
    {
        if (Editor->objectName().isEmpty())
            Editor->setObjectName(QString::fromUtf8("Editor"));
        Editor->resize(552, 418);
        webView = new QWebView(Editor);
        webView->setObjectName(QString::fromUtf8("webView"));
        webView->setGeometry(QRect(18, 168, 382, 225));
        webView->setUrl(QUrl("qrc:/ckeditor/editor.html"));
        formLayoutWidget = new QWidget(Editor);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(22, 100, 169, 51));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(formLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        title = new QLineEdit(formLayoutWidget);
        title->setObjectName(QString::fromUtf8("title"));

        formLayout->setWidget(1, QFormLayout::FieldRole, title);

        categories = new QComboBox(formLayoutWidget);
        categories->setObjectName(QString::fromUtf8("categories"));

        formLayout->setWidget(0, QFormLayout::FieldRole, categories);


        retranslateUi(Editor);

        QMetaObject::connectSlotsByName(Editor);
    } // setupUi

    void retranslateUi(QWidget *Editor)
    {
        Editor->setWindowTitle(QApplication::translate("Editor", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Editor", "Category", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Editor", "Title", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Editor: public Ui_Editor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITOR_H
