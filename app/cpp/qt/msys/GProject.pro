TEMPLATE = app
TARGET = $$(GPROJECT_TARGET)
DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
RCC_DIR = build
CONFIG += console release gnu++11
QT += widgets sql printsupport
RESOURCES += $$(GPROJECT_RES)

QMAKE_CXXFLAGS +=\
    -Wno-unused-parameter \
    -Wno-deprecated-declarations

include($$(GPROJECT_SRC)/GMain.pri)

INCLUDEPATH +=\
    /mingw32/include \

LIBS +=\
