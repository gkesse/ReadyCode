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

GRLIB = $$(GPROJECT_ROOT)\ReadyLib\dev\mingw

include($$GRLIB\src\qtawesome\QtAwesome.pri)

INCLUDEPATH +=\
    ..\code\src\manager \
    ..\build \
    $$GRLIB\include \
    $$GRLIB\include\libxml2 \

SOURCES +=\
    $$files(..\code\src\*.cpp) \
    $$files(..\code\src\manager\*.cpp) \
    
HEADERS +=\
    $$files(..\code\src\manager\*.h) \

FORMS +=\
    $$files(..\code\src\manager\*.ui) \

LIBS +=\
    -L$$GRLIB\lib \
    -L$$GRLIB\bin \
    -lws2_32 -lxml2 -lz -liconv \
    -lopencv_core452 -lopencv_highgui452 -lopencv_imgcodecs452 \
    