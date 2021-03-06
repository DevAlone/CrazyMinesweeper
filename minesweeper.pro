#-------------------------------------------------
#
# Project created by QtCreator 2017-04-05T12:25:44
#
#-------------------------------------------------

CONFIG += c++14
QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = minesweeper
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


SOURCES += main.cpp\
    minesfield.cpp \
    minesfieldwidget.cpp \
    point.cpp \
    minesfieldwidgetsettings.cpp \
    cell.cpp \
    mainwindow.cpp \
    minesfieldscrollablewidget.cpp \
    newgamedialog.cpp \
    minesfieldsettingsdialog.cpp \
    colorchoosebutton.cpp \
    wongamedialog.cpp \
    minesfieldwidgetupdaterthread.cpp

HEADERS  += \
    minesfield.h \
    minesfieldwidget.h \
    point.h \
    minesfieldwidgetsettings.h \
    cell.h \
    mainwindow.h \
    minesfieldscrollablewidget.h \
    newgamedialog.h \
    minesfieldsettingsdialog.h \
    colorchoosebutton.h \
    wongamedialog.h \
    minesfieldwidgetupdaterthread.h

# FORMS    +=

FORMS += \
    mainwindow.ui \
    newgamedialog.ui \
    minesfieldsettingsdialog.ui \
    wongamedialog.ui


