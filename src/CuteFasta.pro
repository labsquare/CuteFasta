#-------------------------------------------------
#
# Project created by QtCreator 2017-06-16T09:48:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CuteFasta
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    FastaDevice.cpp

HEADERS  += MainWindow.h \
    FastaDevice.h

FORMS    += MainWindow.ui
