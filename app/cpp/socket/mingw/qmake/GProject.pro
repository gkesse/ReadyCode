TEMPLATE = app
TARGET = rdcpp
DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
RCC_DIR = build
CONFIG += console debug

QMAKE_CXXFLAGS +=\
    -Wno-unused-parameter \
    -Wno-deprecated-declarations \

GRLIB = C:\Users\Admin\Downloads\Programs\ReadyLib\dev
GRDATA = C:\Users\Admin\Downloads\Programs\ReadyData\data

INCLUDEPATH +=\
    ..\code\src\manager \
    $$GRLIB\include \
    $$GRLIB\include\libxml2 \
    $$GRDATA\include \

SOURCES +=\
    $$files(..\code\src\*.cpp) \
    $$files(..\code\src\manager\*.cpp) \
    
LIBS +=\
    -L$$GRLIB\lib \
    -lws2_32 -lxml2 -lz -liconv \
    -lfreeglut.dll \
    