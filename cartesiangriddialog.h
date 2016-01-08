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
    int getNi()const;
private:

    Ui::CartesianGridDialog *ui;
};

#endif // CARTESIANGRIDDIALOG_H
