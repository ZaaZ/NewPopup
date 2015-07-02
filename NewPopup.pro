#-------------------------------------------------
#
# Project created by QtCreator 2015-06-24T23:06:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NewPopup
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    popupmsg.cpp \
    countmsg.cpp

HEADERS  += mainwindow.h \
    popupmsg.h \
    countmsg.h

FORMS    += mainwindow.ui \
    popupmsg.ui \
    countmsg.ui

RESOURCES += \
    resource.qrc
