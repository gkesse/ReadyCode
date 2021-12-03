TEMPLATE = app
TARGET = rdcpp
DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
RCC_DIR = build
CONFIG += console debug gnu++11
QT += widgets printsupport

QMAKE_CXXFLAGS +=\
    -Wno-unused-parameter \
    -Wno-deprecated-declarations \

GRLIB = C:\Users\Admin\Downloads\Programs\ReadyLib\dev

include($$GRLIB\src\qtawesome\QtAwesome.pri)

INCLUDEPATH +=\
    ..\code\src\manager \
    $$GRLIB\include \
    $$GRLIB\include\libxml2 \

SOURCES +=\
    $$files(..\code\src\*.cpp) \
    $$files(..\code\src\manager\*.cpp) \
    
HEADERS +=\
    $$files(..\code\src\manager\*.h) \

LIBS +=\
    -L$$GRLIB\lib \
    -lws2_32 -lxml2 -lz -liconv -lsqlite3 \
    