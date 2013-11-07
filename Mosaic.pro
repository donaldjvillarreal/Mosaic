#-------------------------------------------------
#
# Project created by QtCreator 2013-10-28T09:51:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Mosaic
TEMPLATE = app


# Input
HEADERS += ControlPanel.h \
           Globals.h \
           ImageWindow.h \
           MainWindow.h \
           TesseraParameters.h
SOURCES += ControlPanel.cpp \
           ImageWindow.cpp \
           main.cpp \
           MainWindow.cpp \
           TesseraParameters.cpp
RESOURCES += mainres.qrc
