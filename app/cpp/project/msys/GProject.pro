TEMPLATE = app
TARGET = rdcpp
DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
RCC_DIR = build
CONFIG += console debug
QT += widgets sql

QMAKE_CXXFLAGS +=\
    -Wno-unused-parameter \
    -Wno-deprecated-declarations

INCLUDEPATH +=\
    /mingw32/include \
    /mingw32/include/libxml2 \
    ../code/src \

SOURCES +=\
    ../code/src/*.cpp \

HEADERS +=\
    ../code/src/*.h \
    
LIBS +=\
    -lxml2 \
    -lws2_32 \
    