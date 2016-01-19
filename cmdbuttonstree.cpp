#include "cmdbuttonstree.h"
#include <QVBoxLayout>
cmdButtonsTree::cmdButtonsTree(QWidget *parent) : QWidget(parent)
{
    setCustmQuery();
    QVBoxLayout * layout = new QVBoxLayout;
    buttons.resize(custmQueryVector.size());

    for(int i=0; i< buttons.size(); ++i){
        buttons[i]= new QPushButton(custmQueryVector.at(i));
        layout->addWidget(buttons.at(i));
    }

    this->setLayout(layout);
}

void cmdButtonsTree::setCustmQuery(){
    custmQueryVector<<tr("I/O control")
                   <<tr("Reservoir" )
                  <<tr("PVT")
                 <<tr("Rock-Fluid")
                <<tr("Numerical")
               <<tr("Initialize");
}

QPushButton* cmdButtonsTree::getButton(const int i) {
    return buttons.at(i);
}
QPushButton* cmdButtonsTree::getButton(const QString& str){
    int i = custmQueryVector.indexOf(str);
    if( i != -1){
        return getButton(i);
    } else {
        return getButton(0);
    }
}
