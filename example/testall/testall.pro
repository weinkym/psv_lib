#-------------------------------------------------
#
# Project created by QtCreator 2014-09-20T20:17:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testall
TEMPLATE = app

LIBS += -L../../bin -lpsv_lib
DESTDIR = ../../bin
INCLUDEPATH += ../../include
SOURCES += main.cpp\
        mainwindow.cpp \
    testpublic.cpp

HEADERS  += mainwindow.h \
    testpublic.h

FORMS    += mainwindow.ui

win32:RC_FILE = app.rc
