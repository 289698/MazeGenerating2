#-------------------------------------------------
#
# Project created by QtCreator 2018-07-11T22:01:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Maze2
TEMPLATE = app


SOURCES += main.cpp\
        mazewindow.cpp \
    huntandkill.cpp \
    mazemap.cpp \
    mazeboard.cpp \
    gamemechanics.cpp

HEADERS  += mazewindow.h \
    huntandkill.h \
    mazemap.h \
    mazeboard.h \
    gamemechanics.h

RESOURCES += textures.qrc

DISTFILES +=
