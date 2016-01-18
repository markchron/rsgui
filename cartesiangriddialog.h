#ifndef CARTESIANGRIDDIALOG_H
#define CARTESIANGRIDDIALOG_H

#include <QDialog>

namespace Ui {
class CartesianGridDialog;
}

class CartesianGridDialog : public QDialog
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
private:

    Ui::CartesianGridDialog *ui;
};

#endif // CARTESIANGRIDDIALOG_H
