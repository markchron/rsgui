#include "cmdbuttonstree.h"
#include <QVBoxLayout>
cmdButtonsTree::cmdButtonsTree(QWidget *parent) : QWidget(parent)
{
    setCustmQuery();
    buttons[0] = new QPushButton(custmQueryVector.at(0));
    buttons[1] = new QPushButton(custmQueryVector.at(1));
    buttons[2] = new QPushButton(custmQueryVector.at(2));

    QVBoxLayout * layout = new QVBoxLayout;
    for(int i=0; i<3; ++i )   layout->addWidget(buttons[i]);

    this->setLayout(layout);
}

void cmdButtonsTree::setCustmQuery(){
    custmQueryVector<<tr("I/O control") <<"Reservoir" <<"PVT" <<"Rock-Fluid"<<"Numerical" <<"Initialize";
}

QPushButton* cmdButtonsTree::getButton(const int i) const{
    return buttons[i];
}
QPushButton* cmdButtonsTree::getButton(const QString& str) const{
    int i = custmQueryVector.indexOf(str);
    if( i != -1){
        return getButton(i);
    } else {
        return getButton(0);
    }
}
