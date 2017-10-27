#-------------------------------------------------
#
# Project created by QtCreator 2017-10-19T14:25:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 02_ccpath
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    ../fltk-graphics/display.cc \
    ../fltk-graphics/graphic-objects.cc \
    ../smt/cc-dubins.cc \
    ../smt/cc-rs.cc \
    ../smt/configuration.cc \
    ../smt/graphicize.cc \
    ../smt/paths.cc \
    ../utilities/utilities.cc

HEADERS += \
        mainwindow.h \
    ../smt/cc-dubins.h \
    ../smt/cc-rs.h \
    ../smt/configuration.h \
    ../smt/graphicize.h \
    ../smt/object.h \
    ../smt/paths.h \
    ../utilities/utilities.h \
    ../fltk-graphics/display.h \
    ../fltk-graphics/graphic-objects.h

FORMS += \
        mainwindow.ui

INCLUDEPATH += ../smt \
    ../utilities \
    ../fltk-graphics

LIBS += -lfltk


DISTFILES += \
    utilities/fresnel.data \
    ../utilities/fresnel.data
