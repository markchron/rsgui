#ifndef CMDBUTTONSTREE_H
#define CMDBUTTONSTREE_H

#include <QWidget>
#include <QPushButton>
#include <QToolButton>
class cmdButtonsTree : public QWidget
{
    Q_OBJECT
public:
    explicit cmdButtonsTree(QWidget *parent = 0);

    QToolButton * getButton(const int i);
    QToolButton * getButton(const QString& str);
signals:

public slots:

private:
    void setCustmQuery();

    QVector<QPushButton*> buttons;
    QVector<QToolButton*> toolButtons;
    QVector<QString> custmQueryVector;
};

#endif // CMDBUTTONSTREE_H
