#ifndef GENSETDIALOG_H
#define GENSETDIALOG_H

#include <QDialog>
#include "envset.h"

class QGroupBox;
class QRadioButton;
class QDateEdit;
class QLabel;
class QString;

class GenSetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GenSetDialog(QWidget *parent = 0);
    ~GenSetDialog();
    int getSimType() const;
    int getUnitType() const;
    int getPorosityType() const;
    int getStartDay() const;
private slots:
    void updatePreview();

private:
    void createTypeGroupBox();
    void createHintsGroupBox();

    void updatePreviewValue();
    void updatePreviewActive();

    QRadioButton *createRadioButton(const QString& text);

    QPushButton *okBt;
    QPushButton *quitBt;

    QGroupBox * simGBox;
    QRadioButton *simBlackOilRBt; // simulator black oil radio button
    QRadioButton *simCompositionRBt; // simulator compositional radio button
    QRadioButton *simThermalRBt;
    envsimtype_et et_sim_type;

    QGroupBox * unitGBox;
    QRadioButton *unitSIRBt;
    QRadioButton *unitFieldRBt;
    envunittype_et et_unit_type;

    QGroupBox * porosityGBox;
    QRadioButton *porositySinglePorosityRBt;
    QRadioButton *porosityDualPorosityRBt;
    QRadioButton *porosityDualPermRBt;
    QRadioButton *porosityDualPorDualPermRBt;
    envporositytype_et et_porosity_type;

    QLabel * dateLabel;
    QDateEdit * dateStartLedt;

};

#endif // GENSETDIALOG_H
