#include "cartesiangriddialog.h"
#include "ui_cartesiangriddialog.h"

CartesianGridDialog::CartesianGridDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CartesianGridDialog)
{
    this->setWindowTitle(tr("Create Structure Grid"));
    ui->setupUi(this);

    QGridLayout * layout = new QGridLayout(this);
    layout->addWidget(ui->gridTypeGBox,0,0,1,1);
    layout->addWidget(ui->kdirGBox,0,1,1,1);
    layout->addWidget(ui->gridNumGBox,1,0,1,-1);
    layout->addWidget(ui->gridOriginGBox,2,0,1,-1);

    this->setLayout(layout);

    int nwidth = 380;
    int nheight = 450;
    if(parent != NULL){
        setGeometry(parent->x() + parent->width()/2 - nwidth/2,
                    parent->y() + parent->width()/2 - nheight/2,
                    nwidth, nheight);
    } else {
        resize(nwidth, nheight);
    }
}

CartesianGridDialog::~CartesianGridDialog()
{
    delete ui;
}

int CartesianGridDialog::getNi()const{
    return ui->niLEdt->text().toInt();
}
