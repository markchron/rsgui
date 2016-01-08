#include "cartesiangriddialog.h"
#include "ui_cartesiangriddialog.h"

CartesianGridDialog::CartesianGridDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CartesianGridDialog)
{
    this->setWindowTitle(tr("Create Structure Grid"));

    designDialog();

    ui->setupUi(this);
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

void CartesianGridDialog::designDialog(){
    QHBoxLayout * topHLay = new QHBoxLayout;
    topHLay->addWidget(ui->gridTypeGBox);
    topHLay->addStretch();
    topHLay->addWidget(ui->kdirGBox);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topHLay);
    mainLayout->addLayout(ui->gridNumHLay);
    mainLayout->addLayout(ui->gridOriginHLay);
    mainLayout->addLayout(ui->gridStepHLay);

    mainLayout->addWidget(ui->buttonBox);
    setLayout(mainLayout);
}
int CartesianGridDialog::getNi()const{
    return ui->niLEdt->text().toInt();
}
