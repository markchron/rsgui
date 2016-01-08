#-------------------------------------------------
#
# Project created by QtCreator 2016-01-05T14:27:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = prgui
TEMPLATE = app


SOURCES += main.cpp\
        prgui.cpp \
    resprodialog.cpp \
    gensetdialog.cpp \
    cartesiangriddialog.cpp \
    qcustomplot.cpp \
    treeview.cpp

HEADERS  += prgui.h \
    resprodialog.h \
    gensetdialog.h \
    envset.h \
    cartesiangriddialog.h \
    qcustomplot.h \
    treeview.h

FORMS    += prgui.ui \
    resprodialog.ui \
    cartesiangriddialog.ui

RESOURCES += prgui.qrc

DISTFILES +=
