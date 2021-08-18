TEMPLATE = app
TARGET = rdcpp
DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
RCC_DIR = build
CONFIG += console release gnu++11
QT += widgets sql printsupport

QMAKE_CXXFLAGS +=\
    -Wno-unused-parameter \
    -Wno-deprecated-declarations

include(C:\Users\Admin\Downloads\Programs\ReadyLib\dev\qcustomplot\2.1.0\GQCustomPlot.pri)

LIBS +=\
    -lgsl -lgslcblas -lm \

INCLUDEPATH +=\
    /mingw32/include \
    ../code/src \

SOURCES +=\
    ../code/src/*.cpp \

HEADERS +=\
    ../code/src/*.h \
    