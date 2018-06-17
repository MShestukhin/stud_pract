#-------------------------------------------------
#
# Project created by QtCreator 2018-06-11T17:57:16
#
#-------------------------------------------------

QT       += core gui
QT       +=network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = maxim
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    udpclient.cpp

HEADERS  += widget.h \
    udpclient.h \
    user.h

FORMS    += widget.ui
