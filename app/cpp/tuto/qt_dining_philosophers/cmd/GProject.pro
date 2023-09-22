TEMPLATE = app
TARGET = rdv_cpp
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

GSRC = ..\src

SOURCES +=\
    $$files($$GSRC\*.cpp) \
    
HEADERS +=\
    $$files($$GSRC\*.h) \

FORMS +=\
    $$files($$GSRC\*.ui) \

