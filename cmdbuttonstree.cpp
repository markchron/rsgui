#include "cmdbuttonstree.h"
#include <QGridLayout>
cmdButtonsTree::cmdButtonsTree(QWidget *parent) : QWidget(parent)
{
    setCustmQuery();
    QGridLayout * layout = new QGridLayout;
    int size = custmQueryVector.size();
    buttons.resize(size);
    toolButtons.resize(size);
    for(int i=0; i< buttons.size(); ++i){
        buttons[i]= new QPushButton(custmQueryVector.at(i), this);
        //buttons.at(i)->setFlat(true);
        toolButtons[i] = new QToolButton(this);
        toolButtons.at(i)->setPopupMode(QToolButton::InstantPopup);
        toolButtons.at(i)->setArrowType(Qt::RightArrow);
        toolButtons.at(i)->setToolButtonStyle(Qt::ToolButtonIconOnly);
        layout->addWidget(buttons.at(i), i, 1);
        layout->addWidget(toolButtons.at(i), i, 2);
    }
    layout->setHorizontalSpacing(0);
    layout->setVerticalSpacing(1);

    this->setLayout(layout);
    this->setFixedHeight(sizeHint().height());
}

void cmdButtonsTree::setCustmQuery(){
    custmQueryVector<<tr("I/O control")
                   <<tr("Reservoir" )
                  <<tr("PVT")
                 <<tr("Rock-Fluid")
                <<tr("Numerical")
               <<tr("Initialize");
}

QToolButton* cmdButtonsTree::getButton(const int i) {
    return toolButtons.at(i);
}
QToolButton* cmdButtonsTree::getButton(const QString& str){
    int i = custmQueryVector.indexOf(str);
    if( i != -1){
        return getButton(i);
    } else {
        return getButton(0);
    }
}
