#ifndef RESPRODIALOG_H
#define RESPRODIALOG_H

#include <QDialog>

namespace Ui {
class ResProDialog;
}

class ResProDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResProDialog(QWidget *parent = 0);
    ~ResProDialog();

private:
    Ui::ResProDialog *ui;
};

#endif // RESPRODIALOG_H
