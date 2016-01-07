#include "gensetdialog.h"
#include <QRadioButton>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QMessageBox>
#include <QDateEdit>
#include <QLabel>
GenSetDialog::GenSetDialog(QWidget *parent) :
    QDialog(parent)
{
    et_unit_type    =ENV_UNIT_UNDEFINED;
    et_porosity_type=ENV_POROSITY_UNDEFINED;
    createTypeGroupBox();

    this->setWindowTitle(tr("Reservoir Simulator Settings"));

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(simGBox);
    topLayout->addWidget(unitGBox);
    topLayout->addWidget(porosityGBox);

    okBt = new QPushButton(tr("&OK"));
    okBt->setDisabled(true);
    quitBt = new QPushButton(tr("&Cancel"));
    connect(quitBt, SIGNAL(clicked(bool)), this, SLOT(reject()));
    connect(okBt, SIGNAL(clicked(bool)), this, SLOT(accept()));

    dateStartLedt = new QDateEdit(QDate::currentDate(), this);
    dateLabel = new QLabel(this);
    dateLabel->setText(tr("Simulation Start Date:"));
    QHBoxLayout *clay1Layout = new QHBoxLayout;
    clay1Layout->addWidget(dateLabel);
    clay1Layout->addWidget(dateStartLedt);
    clay1Layout->addStretch();


    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addStretch();
    bottomLayout->addWidget(okBt);
    bottomLayout->addWidget(quitBt);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(clay1Layout);
    mainLayout->addStretch();
    mainLayout->addLayout(bottomLayout);
    setLayout(mainLayout);

    int nwidth = 400;
    int nheight = 300;
    if(parent != NULL)
        setGeometry(parent->x() + parent->width()/2 - nwidth/2,
                    parent->y() + parent->height()/2 - nheight/2,
                    nwidth, nheight);
    else
        resize(nwidth, nheight);

}

GenSetDialog::~GenSetDialog()
{

}
int GenSetDialog::getSimType() const{
    return et_sim_type;
}
int GenSetDialog::getUnitType()const{
    return et_unit_type;
}
int GenSetDialog::getPorosityType() const{
    return et_porosity_type;
}
int GenSetDialog::getStartDay()const{
    return dateStartLedt->date().day();
}
void GenSetDialog::createTypeGroupBox(){
    simGBox = new QGroupBox(tr("Simulator"));
    simBlackOilRBt = createRadioButton(tr("Black Oil"));
    simCompositionRBt = createRadioButton(tr("Composition"));
    simThermalRBt =createRadioButton("Thermal");
    simBlackOilRBt->setChecked(true); // default
    QVBoxLayout * layout = new QVBoxLayout;
    layout->addWidget(simBlackOilRBt,0);
    layout->addWidget(simCompositionRBt,1);
    layout->addWidget(simThermalRBt,2);
    simGBox->setLayout(layout);

    unitGBox = new QGroupBox(tr("Working Unit"));
    unitSIRBt = createRadioButton(tr("SI"));
    unitFieldRBt = createRadioButton(tr("Field"));
    QVBoxLayout * layout2 = new QVBoxLayout;
    layout2->addWidget(unitSIRBt,0);
    layout2->addWidget(unitFieldRBt,1);
    unitGBox->setLayout(layout2);

    porosityGBox = new QGroupBox(tr("Porosity"));
    porositySinglePorosityRBt = createRadioButton(tr("Single"));
    porosityDualPorosityRBt = createRadioButton(tr("Dual"));
    porosityDualPermRBt = createRadioButton(tr("Dual Perm"));
    porosityDualPorDualPermRBt = createRadioButton(tr("DPDP"));
    QVBoxLayout * layout3 = new QVBoxLayout;
    layout3->addWidget(porositySinglePorosityRBt,0);
    layout3->addWidget(porosityDualPorosityRBt,1);
    layout3->addWidget(porosityDualPermRBt,2);
    layout3->addWidget(porosityDualPorDualPermRBt,3);
    porosityGBox->setLayout(layout3);
}
void GenSetDialog::updatePreview(){
    updatePreviewValue();
    updatePreviewActive();
}
void GenSetDialog::updatePreviewValue(){
    /* updatePreview() slot is called whenever the user changes any of the window flags.
     *
     * First, create an empty flags
     * the, determine which one of the types that is checked and add it to flags
     */
   if(simBlackOilRBt->isChecked()){
       et_sim_type = ENV_SIM_BLACK_OIL;
   }else if(simCompositionRBt->isChecked()){
       et_sim_type = ENV_SIM_COMPOSITION;
   }else if(simThermalRBt->isChecked()){
       et_sim_type = ENV_SIM_THERMAL;
   }

   if(unitSIRBt->isChecked()){
       et_unit_type = ENV_UNIT_SI;
   }else if(unitFieldRBt->isChecked()){
       et_unit_type = ENV_UNIT_FIELD;
   }

   if(porositySinglePorosityRBt->isChecked()){
       et_porosity_type = ENV_POROSITY_SINGLE;
   }else if(porosityDualPorosityRBt->isChecked()){
       et_porosity_type = ENV_POROSITY_DUAL_POROSITY;
   }else if(porosityDualPermRBt->isChecked()){
       et_porosity_type = ENV_POROSITY_DUAL_PERM;
   }else if(porosityDualPorDualPermRBt->isChecked()){
       et_porosity_type = ENV_POROSITY_DUAL_POR_DUAL_PERM;
   }
}

void GenSetDialog::updatePreviewActive(){
    if(simBlackOilRBt->isChecked()){
        porosityDualPorosityRBt->setEnabled(true);
        porosityDualPermRBt->setEnabled(true);
        porosityDualPorDualPermRBt->setEnabled(true);
    }else if(simCompositionRBt->isChecked()){
        porosityDualPorosityRBt->setDisabled(true);
        porosityDualPermRBt->setDisabled(true);
        porosityDualPorDualPermRBt->setDisabled(true);
    }else if(simThermalRBt->isChecked()){
        porosityDualPorosityRBt->setDisabled(true);
        porosityDualPermRBt->setDisabled(true);
        porosityDualPorDualPermRBt->setDisabled(true);
    }

    if(et_unit_type != ENV_UNIT_UNDEFINED &&
            et_porosity_type != ENV_POROSITY_UNDEFINED){
        okBt->setDisabled(false);
    }
}

QRadioButton* GenSetDialog::createRadioButton(const QString &text){
    QRadioButton * button = new QRadioButton(text);
    connect(button, SIGNAL(clicked()), this, SLOT(updatePreview()));
    return button;
}
