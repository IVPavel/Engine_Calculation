#-------------------------------------------------
#
# Project created by QtCreator 2019-11-20T22:01:17
#
#-------------------------------------------------

QT       += core gui sql webkit webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = EngineCalculation
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Database/DatabaseManager.cpp \
    Database/EngineParameters.cpp \
    Database/FuelParameters.cpp \
    buildgraphic.cpp \
    dialogtpp.cpp \
    fourthtab.cpp \
    fuel.cpp \
    ThermophysicalIndicators.cpp \
    thermophysicalparameters.cpp \
    qcustomplot.cpp \
    thermind.cpp \
    BuildGraphWindow.cpp

HEADERS  += mainwindow.h \
    Database/DatabaseManager.h \
    Database/EngineParameters.h \
    Database/FuelParameters.h \
    buildgraphic.h \
    dialogtpp.h \
    fuel.h \
    ThermophysicalIndicators.h \
    thermophysicalparameters.h \
    qcustomplot.h \
    thermind.h \
    BuildGraphWindow.h

FORMS    += mainwindow.ui \
    buildgraphic.ui \
    dialogtpp.ui \
    thermophysicalparameters.ui \
    buildgraphwindow.ui

RESOURCES += \
    res.qrc

DISTFILES +=
