QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bullet
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mainview.cpp \
    renderable.cpp \
    background.cpp \
    timer.cpp \
    ship.cpp \
    texturerenderable.cpp

HEADERS  += mainwindow.h \
    mainview.h \
    renderable.h \
    background.h \
    timer.h \
    ship.h \
    texturerenderable.h

RESOURCES += \
    resources.qrc \
    textures.qrc

FORMS    += mainwindow.ui

LIBS += -lSOIL

CONFIG += c++11 -Wall -pedantic

