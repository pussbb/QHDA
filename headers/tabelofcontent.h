#ifndef TABELOFCONENT_H
#define TABELOFCONENT_H

#include <QTreeWidget>

class TabelOfContent : public QTreeWidget
{
    Q_OBJECT
public:
    explicit TabelOfContent(QWidget *parent = 0);
    bool onItem;
signals:

public slots:
    void customContextMenuRequested(const QPoint &pos);
};

#endif // TABELOFCONENT_H
