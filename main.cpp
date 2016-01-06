#include "prgui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PRGUI w;
    w.show();

    return a.exec();
}
