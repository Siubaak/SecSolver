#-------------------------------------------------
#
# Project created by QtCreator 2016-04-22T09:17:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SCS
TEMPLATE = app


SOURCES += main.cpp\
        scs.cpp \
    graph.cpp \
    figure.cpp \
    fiber.cpp \
    input.cpp

HEADERS  += scs.h \
    graph.h \
    figure.h \
    fiber.h \
    input.h

FORMS    += scs.ui
