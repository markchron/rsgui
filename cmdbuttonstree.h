#ifndef CMDBUTTONSTREE_H
#define CMDBUTTONSTREE_H

#include <QWidget>
#include <QPushButton>

class cmdButtonsTree : public QWidget
{
    Q_OBJECT
public:
    explicit cmdButtonsTree(QWidget *parent = 0);

    QPushButton * getButton(const int i);
    QPushButton * getButton(const QString& str);
signals:

public slots:

private:
    void setCustmQuery();

    QVector<QPushButton*> buttons;
    QVector<QString> custmQueryVector;
};

#endif // CMDBUTTONSTREE_H
