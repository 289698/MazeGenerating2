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
    hunt-and-kill.cpp \
    game-mechanics.cpp \
    maze.cpp \
    game-map.cpp \
    launcher-widget.cpp \
    game-widget.cpp \
    textures.cpp \

HEADERS  += \
    hunt-and-kill.h \
    game-mechanics.h \
    maze.h \
    game-map.h \
    launcher-widget.h \
    game-widget.h \
    textures.h

RESOURCES += textures.qrc

DISTFILES += \
    draft.h

FORMS +=
