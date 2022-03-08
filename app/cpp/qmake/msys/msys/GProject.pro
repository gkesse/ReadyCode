TEMPLATE = app
TARGET = rdcpp
DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
RCC_DIR = build
CONFIG += console debug gnu++11
QT += widgets

QMAKE_CXXFLAGS +=\
    -Wno-unused-parameter \
    -Wno-deprecated-declarations \

GRLIB = C:\Users\Admin\Downloads\Programs\ReadyLib\dev\msys

include($$GRLIB\src\qtawesome\QtAwesome.pri)

INCLUDEPATH +=\
    ..\code\src\manager \
    /mingw64/include \
    /mingw64/include/libxml2 \

SOURCES +=\
    $$files(..\code\src\*.cpp) \
    $$files(..\code\src\manager\*.cpp) \

HEADERS +=\
    $$files(..\code\src\manager\*.h) \

LIBS +=\
    -L/mingw64/lib \
	-lxml2 -lmariadb \
    