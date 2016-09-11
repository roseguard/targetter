#-------------------------------------------------
#
# Project created by QtCreator 2016-07-08T12:51:41
#
#-------------------------------------------------

QT       += core gui network multimedia sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Spirit_war
TEMPLATE = app


SOURCES += main.cpp\
        basewindow.cpp \
    roptmenu.cpp \
    mainmenuscene.cpp \
    optionsmenu.cpp \
    multiplayermenu.cpp \
    hostmenuscene.cpp \
    hostacceptdeny.cpp \
    connectto.cpp \
    gamescene.cpp \
    fieldcell.cpp \
    creatureitem.cpp \
    objectitem.cpp

HEADERS  += basewindow.h \
    foropt.h \
    roptmenu.h \
    mainmenuscene.h \
    optionsmenu.h \
    multiplayermenu.h \
    hostmenuscene.h \
    hostacceptdeny.h \
    connectto.h \
    gamescene.h \
    fieldcell.h \
    creatureitem.h \
    objectitem.h

RESOURCES += \
    resouces.qrc
