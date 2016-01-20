#include "cartesiangriddialog.h"
#include "ui_cartesiangriddialog.h"
#include "envset.h"
#include <QPushButton>
#include <QRegExp>

CartesianGridDialog::CartesianGridDialog(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    setWindowTitle(tr("Create Structure Grid"));
    buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    // making the dialog non-resizable by the user.
    /* The layout then takes over the responsibiliyt for resizing,
     * and resizes the dailog automatically when child widgets are shown or hidden,
     * ensuring that the dialog is always displayed at its optimal size
     */
    layout()->setSizeConstraint(QLayout::SetFixedSize);

    int nwidth = width();
    int nheight = height();
    if(parent != NULL){
        setGeometry(parent->x() + parent->width()/2 - nwidth/2,
                    parent->y() + parent->width()/2 - nheight/2,
                    nwidth, nheight);
    } else {
        resize(nwidth, nheight);
    }

    /* //example
    connect(ui->niLEdt, SIGNAL(textChanged(const QString&)),
            this, SLOT(enableOkButton(const QString&)) );
    */
    QValidator *regNumValidor = new QIntValidator(1, 99999999, this);
    niLEdt->setValidator(regNumValidor);
    njLEdt->setValidator(regNumValidor);
    nkLEdt->setValidator(regNumValidor);


/*
     * "." any character
     * "\\d" A digit [0-9]
     * "\\D" A non-digit [^0-9]
     * "\\s" A whitespace [ \t\n\r\f]
     * "\\S" A non-whitespace
     * "\\w" A word character[_a-zA-Z0-9]
     * "\\W" A non-word character
*/

}

CartesianGridDialog::~CartesianGridDialog()
{
//    delete ui;
}
QString CartesianGridDialog::getGridType()const{
    if( gridTypeCylindRBt_2->isChecked())
        return gridTypeCylindRBt_2->text();
    else
        return gridTypeCartesianRBt->text();
}
QString CartesianGridDialog::getKdir()const{
    if(kUpDirRBt->isChecked()){
        return kUpDirRBt->text();
    } else
        return kDownDirRBt->text();
}
int CartesianGridDialog::getNi()const {
    return niLEdt->text().toInt();
}
int CartesianGridDialog::getNj()const{
    return njLEdt->text().toInt();
}
int CartesianGridDialog::getNk()const{
    return nkLEdt->text().toInt();
}
double CartesianGridDialog::getX0()const{
    return xOriginLEt->text().toDouble();
}
double CartesianGridDialog::getY0()const{
    return yOriginLEt->text().toDouble();
}
double CartesianGridDialog::getZ0()const{
    return zOriginLEt->text().toDouble();
}
double CartesianGridDialog::getStepX()const{
    return xStepLEt->text().toDouble();
}
double CartesianGridDialog::getStepY()const{
    return yStepLEt->text().toDouble();
}
double CartesianGridDialog::getStepZ()const{
    return zStepLEt->text().toDouble();
}
/*
void CartesianGridDialog::enableOkButton(const QString &text){
     buttonBox->button(QDialogButtonBox::Ok)->setEnabled(!text.isEmpty());
}
*/
void CartesianGridDialog::on_niLEdt_textChanged(){
    buttonBox->button(QDialogButtonBox::Ok)
            ->setEnabled(niLEdt->hasAcceptableInput());
}
void CartesianGridDialog::on_njLEdt_textChanged(){
    buttonBox->button(QDialogButtonBox::Ok)
            ->setEnabled(niLEdt->hasAcceptableInput());
}
void CartesianGridDialog::on_nkLEdt_textChanged(){
    buttonBox->button(QDialogButtonBox::Ok)
            ->setEnabled(niLEdt->hasAcceptableInput());
}
