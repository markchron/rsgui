#ifndef CARTESIANGRIDDIALOG_H
#define CARTESIANGRIDDIALOG_H

#include <QDialog>
#include "ui_cartesiangriddialog.h"
/*
namespace Ui {
class CartesianGridDialog;
}
*/
class CartesianGridDialog : public QDialog, public Ui::CartesianGridDialog
{
    Q_OBJECT

public:
    explicit CartesianGridDialog(QWidget *parent = 0);
    ~CartesianGridDialog();
    QString getGridType()const;
    QString getKdir()const;

    int getNi()const;
    int getNj()const;
    int getNk()const;

    double getX0()const;
    double getY0() const;
    double getZ0() const;

    double getStepX()const;
    double getStepY()const;
    double getStepZ()const;
private slots:
//    void enableOkButton(const QString& text);
    void on_niLEdt_textChanged();
    void on_njLEdt_textChanged();
    void on_nkLEdt_textChanged();
private:

//    Ui::CartesianGridDialog *ui;
};

#endif // CARTESIANGRIDDIALOG_H
