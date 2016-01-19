#ifndef CMDBUTTONSTREE_H
#define CMDBUTTONSTREE_H

#include <QWidget>
#include <QPushButton>

class cmdButtonsTree : public QWidget
{
    Q_OBJECT
public:
    explicit cmdButtonsTree(QWidget *parent = 0);

    QPushButton * getButton(const int) const;
    QPushButton * getButton(const QString& str)const;
signals:

public slots:

private:
    void setCustmQuery();

    QPushButton * buttons[3];
    QVector<QString> custmQueryVector;
};

#endif // CMDBUTTONSTREE_H
