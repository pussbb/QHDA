#ifndef TREEBOX_H
#define TREEBOX_H

#include <QComboBox>
#include <QTreeView>
#include <QEvent>
#include <QMouseEvent>
#include <QTreeWidget>
#include <QTreeWidgetItem>

class TreeBox:public QComboBox{
public:
    TreeBox(QWidget*parent=0):QComboBox(parent),skipNextHide(false)
    {
        setView(new QTreeView(this));
       /// QComboBox::resize(250,60);
        view()->viewport()->installEventFilter(this);
        view()->setProperty("headerHidden",true);
        view()->setMinimumSize(200,150);
        view()->setAlternatingRowColors(true);
        static_cast<QTreeView*>(view())->setAllColumnsShowFocus(true);
    }

    bool eventFilter(QObject*object,QEvent*event)
    {
        if(event->type()==QEvent::MouseButtonPress
                && object==view()->viewport())
            {
                QMouseEvent*mouseEvent=static_cast<QMouseEvent*>(event);
                QModelIndex index=view()->indexAt(mouseEvent->pos());
                setCurrentIndex(index.row());
                if(!view()->visualRect(index).contains(mouseEvent->pos()))
                    skipNextHide=true;
                hidePopup();
            }
        return false;
    }

    virtual void showPopup()
    {
        setRootModelIndex(view()->currentIndex().parent());
        setCurrentIndex(view()->currentIndex().row());
        setRootModelIndex(QModelIndex());
        QComboBox::showPopup();
        static_cast<QTreeView*>(view())->expandAll();
    }
    virtual QVariant getData(int userRole)
    {
        return view()->currentIndex().data(userRole);
    }

    virtual void hidePopup()
    {
        setRootModelIndex(view()->currentIndex().parent());
        setCurrentIndex(view()->currentIndex().row());
        setRootModelIndex(QModelIndex());
        if(skipNextHide)
            skipNextHide=false;
        else
        QComboBox::hidePopup();
    }
private: bool skipNextHide;
};
#endif // TREEBOX_H
