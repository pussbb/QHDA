#include "headers/tabelofcontent.h"
#include <QDebug>
TabelOfContent::TabelOfContent(QWidget *parent) :
    QTreeWidget(parent)
{
    //topLevelItem(0)->setText(0,"");
    connect(this,SIGNAL(customContextMenuRequested(QPoint)),
            this,SLOT(customContextMenuRequested(QPoint)));
}

void TabelOfContent::customContextMenuRequested(const QPoint &pos)
{
qDebug()<<"dfsdf";
}


