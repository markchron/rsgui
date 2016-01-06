#include "resprodialog.h"
#include "ui_resprodialog.h"

ResProDialog::ResProDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResProDialog)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("Reservoir property"));

    int nwidth = 400;
    int nheight = 300;
    if(parent != NULL)
        setGeometry(parent->x() + parent->width()/2 - nwidth/2,
                    parent->y() + parent->height()/2 - nheight/2,
                    nwidth, nheight);
    else
        resize(nwidth, nheight);
}

ResProDialog::~ResProDialog()
{
    delete ui;
}
