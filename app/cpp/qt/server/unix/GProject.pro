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

INCLUDEPATH +=\
    ../code \

SOURCES +=\
    ../code/main.cpp \
    ../code/GWindow.cpp \
    ../code/GWindowGL.cpp \

HEADERS +=\
    ../code/GWindow.h \
    ../code/GWindowGL.h \

LIBS +=\
    