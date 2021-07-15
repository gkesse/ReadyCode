TEMPLATE = app
TARGET = rdcpp
DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
RCC_DIR = build
CONFIG += console release gnu++11
QT += widgets sql printsupport dbus

QMAKE_CXXFLAGS +=\
    -Wno-unused-parameter \
    -Wno-deprecated-declarations

include(C:\Users\Admin\Downloads\Programs\ReadyLib\dev\qtawesome\4.7.0\QtAwesome.pri)
include(C:\Users\Admin\Downloads\Programs\ReadyLib\dev\qcustomplot\2.1.0\GQCustomPlot.pri)

INCLUDEPATH +=\
    /mingw32/include \
    ../code \

SOURCES +=\
    ../code/*.cpp \

HEADERS +=\
    ../code/*.h \

LIBS +=\
    -lgsl -lgslcblas -lm \
    