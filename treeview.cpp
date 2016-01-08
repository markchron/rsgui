#include "treeview.h"
#include<QModelIndex>
#include <QMessageBox>
TreeView::TreeView(QWidget *parent):
    QTreeView(parent)
{
    model = new QStandardItemModel(2,1);
    model->setHeaderData(0, Qt::Horizontal, "Property");

    QStandardItem * rsritem1 = new QStandardItem("Grid");
    //item1->setIcon(QIcon(":/icons/images/icon_new.png"));
    QStandardItem * rsritem2 = new QStandardItem("Array Properties");

    model->setItem(0,0, rsritem1);
    model->setItem(1,0, rsritem2);

    QModelIndex myparent;
    for (int i=0; i<2; i++){
        myparent = model->index(0,0, myparent);
        model->insertRows(0,1, myparent);
        model->insertColumns(0,1, myparent);
        QModelIndex index = model->index(0, 0, myparent);
        model->setData(index, i);
    }

    this->setModel(model);

}
QList<QStandardItem*> TreeView::getItems(){
    return model->findItems("*", Qt::MatchWildcard | Qt::MatchRecursive);
}

void TreeView::mouseDoubleClickEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        QModelIndex index = currentIndex();
        QMessageBox::information(this, tr("Tree select"),
                                 index.data().toString(),
                                 QMessageBox::Ok);
    }
}
