#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QTreeView>
#include <QList>
#include <QMouseEvent>
#include <QStandardItem>

class TreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit TreeView(QWidget * parent=0);
    QList<QStandardItem*> getItems();
    void mouseDoubleClickEvent(QMouseEvent *event);

public slots:

private:
    QStandardItemModel *model;

};

#endif // TREEVIEW_H
