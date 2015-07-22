TEMPLATE = app

TARGET = DiPlot
QT += core gui quick

SOURCES += main.cpp \
    Plot.cpp \
    Point.cpp \
    LineNode.cpp \
    BackgroundNode.cpp

RESOURCES += qml.qrc

QMAKE_CXXFLAGS += -std=gnu++11

DEPENDPATH += ./

HEADERS += \
    Plot.h \
    Point.h \
    LineNode.h \
    BackgroundNode.h
