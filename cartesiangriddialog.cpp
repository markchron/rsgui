#include "cartesiangriddialog.h"
#include "ui_cartesiangriddialog.h"
#include "envset.h"
#include <QPushButton>

CartesianGridDialog::CartesianGridDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CartesianGridDialog)
{
    this->setWindowTitle(tr("Create Structure Grid"));
    ui->setupUi(this);

    int nwidth = width();
    int nheight = height();
    if(parent != NULL){
        setGeometry(parent->x() + parent->width()/2 - nwidth/2,
                    parent->y() + parent->width()/2 - nheight/2,
                    nwidth, nheight);
    } else {
        resize(nwidth, nheight);
    }
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    connect(ui->niLEdt, SIGNAL(textChanged(const QString&)),
            this, SLOT(enableOkButton(const QString&)) );
}

CartesianGridDialog::~CartesianGridDialog()
{
    delete ui;
}
QString CartesianGridDialog::getGridType()const{
    if( ui->gridTypeCylindRBt_2->isChecked())
        return ui->gridTypeCylindRBt_2->text();
    else
        return ui->gridTypeCartesianRBt->text();
}
QString CartesianGridDialog::getKdir()const{
    if(ui->kUpDirRBt->isChecked()){
        return ui->kUpDirRBt->text();
    } else
        return ui->kDownDirRBt->text();
}
int CartesianGridDialog::getNi()const {
    return ui->niLEdt->text().toInt();
}
int CartesianGridDialog::getNj()const{
    return ui->njLEdt->text().toInt();
}
int CartesianGridDialog::getNk()const{
    return ui->nkLEdt->text().toInt();
}
double CartesianGridDialog::getX0()const{
    return ui->xOriginLEt->text().toDouble();
}
double CartesianGridDialog::getY0()const{
    return ui->yOriginLEt->text().toDouble();
}
double CartesianGridDialog::getZ0()const{
    return ui->zOriginLEt->text().toDouble();
}
double CartesianGridDialog::getStepX()const{
    return ui->xStepLEt->text().toDouble();
}
double CartesianGridDialog::getStepY()const{
    return ui->yStepLEt->text().toDouble();
}
double CartesianGridDialog::getStepZ()const{
    return ui->zStepLEt->text().toDouble();
}

void CartesianGridDialog::enableOkButton(const QString &text){
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(!text.isEmpty());
}
